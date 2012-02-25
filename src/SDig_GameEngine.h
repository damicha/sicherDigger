/******************************************************************************/
/*!
 * \file    SDig_GameEngine.h
 * \brief   Initializes and controls the game data and engines.
 *
 * \author  damicha of defect
 * \date    2011
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_GAME_ENGINE_H_
#define _SDIG_GAME_ENGINE_H_

#include "SDig_TimeEngine.h"
#include "SDig_TextEngine.h"
#include "SDig_LevelEngine.h"
#include "SDig_PhysicsEngine.h"

#include "SDig_LevelConfig.h"
#include "SDig_ConfigData.h"

#include "objField.h"

//using namespace std;


namespace SDig {

/*!
 * \class   GameEngine
 * \brief   Implementes the game data, controlling and engines.
 * FIXME: move level stuff to level engine
 * \details 
 *  - runs physics engine
 *  - runs text engine
 */
class GameEngine
{
/* ======== class types ======== */    
private:
    /*!
     * \brief   State of the game engine to switch between possible menus
     */
    enum EngineStateType {
        EST_MAIN_MENU,          //!< main menu
        EST_LEVEL_START_MENU,   //!< start of a level
        EST_LEVEL_EXEC,         //!< level execution
        EST_LEVEL_END_MENU,     //!< end of a level
        EST_QUIT,               //!< leave game engine
    };

/* ======== attributes ======== */    
private:
//    objField        *mField;    //!< object field (game level data)

    TextEngine      mTxt;       //!< test engine
    TimeEngine      mTime;      //!< time engine
    LevelEngine     mLevel;     //!< level engine FIXME: dynamically?

    // FIXME: create LevelStatisticData Class/Struct
//    int mTimeLimit;             //!< The level's time limit. FIXME: move to LevelEngine
/* ======== functions ======== */    
public:

    /*!
     * \brief   constructor
     */
    GameEngine(void)
    {
        /* set duration of one turn (1/60 sec) */
        mTime.setTriggerInterval(16667);    // in us
    }
        
    /*!
     * \brief   destructur
     */
    ~GameEngine(void) {}

#if 0
    /*!
     * \brief   initialize game engine
     */
    void init() {}
#endif
    /* Run game engine until it quits. */
    void run();

};


}       // namespace

#endif // _SDIG_GAME_ENGINE_H_
