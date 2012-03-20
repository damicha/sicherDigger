/******************************************************************************/
/*!
 * \file    SDig_BaseDOT.h
 * \brief   Base class of the data object types (dot|DOT).
 *
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_BASE_DOT_H_
#define _SDIG_BASE_DOT_H_

#include <string>
#include <stdio.h> 

//#include "SDig_DataObject.h"

using namespace std;

/* pre-declarations */
namespace SDig {
    class DataObject;
namespace ObjField {
    class Entry;
    class Field;
}
}

namespace SDig {

/*!
 * \class   BaseDOT
 * \brief   Base class of the data object types (dot|DOT).
 * 
 * This class implements an interface and some functions to support
 * its derived classes like SDig::dotStone.
 */
class BaseDOT
{
/* ======== class datatypes ======== */    
public:
    /*!
     * \enum    DOTType
     * \brief   Supported data object types.
     *
     * This enum is used to identify the derived classes.
     */
    enum DOTType {
        empty,
        sand,
        wall,
        stone,
        player,
        exit,
        unknown
    };


/* ======== class attributes ======== */
protected:
    DOTType mType;  //!< data type
    string  mName;  //!< data type name (FIXME: remove)

public:
    /*!
     * \brief   Default constructor
     * \details Set default values to the attributes of this base class.
     */
    BaseDOT() : mType(unknown), mName("unknown") {}
    

    /* A destructor is not necessary, because there is nothing to
       destroy in this base class */


    /* Create a new DOT object as a function of its type. */
    static BaseDOT *createDOT(DOTType pType);

    /* Delete a DOT object */
    static void deleteDOT(BaseDOT *pObj);



/* ======== class type/string functions ======== */
public:

    /*!
     * \brief   Set the data object type.
     * \param pType
     *          Type of the data object.
     */
    void setType(DOTType pType) {
        mType = pType;
    }
    /*!
     * \brief   Get the type of an DOT object.
     * \return  Data object type of the class.
     */
    DOTType getType() {
        return mType;
    }
    
    
    /*!
     * \brief   Get the objects name.
     * \return  Name as a string object.
     */
    string getName() {
        return mName;
    }
    
};

/*!
 * \class   Base2DOT
 * \brief   Base class type 2 of enhanced data object types (dot|DOT).
 * 
 * This class implements an additional interface and functions to support
 * its derived classes like SDig::dotPlayer.
 */
class Base2DOT : public BaseDOT
{
/* ======== class members ======== */
private:
    ObjField::Field *mObjField; /*!< back-reference to the overlying object field
                                     to get access to its members/functions */
    DataObject  *mDataObject;   /*!< back-reference to the overlying data object */

public:
    /*!
     * \brief   Default constructor
     * \details Set default values to the attributes of this base class.
     */
    Base2DOT() {
        mObjField = NULL;           // has to be set later
        mDataObject = NULL;
    }


    /* A destructor is not necessary, because there is nothing to
       destroy in this base class */

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
    
    /*!\brief   Set reference to the overlying data object */
    DataObject *getDataObject(void) const {
        return mDataObject;
    }

    /* Get the overlying field entry of the data object of this object */
    ObjField::Entry *getFieldEntry(void) const;
    
    /*!\brief   run function to proceed with internal states. */
    virtual void run(void) = 0;

};

}       // namespace

#endif
