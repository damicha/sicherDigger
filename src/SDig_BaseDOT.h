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

using namespace std;


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
    

    /* a virtual destructor is not necessary, because there is nothing to
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

}       // namespace

#endif
