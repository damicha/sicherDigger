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

#ifndef _SDIG_DOTS_H_
#define _SDIG_DOTS_H_

#include "SDig_BaseDOT.h"

#include <string>


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
//        printf("%s: %s\n", __func__, getName().c_str());
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
 */
class DOTPlayer : public BaseDOT
{
/* ======== class types ======== */
public:
    /*!
     * State of the player.
     */
    enum StateType {
        ST_ALIVE,           //!< still alive
        ST_EXITING,         //!< is entering the exit
        ST_EXITED           //!< entered the exit
    };

private:
    StateType   mState;     //!< player's state: FIXME: use it instead of mExiting
    int         mCnt;       //!< counter value used for the exiting phases
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTPlayer()
    {
        mName = string("Player");
        setType(player);
        
        /* set local class members */
        setState(ST_ALIVE);
        mCnt = 0;
    };

    void setState(StateType pState) {
        mState = pState;

        /* initialize new states */
        if (pState == ST_EXITING) {
            mCnt = 0;
        }
    }
    
    StateType getState(void) {
        return mState;
    }

    void run(void)
    {
        switch (mState)
        {
            case ST_ALIVE:
                break;

            case ST_EXITING:
                mCnt++;
                if (mCnt > 4) {
                    mState = ST_EXITED;
                }
                break;

            case ST_EXITED:
                break;
        }
    }

    int getStateCnt(void) {
        return mCnt;
    }

};


/*!
 * \class   DOTExit
 * \brief   Declaration of the data object type class: exit.
 */
class DOTExit : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTExit() {
        mName = string("Exit");
        setType(exit);
    };
};


}       // namespace

#endif
