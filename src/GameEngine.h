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

#include "GameEngineTypes.h"
#include "SDig_TimeEngine.h"
#include "TextEngine.h"
#include "LevelEngine.h"
#include "PhysicsEngine.h"

#include "LevelConfigSet.h"


namespace SDig {

/*!
 * \class   GameEngine
 * \brief   Implements the game data, controlling and engines.
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
    LevelConfigSet  *mLevelSet; //!< set of level configurations

/* ======== init functions ======== */    
public:

    /* Constructor */
    GameEngine(void);
        
    /* Destructur */
    ~GameEngine(void);

    /* Initialize level configuration set */
    void initLevelConfig();
    
/* ======== run functions ======== */    
public:
    /* Run game engine until it quits. */
    void run();

/* ======== level select functions ======== */
public:
    /* select next level */
    bool getNextLevelNr(int *pLevelNr, int pLevelNum, bool pAllowWrap) const; 
    
    /* select previous level */
    bool getPrevLevelNr(int *pLevelNr, int pLevelNum, bool pAllowWrap) const; 

};


}       // namespace

#endif // _SDIG_GAME_ENGINE_H_
