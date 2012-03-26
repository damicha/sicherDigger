/******************************************************************************/
/*!
 * \file    DOT/Player.cpp
 * \brief   Function implementation of data object type DOT::Player.
 * 
 * \author  damicha of defect
 * \date    2011-2012 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "Base.h"
#include "DOTs.h"

#include <string>

using namespace std;
using namespace SDig;
using namespace DOT;



/* ==== player's init functions ==== */

/*!
 * \brief   Constructor
 * \details Define constant class attributes.
 */
Player::Player()
{
    mName = string("Player");
    setType(T_PLAYER);
    
    /* set local class members */
    setState(ST_ALIVE);
    mCnt = 0;
    mSandCnt = 0;
};


/* ==== player's state functions ==== */

/*!
 * \brief   Set player's state.
 * \param[in]   pState State to set.
 */
void Player::setState(StateType pState) {
    mState = pState;

    /* initialize new state variables */
    if (pState == ST_EXITING) {
        mCnt = 0;
    }
}

/*!
 * \brief   Get players current state
 * \return  Players state.
 */ 
Player::StateType Player::getState(void) const {
    return mState;
}

/*!
 * \brief   Get state counter value
 * \details The state EXITING uses this counter.
 */
int Player::getStateCnt(void) const {
    return mCnt;
}

/*!
 * \brief   Do one iteration of the player's states.
 */
void Player::run(void)
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

/*!
 * \brief   Get the number of eaten sand.
 * \return  Amount of sand that the player has already eaten.
 */ 
int Player::getSandCnt(void) const {
    return mSandCnt;
}

/*!\brief   Increment the sand counter. */ 
void Player::incrSandCnt(void) {
    mSandCnt++;
}

/*!\brief   Clear sand counter. */ 
void Player::clearSandCnt(void) {
    mSandCnt = 0;
}

