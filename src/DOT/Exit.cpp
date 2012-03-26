/******************************************************************************/
/*!
 * \file    DOT/Exit.cpp
 * \brief   Function implementation of data object type DOT::Exit.
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


/* ==== exit's init functions ==== */

/*!
 * \brief   Constructor
 * \details Define constant class attributes.
 */
Exit::Exit() {
    mName = string("Exit");
    setType(T_EXIT);

    setState(ST_CLOSED);
};


/* ==== exit's state functions ==== */

/*!\brief  Set exit's state. */
void Exit::setState(StateType pState) {
    mState = pState;
}

/*!\brief  Set exit's state to directly to open. */
void Exit::openIt(void) {
    mState = ST_OPEN;
}

/*!\brief  Set exit's state to directly to close. */
void Exit::closeIt(void) {
    mState = ST_CLOSED;
}

/*!\brief  Get exit's current state */ 
Exit::StateType Exit::getState(void) const {
    return mState;
}

/*!
 * \brief   Do one interration of the exit's states.
 */
void Exit::run(void)
{
    /* get sand */
    int sandEaten = 0;

    /* check if exit can be opened */
    if (sandEaten >= mSandReq) {
        mState = ST_OPEN;
    }

}

/* ==== exits's required sand functions ==== */

/*!\brief   Get the value of required sand. */ 
int Exit::getRequiredSand(void) const {
    return mSandReq;
}

/*!\brief   Set the amount of required sand. */ 
void Exit::setRequiredSand(int pSandReq) {
    mSandReq = pSandReq;
}
