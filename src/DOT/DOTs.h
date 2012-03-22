/******************************************************************************/
/*!
 * \file    DOT/DOTs.h
 * \brief   Declarations of data object type classes derived from
 *  class DOT::Base.
 * 
 * \author  damicha of defect
 * \date    2011-2012 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_DOTS_H_
#define _SDIG_DOTS_H_

#include "Base.h"

#include <string>

namespace SDig {
namespace ObjField {
    class Field;            // pre-declaration
}
}

using namespace std;



namespace SDig {
namespace DOT {

/*!
 * \brief   Declaration of the data object type class: wall. 
 */
class Wall : public Base
{

public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    Wall() {
        mName = string("Wall");
        setType(T_WALL);
    }
};


/*!
 * \brief   Declaration of the data object type class: sand.
 */
class Sand : public DOT::Base
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    Sand() {
        mName = string("Sand");
        setType(T_SAND);
    };
};


/*!
 * \brief   Declaration of the data object type class: empty.
 */
class Empty : public DOT::Base
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    Empty() {
        mName = string("Empty");
        setType(T_EMPTY);
    };
};


/*!
 * \brief   Declaration of the data object type class: stone.
 */
class Stone : public DOT::Base
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    Stone() {
        mName = string("Stone");
        setType(T_STONE);
    };
};


/*!
 * \brief   Declaration of the data object type class: player.
 * 
 * Don't delete the player object during the level engine is running, because its
 * member variables are used by the level engine.
 */
class Player : public DOT::Base2
{
/* ======== class types ======== */
public:
    /*!
     * States of the player.
     */
    enum StateType {
        ST_ALIVE,           //!< still alive
        ST_EXITING,         //!< is entering the exit
        ST_EXITED           //!< entered the exit
    };

/* ======== class members ======== */
private:
    StateType   mState;     //!< player's state
    int         mCnt;       //!< counter value used for the exiting phases
    int         mSandCnt;   //!< counter for eaten sand

/* ======== class functions ======== */
public:
    
    /* ==== player's init functions ==== */
    
    /* Constructor */
    Player();


    /* ==== player's state functions ==== */
    
    /* Set players state. */
    void setState(StateType pState);

    /* Get players current state */ 
    StateType getState(void) const;

    /* Get state counter value. */
    int getStateCnt(void) const;

    /*  Do one iteration of the player's states. */
    void run(void);


    /* ==== player's sand counter functions ==== */
    
    /* Get the number of eaten sand. */ 
    int getSandCnt(void) const;
    
    /* Increment the sand counter. */ 
    void incrSandCnt(void);

    /* Clear sand counter. */ 
    void clearSandCnt(void);

};


/*!
 * \brief   Declaration of the data object type class: exit.
 *
 * Don't delete the exit object during the level engine is running, because its
 * member variables are used by the level engine.
 */
class Exit : public DOT::Base2
{
/* ======== class types ======== */
public:
    /*!
     * States of the Exit.
     */
    enum StateType {
        ST_CLOSED,      //!< exit it closed (not enterable)
        ST_OPEN         //!< exit is open (enterable)
    };

/* ======== class members ======== */
private:
    StateType   mState;     //!< exit's state
    int         mSandReq;   //!< required sand to change the state to open


/* ======== class functions ======== */
public:
    
    /* ==== exit's init functions ==== */
    
    /* Constructor */
    Exit();
    
    
    /* ==== exit's state functions ==== */

    /* Set exit's state. */
    void setState(StateType pState);
    
    /* Set exit's state to directly to open. */
    void openIt(void);
    
    /* Set exit's state to directly to close. */
    void closeIt(void);
   
    /* Get exit's current state */ 
    StateType getState(void) const;
    
    /* Do one iteration of the exit's states. */
    void run(void);


    /* ==== exit's required sand functions ==== */
    
    /* Get the value of required sand. */ 
    int getRequiredSand(void) const;
    
    /* Set the amount of required sand. */ 
    void setRequiredSand(int pSandReq);
};


}       // namespace DOT
}       // namespace SDig

#endif
