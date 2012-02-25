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
#include "SDig_TextEngineTypes.h"
#include "SDig_TextEngine.h"
#include "SDig_PhysicsEngine.h"

#include "objField.h"

using namespace SDig;


/*!
 * \brief   run game engine until it quits.
 */
/* Implemented sequences:
   menu  -> start                       - go to level start
        <-  start                       - go back to menu
            start  -> level             - run level
                      level  -> end     - conclusion
                  <-----------  end     - restart level
        <---------------------  end     - go back to menu

*/
void GameEngine::run()
{
    EngineStateType s_curr;     // current state
    EngineStateType s_next;     // next state

    s_curr = EST_MAIN_MENU;
    s_next = EST_MAIN_MENU;

    mTxt.clearScreen();
    
    // FIXME: move phyEngine triggering to TimeEngine
    int phyTrigger = 0;
    
    using namespace TextEngineTypes;    // refer to button types (BT_...)
    TextEngineTypes::Button  button     = BT_NONE;
    TextEngineTypes::Button  phyButton  = BT_NONE;
 
    bool stop = false;
    while(stop == false) 
    {
    
        s_curr = s_next;

        /* sync on tigger event to display content */
        mTime.wait4TriggerEvent();

        /* get last pushed button */
        // FIXME: detection of only the last and only one pressed
        //        button is currently possible
        // -> change to pressed, released behavior/events
        button = mTxt.getButton();
        
        switch (s_curr)
        {
            /* ==== Main menu ==== */
            case EST_MAIN_MENU:
            {
                /* change state */
                if        (button == BT_START)  {
                    s_next = EST_LEVEL_START_MENU;
                } else if (button == BT_SELECT) {
                    s_next = EST_QUIT;
                }
                
                /* print menu */
                mTxt.drawMainMenu();

                break;
            }
            
            /* ==== Level Start Menu ==== */
            case EST_LEVEL_START_MENU:
            {
                /* change state */
                if        (button == BT_START)  {
                    s_next = EST_LEVEL_EXEC;
                    /* init level state */
                    mLevel.setStart(); 
                } else if (button == BT_SELECT) {
                    s_next = EST_MAIN_MENU;
                }

                /* print menu */
                mTxt.drawLevelStart();
                
                break;
            }

            /* ==== Level Execution ==== */
            case EST_LEVEL_EXEC:
            {
                /* get first button event */
                if (button != BT_NONE &&
                    phyButton == BT_NONE) {
                    phyButton = button;
                }

                bool isExit = false;
                if (phyTrigger % 15 == 0) {  
                    mLevel.run(phyButton);
                    if (mLevel.getState() == LevelEngine::ST_END) {
                        isExit = true;
                    }
                    // reset button value
                    phyButton = BT_NONE;
                }
                phyTrigger++;

                /* change state */
                if        (button == BT_SELECT)  {
                    s_next = EST_LEVEL_END_MENU;
                } else if (isExit == true) {
                    s_next = EST_LEVEL_END_MENU;
                }
    
                /* generate the output */
                mTxt.drawLevel(mLevel);
                break;
            }

            /* ==== Level End Menu ==== */
            case EST_LEVEL_END_MENU:
            {
                /* change state */
                if        (button == BT_START)  {
                    s_next = EST_LEVEL_START_MENU;
                } else if (button == BT_SELECT) {
                    s_next = EST_MAIN_MENU;
                }
                
                /* print menu */
                mTxt.drawLevelEnd();
                
                break;
            }

            case EST_QUIT:
                stop = true;
                break;
        }

        /* clear screen if menu will change */
        if (s_curr != s_next) {
            mTxt.clearScreen();
        }


    }

    // default
    return;
}


