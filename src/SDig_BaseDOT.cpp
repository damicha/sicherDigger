/******************************************************************************/
/*!
 * \file    SDig_BaseDOT.cpp
 * \brief   Base class of the data object types (dot).
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "dataObjectTypes.h"
#include "SDig_BaseDOT.h"


using namespace std;

/*!
 * \brief   Function to create a new DOT object as a function of its type.
 */
BaseDOT *SDig::BaseDOT::createDOT(DOTType pType)
{
    BaseDOT *t;
    switch(pType)
    {
        case wall:  t = (dotWall  *)new dotWall();  break;
        case sand:  t = (dotSand  *)new dotSand();  break;
        case empty: t = (dotEmpty *)new dotEmpty(); break;
        case stone: t = (dotStone *)new dotStone(); break;
        case player:t = (dotStone *)new dotPlayer(); break;
        // FIXME: give a note/message to the user, because the default case is not intended
        default:    t = new BaseDOT();   break;
    }
    return t;
};

/*!
 * \brief   Delete a DOT object
 */
void SDig::BaseDOT::deleteDOT(BaseDOT *pObj)
{
    if (pObj != NULL) {
        delete pObj;
    }
    pObj = NULL;
};



