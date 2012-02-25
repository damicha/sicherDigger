/******************************************************************************/
/*!
 * \file    SDig_LevelEngine.h
 * \brief   Initializes and controls the engines and data structures of the
 *          level.
 *
 * \author  damicha of defect
 * \date    2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_LEVEL_ENGINE_H_
#define _SDIG_LEVEL_ENGINE_H_

#include "SDig_TimeEngine.h"
#include "SDig_TextEngine.h"
#include "SDig_PhysicsEngine.h"

#include "SDig_LevelConfig.h"
#include "SDig_ConfigData.h"

#include "objField.h"

namespace SDig {

/*!
 * \class   LevelEngine
 * \brief   Implementes the game data, controlling and engines.
 */
class LevelEngine
{
/* ======== class types ======== */    
public:
    /*!
     * \brief   States of the level
     */
    enum StateType {
        //LST_PRE_START
        ST_START,               //!< start the level
        ST_RUNNING,             //!< level is running (normal state)
        ST_ENDING,              //!< level is within its end phase
        ST_END                  //!< level end
    };

/* ======== attributes ======== */    
private:
    objField        *mField;    //!< object field (game level data)

    TextEngine      mTxt;       //!< text engine
    PhysicsEngine   mPhy;       //!< physics engine

    StateType       mState;     //!< current state of the level

    // FIXME: create LevelStatisticData Class/Struct
    int mTimeLimit;             //!< The level's time limit.
    int mTimeCnt;               //!< The current time counter value.

    /* ======== functions ======== */    
public:
     /* Constructor */
    LevelEngine(void);
    
     /* Destructur */
    ~LevelEngine(void);

    /* Set start state */
    void setStart();

    /* Run level engine for one iteration. */
    void run(TextEngine::ButtonType button);
    
    /*!
     * \brief   Get object field address.
     */
    objField *getField(void) {
        return mField;
    }
    
    /*!
     * \brief   Get engine state
     */
    StateType getState(void) {
        return mState;
    }
    
    /*!
     * \brief   Get value of the level timer.
     */
    int getTimer(void) {
        return mTimeCnt;
    }
};


}       // namespace

#endif // _SDIG_LEVEL_ENGINE_H_
