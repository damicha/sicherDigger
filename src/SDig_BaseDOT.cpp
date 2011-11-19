/******************************************************************************/
/*!
 * \file    SDig_BaseDOT.cpp
 * \brief   Base class of the data object types (dot|DOT).
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "SDig_DOTs.h"
#include "SDig_BaseDOT.h"


using namespace std;
using namespace SDig;

/*!
 * \brief   Function to create a new DOT object as a function of its type.
 */
BaseDOT *BaseDOT::createDOT(DOTType pType)
{
    BaseDOT *t;
    switch(pType)
    {
        case wall:  t = new DOTWall();  break;
        case sand:  t = new DOTSand();  break;
        case empty: t = new DOTEmpty(); break;
        case stone: t = new DOTStone(); break;
        case player:t = new DOTPlayer(); break;
        // FIXME: give a note/message to the user, because the default case is not intended
        default:    t = new BaseDOT();   break;
    }
    return t;
};

/*!
 * \brief   Delete a DOT object
 */
void BaseDOT::deleteDOT(BaseDOT *pObj)
{
    if (pObj != NULL) {
        delete pObj;
    }
    pObj = NULL;
};



