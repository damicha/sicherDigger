/******************************************************************************/
/*!
 * \file    GameEngine.cpp
 * \brief   Initializes and controls the game data and engines.
 *
 * \author  damicha of defect
 * \date    2011-2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "GameEngine.h"
#include "SDig_TimeEngine.h"
#include "TextEngineTypes.h"
#include "TextEngine.h"
#include "SDig_PhysicsEngine.h"

#include "ObjField/Field.h"

#include "LevelConfig.h"

using namespace SDig;


/*!
 * \brief   run game engine until it quits.
 *
 * The folloing description shows the menu structure of the game engine.
 * <pre>
 *  MM  --> LS                      - go to select level menu
 *     <--  LS                      - go back to menu
 *          LS  --> LE              - run level engine (has its own menus)
 *                  -- level number - DATA: select the level to play
 *
 *          LS <--  LE              - return to level selection
 *                  -- level result - DATA: inform about the level result
 *
 * MM - main menu
 * LS - level selection menu
 * LE - level engine (sub engine called by game engine)
 * </pre>
 *
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
        // FIXME: detection of only the last and only a single pressed
        //  button is currently possible
        // -> change to pressed, released behavior/events
        button = mTxt.getButton();
        
        switch (s_curr)
        {
            /* ==== Main menu ==== */
            case EST_MAIN_MENU:
            {
                /* change state */
                if        (button == BT_START)  {
                    s_next = EST_LEVEL_SELECT_MENU;
                } else if (button == BT_SELECT) {
                    s_next = EST_QUIT;
                }
                
                /* print menu */
                mTxt.drawMainMenu();

                break;
            }
            
            /* ==== Level Select Menu ==== */
            case EST_LEVEL_SELECT_MENU:
            {
                /* change state */
                if        (button == BT_START)  {
                    s_next = EST_LEVEL_EXEC;
                    /* init level engine and set level configuration to use */
                    mLevel.initLevelEngine(&field_a);
                } else if (button == BT_SELECT) {
                    s_next = EST_MAIN_MENU;
                }

                /* print menu */
                // FIXME: use level nr
                mTxt.drawLevelSelectMenu(1);
                
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

                /* run level engine on physics trigger */
                if (phyTrigger % 15 == 0) {  
                    mLevel.run(phyButton, &mTxt);
                    // reset button value
                    phyButton = BT_NONE;
                }
                phyTrigger++;

                /* change state if level has ended */
                // FIXME: get level result
                if (mLevel.isEnd() == true) {
                    s_next = EST_LEVEL_SELECT_MENU;
                }
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


