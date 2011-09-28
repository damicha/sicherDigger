/*! ****************************************************************************
 *
 * \file    SDig_GameEngine.h
 * \brief   Initializes and controls the game data and engines.
 *
 * \author  damicha of defect
 * \date    2011
 *
 ******************************************************************************/

#ifndef _SDIG_GAME_ENGINE_H_
#define _SDIG_GAME_ENGINE_H_

#include "SDig_TimeEngine.h"
#include "SDig_TextEngine.h"
#include "SDig_PhysicsEngine.h"

#include "SDig_LevelConfig.h"
#include "configData.h"

#include "objField.h"

//using namespace std;


namespace SDig {

/*!
 * \class   GameEngine
 * \brief   Implementes the game data, controlling and engines.
 */
class GameEngine
{
/* ======== attributes ======== */    
private:
    objField    *mField;        //!< object field (game level data)

    TextEngine      mTxt;   //!< test engine
    TimeEngine      mTime;  //!< time engine
    PhysicsEngine   mPhy;   //!< physics engine

/* ======== functions ======== */    
public:
    /*!
     * \brief   constructor
     */
    GameEngine(void)
    {
        /* select config and create object field */
        LevelConfig *cfg = &field_a;
        mField  = new objField(*cfg);

        /* set duration of one turn */
        mTime.setTriggerInterval(250000);
    }
    
    
    /*!
     * \brief   destructur
     */
    ~GameEngine(void)
    {
        delete mField;
    }

    /*!
     * \brief   initizalise game engine
     */
    void init()
    {
    }

    /*!
     * \brief   run game engine until it quits.
     */
    void run()
    {
        bool stop = false;
        int loop_cnt = 0;           // counts the number of iterrations
        while(stop == false) 
        {
            const int str_len = 128;
            char str[str_len];

            mTime.wait4TriggerEvent();

            /* get last pushed button */
            // FIXME: detection of only the last and only one pressed
            //        button is possible
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
                case TextEngine::BT_START:
                    stop = true;                // leave the loop
                    break;
                default:
                    break;
            }

            mPhy.run(*mField, moveDirection);

            /* create string with timing information */
            snprintf(str, str_len, "%3d", loop_cnt);
            
            /* generate the output */
            mTxt.drawField(*mField, str);
            
            /* print timing debug information */
            mTxt.drawDebugInfo(mTime);
        
            /* increase loop counter */
            loop_cnt++;
        }
    
    }

};


}       // namespace

#endif // _SDIG_GAME_ENGINE_H_
