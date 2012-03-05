/******************************************************************************/
/*!
 * \file    SDig_LevelEngine.cpp
 * \brief   Initializes and controls the engines and data structures of the
 *          level.
 *
 * \author  damicha of defect
 * \date    2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "SDig_LevelEngine.h"
#include "SDig_TimeEngine.h"
#include "SDig_PhysicsEngine.h"

#include "objField.h"

using namespace SDig;

/*!
 * \brief   Constructor
 */
LevelEngine::LevelEngine(void)
{
    /* select config and create object field */
    // FIXME:
    // - get configuration as an input parameter
    // - move config setting and field creation to an subfunction
    LevelConfig *cfg = &field_a;
    mField  = new objField(*cfg);

    mTimeLimit = cfg->getTimeLimit();
    mSandReq   = cfg->getSandReq(); 
}
    
/*!
 * \brief   Destructur
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

// FIXME: present level exit state not as a return value -> getState function of
// an private member (mLevelExit..)
/* Run level engine for one iteration. */
void LevelEngine::run(TextEngineTypes::Button button)
{

    using namespace TextEngineTypes;    // refer to button types (BT_...)
    PhysicsEngine::MovementType moveDirection = PhysicsEngine::MT_NONE;
    
    /* determine players move direction as a function of the pushed button */
    switch (button)
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
        /* configure level */
        case ST_START:
        {
            mPhy.init(mTimeLimit);  // FIXME: initialize the whole level (use level config)
            mState = ST_RUNNING;
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
            mPhy.run(*mField, moveDirection);

            SDig::DOTPlayer *player = (SDig::DOTPlayer *)mField->mPlayer->getTypeObject();
            SDig::DOTExit   *exit   = (SDig::DOTExit *)mField->mExit->getTypeObject();
//            SDig::DOTPlayer *player = dynamic_cast<SDig::DOTPlayer *>(mField->pl_entry->data->getTypeObject());
//            SDig::DOTExit   *exit  = dynamic_cast<SDig::DOTExit *>(mField->mExit->data->getTypeObject());
            /* stop running the level if time is up */
            if (mPhy.getTimeCnt() == 0) {
                mState = ST_END;
            }
           
            /* FIXME: change exit state from closed to open as a function of eaten sand */
            /* FIXME: send a signal to a signal handler (the exit is connected to it an reacts on ReqSandEaten with an open door) */
            if (mPhy.getSandCnt() >= mSandReq) {
                exit->setState(DOTExit::ST_OPEN);
            }

            /* stop running if player has exited the level */
            if (player->getState() == DOTPlayer::ST_EXITED) {
                mState = ST_END;
            }
            
            break;
        }

        case ST_END:
            /* FIXME: sum up results */
            break;
    }

    return;
}



