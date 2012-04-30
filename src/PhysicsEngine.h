/*! ****************************************************************************
 *
 * \file    PhysicsEngine.h
 * \brief   Class definition of the physics engine
 *
 * \author  damicha of defect
 * \date    2011-2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/


#ifndef _SDIG_PHYSICS_ENGINE_H_
#define _SDIG_PHYSICS_ENGINE_H_

#include "ObjField/Field.h"
#include "ObjField/Entry.h"

#include "stdio.h"

using namespace std;


namespace SDig {

/*!
 * \class   PhysicsEngine
 * \brief   Implements the object physics like stones are falling, stones are
 *          lying on walls or sand, the player can move and eat sand, etc.
 */
class PhysicsEngine
{
/* ======== class types ======== */    
public:
    /*!
     * \brief   Object movement type. Used for player movement
     */
    enum MovementType {
        MT_LEFT,        //!< move to left
        MT_RIGHT,       //!< move to right
        MT_UP,          //!< move up
        MT_DOWN,        //!< move down
        MT_NONE         //!< do not move
    };

/* ======== class attributes ======== */    
private:
    int     mIterNum;       //!< The number of proceeded iterations.
    int     mTimerCnt;      //!< timer's counter value (decreasing)
    bool    mTimerEnable;   //!< Enables or disables the timer.

/* ======== functions ======== */    

public:
    /*!\brief  Constructor */
    PhysicsEngine() {
        resetIterNum();
        mTimerCnt       = 0;
        mTimerEnable    = false;
    }

    /*!\brief  Set the start value.
     * \param[in]   pTimerCnt   Timer value to set. 
     * FIXME: use level config */
    void init(int pTimerCnt) {
        resetIterNum();
        setTimerCnt(pTimerCnt);
        enableTimer();
    }
    
    /*!\brief  Configure time counter. */
    void setTimerCnt(int pTimerCnt) {
        mTimerCnt = pTimerCnt;
    }

    /*!\brief  Get current time counter value.
     * \return Time counter value. */
    int getTimerCnt(void) const {
        return mTimerCnt;
    }
    
    /*!\brief  Enable time counter. */
    void enableTimer(void) {
        mTimerEnable = true;
    }
    /*!\brief  Disable time counter. */
    void disableTimer(void) {
        mTimerEnable = false;
    }

    /*!\brief  Reset the number of iterations. */
    void resetIterNum(void) {
        mIterNum = 0;
    }

    /*!\brief  Get the number of iterations since last reset.
     * \return  Number of done iterations. */
    int getIterNum(void) {
        return mIterNum;
    }

    /* Do one iteration on the object field. */
    bool run(ObjField::Field *pField, MovementType pPlayerMove);

    /* Stone physics */
    void runStonePhysics(ObjField::Entry *e);
    
    /* Player physics */
    bool runPlayerPhysics(ObjField::Entry *e, MovementType pPlayerMove);

    /* Move player's data object */
    bool movePlayer(ObjField::Entry  *pPlayerObj, ObjField::Entry *pDestObj);

    /* Check if this object has the type empty. */
    bool isEmpty(ObjField::Entry *pEntry);
    
    /* Check if this object has the type sand. */
    bool isSand(ObjField::Entry *pEntry);
    
    /* Check if this object has the type exit. */
    bool isExit(ObjField::Entry *pEntry);
    
    /* Check if the it's and closed exit. */
    bool isClosedExit(ObjField::Entry *pEntry);

    /* Check if this object is able to block others. */
    bool isBlocking(ObjField::Entry *pEntry);

};

}       // namespace SDig

#endif // _SDIG_PHYSICS_ENGINE_H_
