/******************************************************************************/
/*!
 * \file    SDig_GameEngine.cpp
 * \brief   Initializes and controls the game data and engines.
 *
 * \author  damicha of defect
 * \date    2011
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "SDig_GameEngine.h"
#include "SDig_TimeEngine.h"
#include "SDig_TextEngine.h"
#include "SDig_PhysicsEngine.h"

#include "objField.h"

using namespace SDig;

/*!
 * \brief   constructor
 */
GameEngine::GameEngine(void)
{
    /* select config and create object field */
    LevelConfig *cfg = &field_a;
    mField  = new objField(*cfg);

    mTimeLimit = cfg->getTimeLimit();

    /* set duration of one turn */
    mTime.setTriggerInterval(250000);
}
    
/*!
 * \brief   destructur
 */
GameEngine::~GameEngine(void)
{
    delete mField;
}


/*!
 * \brief   Main menu.
 */
void GameEngine::runMainMenu()
{

    while(true) 
    {
        /* sync on tigger event */
        mTime.wait4TriggerEvent();

        /* get button */
        TextEngine::ButtonType      button = mTxt.getButton();
        
        /* print menu */
        mTxt.drawMainMenu();

        switch (button)
        {
            case TextEngine::BT_SELECT:
                return;
            
            case TextEngine::BT_START:
                // FIXME: reset level state
                runLevel();
                break;

            // ignore the other keys
            default:
                break;

        }

    }

    // default
    return;
}

/*!
 * \brief   run game engine until it quits.
 */
// FIXME: split into functions: menu, level (start, run, end)
// FIXME: implement a menu stack:
// mainMenu <-> level (start -> run -> end)
// mainMenu --> exit
void GameEngine::run()
{

    runMainMenu();
}

void GameEngine::runLevel()
{

    bool stop = false;
    float timeCnt = (float)mTimeLimit;   // set time counter
    while(stop == false) 
    {
        const int str_len = 128;
        char str[str_len];

        mTime.wait4TriggerEvent();

        /* get last pushed button */
        // FIXME: detection of only the last and only one pressed
        //        button is currently possible
        // -> change to pressed, released bavior/events
        TextEngine::ButtonType      button = mTxt.getButton();
        PhysicsEngine::MovementType moveDirection = PhysicsEngine::MT_NONE;
        
        switch(button)
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
            case TextEngine::BT_SELECT:
                stop = true;                // leave the loop
                break;
            default:
                break;
        }

        mPhy.run(*mField, moveDirection);

        /* create string with timing information */
        snprintf(str, str_len, "%6.2f", timeCnt);
        
        /* generate the output */
        mTxt.drawField(*mField, str);
        
        /* print timing debug information */
        mTxt.drawDebugInfo(mTime);
    
        /* decrease time counter */
        timeCnt = timeCnt - (float)mTime.getTriggerInterval()/(float)mTime.getTimeBase();
    }

}



