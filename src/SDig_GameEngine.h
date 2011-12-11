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
//    void runMainMenu();
    
    /* a single level sequence */
//    void runLevelExec();
    
    /* the level start */
//    void runLevelStart();
    
    /* the level itself  */
    bool runLevelEngine(TextEngine::ButtonType button);
    
    /* the level end */
//    void runLevelEnd();
};


}       // namespace

#endif // _SDIG_GAME_ENGINE_H_
