/******************************************************************************/
/*!
 * \file    SDig_DataObject.h
 * \brief   Stores the properties and states of an data objects.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

// FIXME: add physics properties/states (create a class or add to baseType)
// FIXME: member should be private

#ifndef _SDIG_DATA_OBJECT_H_
#define _SDIG_DATA_OBJECT_H_

#include "SDig_BaseDOT.h"

#include <stdio.h> 

using namespace std;


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
    BaseDOT *mType;   //!< object type FIXME: rename class baseMaterial to baseType
    bool mDone;      /*!< true if material was already used by physics engine: 
                     * FIXME: move to a physics class (maybe)
                     * FIXME: use a own data type
                     * FIXME: don't use done. use blocked by current, next, prev ..
                     */

/* ======== class initialisation functions ======== */
public:
    /*!
     * \brief   Constructor
     */
    DataObject(const BaseDOT::DOTType pObjType = BaseDOT::unknown)
    {
        mType = BaseDOT::createDOT(pObjType);
        mDone = false;
    }
    
    /*!
     * \brief   Destructor
     */
    ~DataObject()
    {
        BaseDOT::deleteDOT(mType);
    }


    /*!
     * \brief   Gets the type object
     */
    // FIXME: return with a reference ?
    BaseDOT *getTypeObject(void) {
        return mType;
    }

    /*!
     * \brief   Gets the type value from type object directly
     */
    BaseDOT::DOTType getType(void) {
        return mType->getType();
    }

    /*!
     * \brief   Sets the done flag of this data object.
     */
    void setDone(void) {
        mDone = true;
    }

    /*!
     * \brief   Clears the done flag of this data object.
     */
    void clearDone(void) {
        mDone = false;
    }

    /*!
     * \brief   Checks the done state.
     * \return  Is true if the data object state is done.
     */
    bool isDone(void) {
        return mDone;
    }

};


}       // namespace


#endif