/******************************************************************************/
/*!
 * \file    SDig_DataObject.h
 * \brief   Stores the properties and states of an data objects.
 * 
 * \author  damicha of defect
 * \date    2011-2012 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

// FIXME: add physics properties/states (create a class or add to baseType)

#ifndef _SDIG_DATA_OBJECT_H_
#define _SDIG_DATA_OBJECT_H_

#include "SDig_BaseDOT.h"

#include <stdio.h> 

using namespace std;

// pre-declare needed class
class objFieldEntry;

namespace SDig {

/*!
 * \class   DataObject
 * \brief   This class stores a type object and some properties.
 */
class DataObject
{

/* ======== class attributes ======== */
private:
    // FIXME: use class name objectType <- is a virtual class!
    BaseDOT *mType; //!< object type
    bool mDone;     /*!< true if material was already used by physics engine: 
                     * FIXME: move to a physics class (maybe)
                     * FIXME: use a own data type
                     * FIXME: don't use done. use blocked by current, next, prev ..
                     */
    objFieldEntry *mParentObj;  //!< back-reference to object field entry

/* ======== class initialisation functions ======== */
public:
    /*!\brief   Constructor */
    DataObject(objFieldEntry *pParentObj, const BaseDOT::DOTType pObjType = BaseDOT::unknown)
    {
        mType = BaseDOT::createDOT(pObjType);
        mDone = false;
        mParentObj = pParentObj;
    }
    
    /*!\brief   Destructor */
    ~DataObject()
    {
        BaseDOT::deleteDOT(mType);
        // FIXME: check if the reference has to be removed from the parent object
    }


    /*!\brief   Gets the type object */
    BaseDOT *getTypeObject(void) {
        return mType;
    }

    /*!\brief   Gets the type value from type object directly */
    BaseDOT::DOTType getType(void) {
        return mType->getType();
    }

    /*!\brief   Gets the reference to the parent object */
    objFieldEntry *getParentObject(void) {
        return mParentObj;
    }
    
    /*!\brief   Set a new reference to the parent object */
    void setParentObject(objFieldEntry *pParentObj) {
        mParentObj = pParentObj;
    }
    
    /*!\brief   Sets the done flag of this data object. */
    void setDone(void) {
        mDone = true;
    }

    /*!\brief   Clears the done flag of this data object. */
    void clearDone(void) {
        mDone = false;
    }

    /*!\brief   Checks the done state.
     * \return  Is true if the data object state is done. */
    bool isDone(void) {
        return mDone;
    }

};


}       // namespace


#endif
