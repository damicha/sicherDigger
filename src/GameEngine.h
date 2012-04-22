/******************************************************************************/
/*!
 * \file    GameEngine.h
 * \brief   Initializes and controls the game data and engines.
 *
 * \author  damicha of defect
 * \date    2011-2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_GAME_ENGINE_H_
#define _SDIG_GAME_ENGINE_H_

#include "SDig_TimeEngine.h"
#include "TextEngine.h"
#include "LevelEngine.h"
#include "PhysicsEngine.h"

#include "LevelConfig.h"
#include "SDig_ConfigData.h"


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
        EST_MAIN_MENU,              //!< main menu
        EST_LEVEL_SELECT_MENU,      //!< select the level
        EST_LEVEL_EXEC,             //!< level execution
        EST_QUIT,                   //!< leave game engine
    };

/* ======== attributes ======== */    
private:
    TextEngine      mTxt;       //!< test engine
    TimeEngine      mTime;      //!< time engine
    LevelEngine     mLevel;     //!< level engine FIXME: dynamically?

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
