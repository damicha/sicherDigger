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
#include "SDig_TextEngineTypes.h"
#include "SDig_PhysicsEngine.h"

#include "SDig_LevelConfig.h"
#include "SDig_ConfigData.h"

#include "ObjField/Field.h"

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
        //ST_PRE_START
        ST_START,               //!< start the level
        ST_RUNNING,             //!< level is running (normal state)
        ST_ENDING,              //!< level is within its end phase
        ST_END                  //!< level end
    };

/* ======== attributes ======== */    
private:
    ObjField::Field *mField;        //!< object field (game level data)

    PhysicsEngine   mPhy;           //!< physics engine

    StateType       mState;         //!< current state of the level



    // FIXME: create LevelStatisticData Class/Struct
    int mTimeLimit;             //!< The level's time limit.

    /* ======== functions ======== */    
public:
     /* Constructor */
    LevelEngine(void);
    
     /* Destructur */
    ~LevelEngine(void);

    /* Set start state */
    void setStart();

    /* Run level engine for one iteration. */
    void run(TextEngineTypes::Button button);
    
    /*! \brief  Get object field address. */
    const ObjField::Field *getField(void) {
        return mField;
    }
    
    /*! \brief  Get eaten sand counter value.
     *  \return Eaten sand counter value. */
    int getSandCnt(void) {
        return mField->mPlayer->getSandCnt();
    }
    
    /*! \brief  Get required and to open the exit.
     *  \return Required sand counter value. */
    int getRequiredSand(void) {
        return mField->mExit->getRequiredSand();
    }
    
    /*! \brief  Get current time counter value.
     *  \return Time counter value. */
    int getTimeCnt(void) {
        return mPhy.getTimeCnt();
    }


    /*! \brief  Get engine state */
    StateType getState(void) {
        return mState;
    }
    
};


}       // namespace

#endif // _SDIG_LEVEL_ENGINE_H_
