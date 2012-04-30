/******************************************************************************/
/*!
 * \file    LevelEngine.h
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
#include "GameEngineTypes.h"
#include "PhysicsEngine.h"

#include "ObjField/Field.h"

/* pre-declarations */
namespace SDig {
    class TextEngine;
}

namespace SDig {

/*!
 * \class   LevelEngine
 * \brief   Implements the game data, controlling and engines.
 */
class LevelEngine
{
/* ======== class types ======== */    
public:
    /*!
     * \brief   States of the level
     */
    enum StateType {
        // FIXME: re-order somehow
        /* general states */
        ST_INFO,                //!< display level info before the level starts
        ST_CONCLUSION,          //!< display a conclusion after the level ends
        /* level states */
        ST_START,               //!< start the level
        ST_RUNNING,             //!< level is running (normal state)
//        ST_PAUSE,               //!< pause
        ST_END                  //!< level end - FIXME: replace by ST_CONCLUSION
    };

    /*!
     * \brief   Reason of level ending
     */
    enum LevelEndReason {
        LER_SUCCESS,
        LER_TIME_UP,
        //LER_DEAD,
        //LER_CANCELD
    };


/* ======== attributes ======== */    
private:
    const LevelConfig *mLevelCfg;   /*!< Reference to the level configuration. 
                                         It has to be set by the setLevelConfig() function */
    ObjField::Field *mField;        //!< object field (game level data)

    PhysicsEngine   mPhy;           //!< physics engine

    StateType       mState;         //!< current state of the level
    LevelEndReason  mEndReason;     /*!< reason for level end.
                                     *   Has to be set if the level ends. */


    // FIXME: create LevelStatisticData Class/Struct
    int mTimeLimit;             //!< level's time limit.

public:
    /* ======== init functions ======== */    
    
    /* Constructor */
    LevelEngine(void);
    
    /* Destructor */
    ~LevelEngine(void);

    /* Initialize the level engine members */
    void initLevelEngine(const LevelConfig *pCfg);
private:
    /* Initialize the level data */
    void initLevel(void);

    /* Free level data */
    void freeLevel(void);
public:    
    /* ======== run functions ======== */

    /* Run level engine for one iteration. */
    void run(GameEngineTypes::Button pButton, TextEngine *pTxt);
    
    /* ======== getting member functions ======== */
    
    /*!\brief   Get object field address. */
    const ObjField::Field *getField(void) const {
        return mField;
    }
    
    /*!\brief   Get eaten sand counter value.
     * \return  Eaten sand counter value. */
    int getSandCnt(void) const {
        return mField->getPlayer()->getSandCnt();
    }
    
    /*!\brief   Get required and to open the exit.
     * \return  Required sand counter value. */
    int getRequiredSand(void) const {
        return mField->getExit()->getRequiredSand();
    }
    
    /*!\brief   Get current time counter value.
     * \return  Time counter value. */
    int getTimeCnt(void) const {
        return mPhy.getTimerCnt();
    }

    /* Check if the level has ended. */
    bool isEnd(void) const;
    
    /* Get the reason of level end. */
    LevelEndReason getLevelEndReason(void) const;
    
};


}       // namespace

#endif // _SDIG_LEVEL_ENGINE_H_
