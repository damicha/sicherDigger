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

#include "LevelEngine.h"
#include "SDig_TimeEngine.h"
#include "SDig_PhysicsEngine.h"
#include "TextEngine.h"

#include "ObjField/Field.h"

using namespace SDig;


/*!
 * \brief   Constructor
 */
LevelEngine::LevelEngine(void)
{
    mField = NULL;
    mTimeLimit = 0;
}
    
/*!
 * \brief   Destructor
 */
LevelEngine::~LevelEngine(void)
{
    delete mField;
}

/*!
 * \brief   Set start state
 */
void LevelEngine::setStart() {
    // FIXME: reset level
    mState = ST_START;
}

/*!
 * \brief   Initialize the level data.
 * \param[in] pCfg  Pointer of the configuration structure to use.
 */
void LevelEngine::initLevel(LevelConfig *pCfg)
{
    /* create game field */
    mField  = new ObjField::Field(pCfg);
    
    /* set levels time limit */
    mTimeLimit = pCfg->getTimeLimit();
    
    /* set internal level engine state to "level info" */
    mState = ST_INFO;
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
void LevelEngine::run(TextEngineTypes::Button pButton, TextEngine *pTxt)
{

    using namespace TextEngineTypes;    // refer to button types (BT_...)
    PhysicsEngine::MovementType moveDirection = PhysicsEngine::MT_NONE;
    
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
            pTxt->drawLevelStartScreen(1, getRequiredSand(), mTimeLimit);

            if (pButton == BT_START)  {
                mState = ST_START;
            }
            break;
        }
        
        /* configure level */
        case ST_START:
        {
            mPhy.init(mTimeLimit);  // FIXME: initialize the whole level (use level config)
            mState = ST_RUNNING;
            pTxt->drawLevel(*this);
            break;
        }

        /* run level */
        case ST_RUNNING:
        {
            /* run physics engine */
            // FIXME: stop counter if player is exiting, but proceed player:
            // -> implement states for the physics engine ?
            // -> or physics engine flags ? - stopTime()/startTime() ?
            // -> or don't control time by physics engine ?
            mPhy.run(mField, moveDirection);

            /* stop running the level if time is up */
            if (mPhy.getTimeCnt() == 0) {
                mEndReason = LER_TIME_UP;
                mState = ST_CONCLUSION;
            }
           
            /* change exit's state to open as a function of eaten sand */
            if (getSandCnt() >= mField->getExit()->getRequiredSand()) {
                mField->getExit()->openIt();
            }

            /* stop running if player has exited the level */
            if (mField->getPlayer()->getState() == DOT::Player::ST_EXITED) {
                mEndReason = LER_SUCCESS;  
                mState = ST_CONCLUSION;
            }
    
            pTxt->drawLevel(*this);

            break;
        }

        /* level conclusion */
        case ST_CONCLUSION:
            pTxt->drawLevelEndScreen(1, mEndReason,
                                     mField->getPlayer()->getSandCnt(),
                                     mField->getExit()->getRequiredSand(),
                                     mPhy.getTimeCnt());
            
            if        (pButton == BT_START) {
                mState = ST_INFO;
            } else if (pButton == BT_SELECT) {
                mState = ST_END;
            }
            break;
        
        /* level engine ends */
        case ST_END:
            /* This state is used to indicates higher level functions that
               the level engine has end */
            // FIXME: provide isEnd(), getEndReason() functions
            break;
    }

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

