/******************************************************************************/
/*!
 * \file    DOT/Base.h
 * \brief   Declarations of the data object type (dot|DOT) base classes DOT::Base
 *  and DOT::Base2.
 *
 * \author  damicha of defect
 * \date    2011-2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_DOT_BASE_H_
#define _SDIG_DOT_BASE_H_

#include <string>
#include <stdio.h> 


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
 *\brief    This namespace includes data object type classes like DOT::Wall
 *  and DOT::Player.
 */
namespace DOT {

/*!
 * \enum    DOT::Type
 * \brief   Supported data object types.
 *
 * This enum is used to identify the derived classes.
 */
enum Type {
    T_EMPTY,
    T_SAND,
    T_WALL,
    T_STONE,
    T_PLAYER,
    T_EXIT,
    T_UNKNOWN
};


/*!
 * \brief   Base class of the data object types (dot|DOT).
 * 
 * This class implements an interface and some functions to support
 * its derived classes like DOT::Stone.
 */
class Base
{
/* ======== class datatypes ======== */    
public:


/* ======== class attributes ======== */
protected:
    Type    mType;  //!< data type
    string  mName;  //!< data type name (FIXME: remove)

public:
    /*!
     * \brief   Default constructor
     * \details Set default values to the attributes of this base class.
     */
    Base() : mType(T_UNKNOWN), mName("unknown") {}
    

    /* A destructor is not necessary, because there is nothing to
       destroy in this base class */


    /* Create a new DOT object as a function of its type. */
    static Base *createDOT(DOT::Type pType);

    /* Delete a DOT object */
    static void deleteDOT(Base *pObj);



/* ======== class type/string functions ======== */
public:

    /*!
     * \brief   Set the data object type.
     * \param[in] pType     Type of the data object.
     */
    void setType(Type pType) {
        mType = pType;
    }
    /*!
     * \brief   Get the type of an DOT object.
     * \return  Data object type of the class.
     */
    Type getType() const {
        return mType;
    }
    
    
    /*!
     * \brief   Get the objects name.
     * \return  Name as a string object.
     */
    string getName() const {
        return mName;
    }
    
};

/*!
 * \brief   Base class type 2 of enhanced data object types (dot|DOT).
 * 
 * This class implements an additional interface and functions to support
 * its derived classes like DOT::Player.
 */
class Base2 : public Base
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
    Base2() {
        mObjField = NULL;           // has to be set later
        mDataObject = NULL;
    }


    /* A destructor is not necessary, because there is nothing to
       destroy in this base class */

    /*!
     * \brief    initialize references
     *
     * \param[in] pObjField     back-reference to the object field
     * \param[in] pDataObject   back-reference to the players data object
     *
     * This function has to be called before the player's object can be used.
     */
    void initReferences(ObjField::Field *pObjField, DataObject *pDataObject) {
        mObjField = pObjField;
        mDataObject = pDataObject;
    }
    
    /*!
     * \brief   Get the reference of the overlying data object
     * \return  The overlying data object.
     */
    DataObject *getDataObject(void) const {
        return mDataObject;
    }

    /* Get the overlying field entry of the data object of this DOT object. */
    ObjField::Entry *getFieldEntry(void) const;
    
    /*!\brief   run function to proceed with internal states. */
    virtual void run(void) = 0;

};

}       // namespace DOT
}       // namespace SDig

#endif
