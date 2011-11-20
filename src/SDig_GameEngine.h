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
#include "SDig_PhysicsEngine.h"

#include "SDig_LevelConfig.h"
#include "SDig_ConfigData.h"

#include "objField.h"

//using namespace std;


namespace SDig {

/*!
 * \class   GameEngine
 * \brief   Implementes the game data, controlling and engines.
 */
class GameEngine
{
/* ======== class types ======== */    
public:
#if 0
    /*!
     * \brief   State of a menu (used as exit reason)
     */
    enum MenuStateType {
        MST_QUIT,           //!< menu requires quit
        MST_START_LEVEL,    //!< start a level
    };
#endif
/* ======== attributes ======== */    
private:
    objField    *mField;        //!< object field (game level data)

    TextEngine      mTxt;   //!< test engine
    TimeEngine      mTime;  //!< time engine
    PhysicsEngine   mPhy;   //!< physics engine

    int mTimeLimit;         //!< The level's time limit. FIXME: move to LevelEngine
/* ======== functions ======== */    
public:
     /* Constructor */
    GameEngine(void);
    
     /* Destructur */
    ~GameEngine(void);

    /*!
     * \brief   initialize game engine
     */
    void init() {}

    /* Run game engine until it quits. */
    void run();

    /* Main menu */
    void runMainMenu();
    
    /* a single Level */
    void runLevel();
};


}       // namespace

#endif // _SDIG_GAME_ENGINE_H_
