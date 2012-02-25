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
#include "SDig_TextEngine.h"
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
    mTimeCnt = mTimeLimit; 
}

// FIXME: present level exit state not as a return value -> getState function of
// an private member (mLevelExit..)
/* Run level engine for one iteration. */
void LevelEngine::run(TextEngine::ButtonType button)
{
//    const int str_len = 128;
//    char str[str_len];

    PhysicsEngine::MovementType moveDirection = PhysicsEngine::MT_NONE;
    
    switch (button)
    {
        case TextEngine::BT_LEFT:
            moveDirection = PhysicsEngine::MT_LEFT; 
            break;
        case TextEngine::BT_RIGHT:
            moveDirection = PhysicsEngine::MT_RIGHT; 
            break;
        case TextEngine::BT_UP:
            moveDirection = PhysicsEngine::MT_UP; 
            break;
        case TextEngine::BT_DOWN:
            moveDirection = PhysicsEngine::MT_DOWN; 
            break;
        default:
            break;
    }

    switch (mState)
    {
        case ST_START:
            mState = ST_RUNNING;
            break;

        case ST_RUNNING:
        {
            bool levelExit = mPhy.run(*mField, moveDirection);
            // FIXME: 
            // - don't use levelExit flag
            // - get players state: exiting -> ending (stop timer)
            // - get level state (timeout)

            if (levelExit == true) {
                mState = ST_END;
            }

            /* decrease level counter */
            mTimeCnt--;
            
            break;
        }

        case ST_END:
            break;
    }

    /* create string with timing information */
    // FIXME: put time count to level data (counter)
//    snprintf(str, str_len, "%04d", mTimeCnt);
   
    // FIXME: remove text output from level engine ???

    /* generate the output */
//    mTxt.drawField(*mField, str);
    
    /* print timing debug information */
//    mTxt.drawDebugInfo(mTime);

    /* decrease time counter */
//    timeCnt = timeCnt - (float)mTime.getTriggerInterval()/(float)mTime.getTimeBase();

    return;
}



