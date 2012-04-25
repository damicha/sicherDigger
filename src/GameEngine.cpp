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
#include "GameEngineTypes.h"

#include "SDig_TimeEngine.h"
#include "TextEngine.h"
#include "PhysicsEngine.h"

#include "ObjField/Field.h"

#include "LevelConfig.h"
#include "LevelConfigSet.h"
#include "LevelData.h"

using namespace SDig;


/* ==========================================================================
 * init functions
 * ========================================================================== */
    
/*!
 * \brief   constructor
 */
GameEngine::GameEngine(void)
{
    /* set duration of one turn (1/60 sec) */
    mTime.setTriggerInterval(16667);    // in us

    /* create level configuration set */
    mLevelSet = new LevelConfigSet;
}
    
/*!
 * \brief   destructur
 */
GameEngine::~GameEngine(void)
{
    /* destroy level configuration set */
    delete mLevelSet;
}

/*!
 * \brief   Initialize level configuration set
 */
void GameEngine::initLevelConfig()
{
    /* create Set A */
    mLevelSet->addConfig(&level_01);
    mLevelSet->addConfig(&level_02);
    mLevelSet->addConfig(&level_03);
}



/* ==========================================================================
 * engines run functions
 * ========================================================================== */

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

    // FIXME: move to higher layer, init() and run() has the same level
    /* init level set */
    initLevelConfig();

    // FIXME: move phyEngine triggering to TimeEngine
    int phyTrigger = 0;
    
    using namespace GameEngineTypes;    // refer to button types (BT_...)
    GameEngineTypes::Button  button     = BT_NONE;
    GameEngineTypes::Button  phyButton  = BT_NONE;
 
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
                static int selLevel = 0;                // selected level
                int levelNum = mLevelSet->getNumber();  // number of provided levels

                /* level selection by setting the level number */
                if        (button == BT_RIGHT) {
                    getNextLevelNr(&selLevel, levelNum, true);
                } else if (button == BT_LEFT) {
                    getPrevLevelNr(&selLevel, levelNum, true);
                }

                /* change state */
                if        (button == BT_START)  {
                    s_next = EST_LEVEL_EXEC;
                    /* init level engine and set level configuration to use */
                    mLevel.initLevelEngine(mLevelSet->getConfig(selLevel));
                } else if (button == BT_SELECT) {
                    s_next = EST_MAIN_MENU;
                }

                /* print menu */
                // FIXME: use level nr ? or level name
                mTxt.drawLevelSelectMenu(selLevel + 1);
                
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

/* ==========================================================================
 * level select functions
 * ========================================================================== */

/*!
 * \brief   Select next level
 * \detail  This functions selects the next possible level number as a function
 *  of if the wrap around of the numbering is allow or not.
 * \param[inout]  *pLevelNr     Level number to increase.
 * \param[in]     pLevelNum     Maximum level count value.
 * \param[in]     pAllowWrap    Flags that allows wrap around.
 * \return  True if there was a wrap around or the upper boarder of level
 *  numbers is reached if a wrap around is not allowed.
 */
bool GameEngine::getNextLevelNr(int *pLevelNr, int pLevelNum, bool pAllowWrap) const 
{
    if (*pLevelNr >= pLevelNum-1)
    {
        if (pAllowWrap == true) {
            *pLevelNr = 0;
        }
        return true;
    }
    else
    {
        (*pLevelNr)++;
        return false;
    }
}

/*!
 * \brief   Select previous level
 * \detail  This functions selects the previous level number as a function
 *  of if the wrap around of the numbering is allow or not.
 * \param[inout]  *pLevelNr     Level number to decrease.
 * \param[in]     pLevelNum     Maximum level count value.
 * \param[in]     pAllowWrap    Flags that allows wrap around.
 * \return  True if there was a wrap around or the lower boarder (0) of level
 *  numbers is reached if a wrap around is not allowed.
 */
bool GameEngine::getPrevLevelNr(int *pLevelNr, int pLevelNum, bool pAllowWrap) const 
{
    if (*pLevelNr <= 0)
    {
        if (pAllowWrap == true) {
            *pLevelNr = pLevelNum-1;
        }
        return true;
    }
    else
    {
        (*pLevelNr)--;
        return false;
    }
}

