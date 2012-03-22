/******************************************************************************/
/*!
 * \file    DOT/Base.cpp
 * \brief   Function implementations of the data object type (dot|DOT)
 *  base classes DOT::Base and DOT::Base2.
 * 
 * \author  damicha of defect
 * \date    2011-2012 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "DOT/DOTs.h"
#include "DOT/Base.h"
#include "SDig_DataObject.h"


using namespace std;
using namespace SDig;
using namespace DOT;

/*!
 * \brief   Create a new DOT object as a function of its type.
 * \param[in] pType Type of the DOT object to create.
 */
Base *DOT::Base::createDOT(DOT::Type pType)
{
    Base *t;
    switch(pType)
    {
        case T_WALL:    t = new DOT::Wall();    break;
        case T_SAND:    t = new DOT::Sand();    break;
        case T_EMPTY:   t = new DOT::Empty();   break;
        case T_STONE:   t = new DOT::Stone();   break;
        case T_PLAYER:  t = new DOT::Player();  break;
        case T_EXIT:    t = new DOT::Exit();    break;
        // FIXME: give a note/message to the user, because the default case is
        // not intended to be used:
        // FIXME: remove the unknown type?
        default:        t = new DOT::Base();    break;
    }
    return t;
};

/*!
 * \brief   Delete a DOT object
 * \param[in] pObj  Delete an DOT object.
 */
void DOT::Base::deleteDOT(DOT::Base *pObj)
{
    if (pObj != NULL) {
        delete pObj;
    }
    pObj = NULL;
};


/*!
 * \brief   Get the overlying field entry of the data object of this DOT object.
 * \return  The field entry that contains the data object of this DOT object.
 */
ObjField::Entry *DOT::Base2::getFieldEntry(void) const {
    return mDataObject->getParentObject();
};

