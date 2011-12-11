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

    /* set duration of one turn (1/60 sec) */
    mTime.setTriggerInterval(16667);    // in us
}
    
/*!
 * \brief   destructur
 */
GameEngine::~GameEngine(void)
{
    delete mField;
}


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
    TextEngine::ButtonType  button = TextEngine::BT_NONE;
    TextEngine::ButtonType  phyButton = TextEngine::BT_NONE;
    bool stop = false;
    while(stop == false) 
    {
    
        s_curr = s_next;

        /* sync on tigger event to display content */
        mTime.wait4TriggerEvent();

        /* get last pushed button */
        // FIXME: the detection of only the last and only one pressed
        //        button is currently possible
        // -> change to pressed, released behavior/events
        button = mTxt.getButton();
        
        switch (s_curr)
        {
            case EST_MAIN_MENU:
                /* print menu */
                mTxt.drawMainMenu();

                /* change state */
                if        (button == TextEngine::BT_START)  {
                    s_next = EST_LEVEL_START_MENU;
                } else if (button == TextEngine::BT_SELECT) {
                    s_next = EST_QUIT;
                }
                break;
            
            case EST_LEVEL_START_MENU:
                /* print menu */
                mTxt.drawLevelStart();
                
                /* change state */
                if        (button == TextEngine::BT_START)  {
                    s_next = EST_LEVEL_EXEC;
                } else if (button == TextEngine::BT_SELECT) {
                    s_next = EST_MAIN_MENU;
                }
                break;


            case EST_LEVEL_EXEC:
            {
                /* get first button event */
                if (button != TextEngine::BT_NONE &&
                    phyButton == TextEngine::BT_NONE) {
                    phyButton = button;
                }

                bool isExit = false;
                if (phyTrigger % 15 == 0) {  
                    isExit = runLevelEngine(phyButton);
                    // reset button value
                    phyButton = TextEngine::BT_NONE;
                }
                phyTrigger++;

                /* change state */
                if        (button == TextEngine::BT_SELECT)  {
                    s_next = EST_LEVEL_END_MENU;
                } else if (isExit == true) {
                    s_next = EST_LEVEL_END_MENU;
                }
                break;
            }

            case EST_LEVEL_END_MENU:
                /* print menu */
                mTxt.drawLevelEnd();
                
                /* change state */
                if        (button == TextEngine::BT_START)  {
                    s_next = EST_LEVEL_START_MENU;
                } else if (button == TextEngine::BT_SELECT) {
                    s_next = EST_MAIN_MENU;
                }
                break;

            case EST_QUIT:
                stop = true;
                break;
        }

        // clear screen if menu will change
        if (s_curr != s_next) {
            mTxt.clearScreen();
        }


    }

    // default
    return;
}

// FIXME: present level exit state not as a return value -> getState function of
// an private member (mLevelExit..)
bool GameEngine::runLevelEngine(TextEngine::ButtonType button)
{
    static float timeCnt = (float)mTimeLimit;   // set time counter
        
    const int str_len = 128;
    char str[str_len];

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
        default:
            break;
    }

    bool levelExit = mPhy.run(*mField, moveDirection);

    /* create string with timing information */
    snprintf(str, str_len, "%6.2f", timeCnt);
    
    /* generate the output */
    mTxt.drawField(*mField, str);
    
    /* print timing debug information */
    mTxt.drawDebugInfo(mTime);

    /* decrease time counter */
    timeCnt = timeCnt - (float)mTime.getTriggerInterval()/(float)mTime.getTimeBase();

    return levelExit;
}



