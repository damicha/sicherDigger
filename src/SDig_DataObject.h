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

#include "DOT/Base.h"

#include <stdio.h> 

using namespace std;

// pre-declarations
namespace SDig {
    class DataObject;
namespace ObjField {
    class Entry;
}
}



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
    DOT::Base   *mType; //!< object type
    bool        mDone;  /*!< true if material was already used by physics engine: 
                         * FIXME: move to a physics class (maybe)
                         * FIXME: use a own data type
                         * FIXME: don't use done. use blocked by current, next, prev ..
                         */
    ObjField::Entry *mParentObj;    //!< back-reference to object field entry

/* ======== class initialisation functions ======== */
public:
    /*!\brief   Constructor */
    DataObject(ObjField::Entry *pParentObj,
               const DOT::Type pObjType = DOT::T_UNKNOWN)
    {
        mType = DOT::Base::createDOT(pObjType);
        mDone = false;
        mParentObj = pParentObj;
    }
    
    /*!\brief   Destructor */
    ~DataObject()
    {
        DOT::Base::deleteDOT(mType);
        // FIXME: check if the reference has to be removed from the parent object
    }


    /*!\brief   Gets the type object */
    DOT::Base *getTypeObject(void) {
        return mType;
    }

    /*!\brief   Gets the type value from type object directly */
    DOT::Type getType(void) {
        return mType->getType();
    }

    /*!\brief   Gets the reference to the parent object */
    ObjField::Entry *getParentObject(void) {
        return mParentObj;
    }
    
    /*!\brief   Set a new reference to the parent object */
    void setParentObject(ObjField::Entry *pParentObj) {
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

    /* Swap data objects. */
    static void swapDataObjects(ObjField::Entry *pSrc, ObjField::Entry *pDest);
};


}       // namespace


#endif
