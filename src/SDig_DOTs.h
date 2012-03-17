/******************************************************************************/
/*!
 * \file    SDig_DOTs.h
 * \brief   Declarations of data object type classes; derivated from the
 *          class SDig_BaseDOT.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

// FIXME: put DOTPlayer and DOTExit into a single file


#ifndef _SDIG_DOTS_H_
#define _SDIG_DOTS_H_

#if 0
namespace SDig {
    class DOTPlayer;
    class DOTExit;
}
#endif

#include "SDig_BaseDOT.h"
#include "SDig_DataObject.h"
//#include "ObjField/Field.h"

#include <string>

namespace SDig {

namespace ObjField {
    class Field;            // pre-declaration
}
}

using namespace std;




namespace SDig {


/*!
 * \class   DOTWall
 * \brief   Declaration of the data object type class: wall. 
 */
class DOTWall : public BaseDOT
{

public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTWall() {
        mName = string("Wall");
        setType(wall);
    }
};


/*!
 * \class   DOTSand
 * \brief   Declaration of the data object type class: sand.
 */
class DOTSand : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTSand() {
        mName = string("Sand");
        setType(sand);
    };
};


/*!
 * \class   DOTEmpty
 * \brief   Declaration of the data object type class: empty.
 */
class DOTEmpty : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTEmpty() {
        mName = string("Empty");
        setType(empty);
    };
};


/*!
 * \class   DOTStone 
 * \brief   Declaration of the data object type class: stone.
 */
class DOTStone : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTStone() {
        mName = string("Stone");
        setType(stone);
    };
};


/*!
 * \class   DOTPlayer
 * \brief   Declaration of the data object type class: player.
 * FIXME: use an own file
 * Don't delete the player object during the level engine is running, because its
 * member variables are used by the level engine.
 */
class DOTPlayer : public BaseDOT
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

private:
    ObjField::Field *mObjField; /*!< back-reference to the overlying object field
                                     to get access to its members/functions */
    DataObject  *mDataObject;   /*!< back-reference to the overlying data object */

    StateType   mState;     //!< player's state
    int         mCnt;       //!< counter value used for the exiting phases
    int         mSandCnt;   //!< counter for eaten sand

/* ======== class functions ======== */
public:
    /*!
     * \brief   Constructor
     * \details Define constant class attributes.
     */
    DOTPlayer()
    {
        mObjField = NULL;           // has to be set later
        mDataObject = NULL;

        mName = string("Player");
        setType(player);
        
        /* set local class members */
        setState(ST_ALIVE);
        mCnt = 0;
        mSandCnt = 0;
    };

    /*!
     *\brief    initialize references
     *
     *\param pObjField      back-reference to the object field
     *\param pDataObject    back-reference to the players data object
     *
     * This function has to be called before the player's object can be used.
     */
    void initReferences(ObjField::Field *pObjField, DataObject *pDataObject) {
        mObjField = pObjField;
        mDataObject = pDataObject;
    }
#if 0    
    /*!\brief   Set reference to the overlying object field */
    void setFieldReference(objField *pObjField) {
        mObjField = pObjField;
    }
    
    /*!\brief   Set reference to the overlying data object */
    void setDataObject(DataObject *pDataObject) {
        mDataObject = pDataObject;
    }
#endif    
    /*!\brief   Set reference to the overlying data object */
    DataObject *getDataObject(void) {
        return mDataObject;
    }


    /* ==== player's state functions ==== */
    
    /*!
     * \brief   Set players state.
     */
    void setState(StateType pState) {
        mState = pState;

        /* initialize new state variables */
        if (pState == ST_EXITING) {
            mCnt = 0;
        }
    }
   
    /*! \brief   Get players current state */ 
    StateType getState(void) {
        return mState;
    }

    /*!
     * \brief   Get state counter value
     * \details Some of the states have an additionally counter
     */
    int getStateCnt(void) {
        return mCnt;
    }

    /*!
     * \brief   Do one interration of the player's states.
     */
    void run(void)
    {
        switch (mState)
        {
            case ST_ALIVE:
                break;

            case ST_EXITING:
            {
                mCnt++;
                if (mCnt > 4) {
                    mState = ST_EXITED;
                }
                break;
            }

            case ST_EXITED:
                break;
        }
    }


    /* ==== player's sand counter functions ==== */
    
    /*! \brief   Get the number of eaten sand. */ 
    int getSandCnt(void) {
        return mSandCnt;
    }
    
    /*! \brief   Increment the sand counter. */ 
    void incrSandCnt(void) {
        mSandCnt++;
    }

    /*! \brief   Clear sand counter. */ 
    void clearSandCnt(void) {
        mSandCnt = 0;
    }

};


/*!
 * \class   DOTExit
 * \brief   Declaration of the data object type class: exit.
 * FIXME: use an own file
 * Don't delete the exit object during the level engine is running, because its
 * member variables are used by the level engine.
 */
class DOTExit : public BaseDOT
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
    ObjField::Field *mObjField; /*!<- back-reference to the overlying object field
                                      to get access to its members/functions */
    DataObject  *mDataObject;   /*!< back-reference to the overlying data object */

    StateType   mState;     //!< exit's state
    int         mSandReq;   //!< required sand to change the state to open


/* ======== class functions ======== */
public:
    /*!
     * \brief   Constructor
     * \details Define constant class attributes.
     */
    DOTExit() {
        mName = string("Exit");
        setType(exit);
    
        setState(ST_CLOSED);
    };

    /*!
     *\brief    initialize references
     *
     *\param pObjField      back-reference to the object field
     *\param pDataObject    back-reference to the exit's data object
     *
     * This function has to be called before the exit object can be used.
     */
    void initReferences(ObjField::Field *pObjField, DataObject *pDataObject) {
        mObjField = pObjField;
        mDataObject = pDataObject;
    }
#if 0    
    /*!\brief   Set reference to the overlying object field */
    void setFieldReference(objField *pObjField) {
        mObjField = pObjField;
    }
#endif
    /*!\brief   Set reference to the overlying data object */
    DataObject *getDataObject(void) {
        return mDataObject;
    }
    
    /* ==== exit's state functions ==== */
    

    /*! \brief  Set exit's state. */
    void setState(StateType pState) {
        mState = pState;
    }
    
    /*! \brief  Set exit's state to directly to open. */
    void openIt(void) {
        mState = ST_OPEN;
    }
    
    /*! \brief  Set exit's state to directly to close. */
    void closeIt(void) {
        mState = ST_CLOSED;
    }
   
    /*! \brief  Get exit's current state */ 
    StateType getState(void) {
        return mState;
    }
    
    /*!
     * \brief   Do one interration of the exit's states.
     */
    void run(void)
    {
        /* get sand */
        int sandEaten = 0;

        /* check if exit can be opened */
        if (sandEaten >= mSandReq) {
            mState = ST_OPEN;
        }

    }

    /* ==== exits's required sand functions ==== */
    
    /*! \brief   Get the value of required sand. */ 
    int getRequiredSand(void) {
        return mSandReq;
    }
    
    /*! \brief   Set the amount of required sand. */ 
    void setRequiredSand(int pSandReq) {
        mSandReq = pSandReq;
    }
};


}       // namespace

#endif
