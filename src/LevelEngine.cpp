/******************************************************************************/
/*!
 * \file    LevelEngine.cpp
 * \brief   Initializes and controls the engines and data structures of the
 *          level.
 *
 * \author  damicha of defect
 * \date    2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

// FIXME:
// - level creation 
// - new states

//#include <exception>

#include "LevelConfigSet.h"     // FIXME: only for testing included

#include "LevelEngine.h"
#include "PhysicsEngine.h"
#include "TextEngine.h"

#include "ObjField/Field.h"

using namespace SDig;


/*!
 * \brief   Constructor
 */
LevelEngine::LevelEngine(void)
{
    mLevelCfg   = NULL;
    mField      = NULL;
    mTimeLimit  = 0;
    mState      = ST_INFO;
}
    
/*!
 * \brief   Destructor
 */
LevelEngine::~LevelEngine(void)
{
    delete mField;
}


/*!
 * \brief   Initialize the level engine members.
 *
 * This function has to be called before the level can be initialized by the
 * initLevel() function.
 * \param[in] pCfg  Pointer of the configuration structure to use.
 */
void LevelEngine::initLevelEngine(const LevelConfig *pCfg)
{
    /* get level configuration data */
    mLevelCfg = pCfg;
    
    /* set internal level engine state to "level info" */
    mState = ST_INFO;
}

/*!
 * \brief   Initialize the level data.
 *
 * The level engine initialization has to be done before by initLevelEngine().
 */
void LevelEngine::initLevel(void)
{


    /* check if level configuration is set */
    /* FIXME:
     * - use own exception, derived from exception
     * - catch exception in a top class
     */
    if (mLevelCfg == NULL) {
        throw "mLevelCfg wasn't set before usage.";
    }

    // FIXME: free level if necessary

    /* create game field from level configuration */
    mField  = new ObjField::Field(mLevelCfg);
    
    /* set levels time limit */
    mTimeLimit = mLevelCfg->getTimeLimit();
            
    mPhy.init(mTimeLimit);
}

/*!
 * \brief   Free level data.
 */
void LevelEngine::freeLevel(void)
{
    delete mField;
}


// FIXME: present level exit state not as a return value -> getState function of
// an private member (mLevelExit..)
/*!
 * \brief   Run level engine for one iteration.
 * \param[in] pButton   Pressed button, to control a level menu or the player.
 */
void LevelEngine::run(GameEngineTypes::Button pButton, TextEngine *pTxt)
{

    using namespace GameEngineTypes;    // refer to button types (BT_...)
    PhysicsEngine::MovementType moveDirection = PhysicsEngine::MT_NONE;
    StateType nextState = mState;


    /* determine players move direction as a function of the pushed button */
    switch (pButton)
    {
        case BT_LEFT:
            moveDirection = PhysicsEngine::MT_LEFT; 
            break;
        case BT_RIGHT:
            moveDirection = PhysicsEngine::MT_RIGHT; 
            break;
        case BT_UP:
            moveDirection = PhysicsEngine::MT_UP; 
            break;
        case BT_DOWN:
            moveDirection = PhysicsEngine::MT_DOWN; 
            break;
        default:
            break;
    }

    /* run level engine */
    switch (mState)
    {
        /* display level information */
        case ST_INFO:
        {
            if (pButton == BT_START)  {
                nextState = ST_START;
            }

            /* Get level information from level configuration, because the
             * level data isn't initialized yet */
            pTxt->drawLevelStartScreen(mLevelCfg->getName(), mLevelCfg->getInfo(),
                                       mLevelCfg->getRequiredSand(),
                                       mLevelCfg->getTimeLimit());
            break;
        }
        
        /* configure level */
        case ST_START:
        {
            /* (re)initialize level data */
            initLevel();

            nextState = ST_RUNNING;
            
            pTxt->drawLevel(this);
            break;
        }

        /* run level */
        case ST_RUNNING:
        {
            /* run physics engine */
            mPhy.run(mField, moveDirection);

            /* stop running the level if time is up */
            if (mPhy.getTimerCnt() == 0) {
                mEndReason = LER_TIME_UP;
                nextState = ST_CONCLUSION;
            }
          
            /* Stop timer if player is entering the exit.
             * - This prevents a time up if the player has already entered the exit. */
            if (mField->getPlayer()->getState() == DOT::Player::ST_EXITING) {
                mPhy.disableTimer();
            }

            /* change exit's state to open as a function of eaten sand */
            if (getSandCnt() >= getRequiredSand()) {
                mField->getExit()->openIt();
            }

            /* stop running if player has exited the level */
            if (mField->getPlayer()->getState() == DOT::Player::ST_EXITED) {
                mEndReason = LER_SUCCESS;  
                nextState = ST_CONCLUSION;
            }
    
            pTxt->drawLevel(this);
            break;
        }

        /* level conclusion */
        case ST_CONCLUSION:
        {    
            if        (pButton == BT_START) {
                nextState = ST_INFO;
            } else if (pButton == BT_SELECT) {
                nextState = ST_END;
            }
            
            pTxt->drawLevelEndScreen(mLevelCfg->getName(), mEndReason,
                                     getSandCnt(), getRequiredSand(),
                                     mPhy.getTimerCnt());
            break;
        }

        /* level engine ends */
        case ST_END:
            /* This state is used to indicates higher level functions that
               the level engine has end */
            // FIXME: provide isEnd(), getEndReason() functions
            break;
    }

    /* Clear screen if state has changed, because a new screen/menu will be drawn */
    if (mState != nextState) {
        pTxt->clearScreen();
    }

    /* set new state value */
    mState = nextState;

    return;
}


/*!
 * \brief   Check if the level has ended.
 */
bool LevelEngine::isEnd(void) const
{
    if (mState == ST_END) {
        return true;
    } else {
        return false;
    }
}
    
/*!
 * \brief   Get the reason of level end.
 */
LevelEngine::LevelEndReason LevelEngine::getLevelEndReason(void) const
{
    return mEndReason;
}

