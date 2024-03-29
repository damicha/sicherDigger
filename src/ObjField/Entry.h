/******************************************************************************/
/*!
 * \file    ObjField/Entry.h
 * \brief   Declaration of the ObjField::Entry class.
 * 
 * \author  damicha of defect
 * \date    2011-2012 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _OBJFIELD_ENTRY_H_
#define _OBJFIELD_ENTRY_H_

#include "DOT/Base.h"
#include "SDig_DataObject.h"

#include <stdio.h>
#include <string>
#include <sstream>


namespace SDig {
namespace ObjField {

class Entry;

/*!
 *\brief    Objects of this class are used in the entry array of ObjField::Field.
 */
class Entry
{
/* ======== class attributes ======== */
private:
    /* neighbor objects */
    Entry   *mPrevX, *mNextX;   //!< objects on the left and right side of this one
    Entry   *mPrevY, *mNextY;   //!< objects that are lying above and below this one
    /* position in field */
    int     mPosX;              //!< entrie's X position in the field
    int     mPosY;              //!< entrie's Y position in the field
    /* data object */
    SDig::DataObject *mData;    //!< Data field that contains properties and states

/* ======== class init functions ======== */
public:
    /*!\brief Constructor */
    Entry() :
        mPrevX(NULL), mNextX(NULL),
        mPrevY(NULL), mNextY(NULL),
        mPosX(-1), mPosY(-1),
        mData(NULL)
    {};


    /*  create a data object */
    // FIXME: move to data object?
    // FIXME: -> make it static
    void createDataObject(DOT::Type pType);

    /*  delete a data object */
    void deleteDataObject();

/* ======== class set/get functions ======== */
public:
    /*!
     * \brief   Set entry's field position
     * \param[in] pPosX x coordinate.
     * \param[in] pPosY y coordinate.
     */
    void setPosition(int pPosX, int pPosY) {
        mPosX = pPosX;
        mPosY = pPosY;
    }

    /*!\brief   Set pointer of the entry that lies on the left side of this entry. */
    void setPrevX(Entry *pPrevX) {
        mPrevX = pPrevX;
    }
    /*!\brief   Set pointer of the entry that lies on the right side of this entry. */
    void setNextX(Entry *pNextX) {
        mNextX = pNextX;
    }
    /*!\brief   Set pointer of the entry that lies below this entry. */
    void setPrevY(Entry *pPrevY) {
        mPrevY = pPrevY;
    }
    /*!\brief   Set pointer of the entry that lies above this entry. */
    void setNextY(Entry *pNextY) {
        mNextY = pNextY;
    }
    
    /*!\brief   Get pointer of the entry that lies on the left side of this entry. */
    Entry *getPrevX(void) const {
        return mPrevX;
    }
    /*!\brief   Get pointer of the entry that lies on the right side of this entry. */
    Entry *getNextX(void) const {
        return mNextX;
    }
    /*!\brief   Get pointer of the entry that lies below this entry. */
    Entry *getPrevY(void) const {
        return mPrevY;
    }
    /*!\brief   Get pointer of the entry that lies above this entry. */
    Entry *getNextY(void) const {
        return mNextY;
    }

    /*!\brief   Set pointer to the data object. */
    void setData(SDig::DataObject *pData) {
        mData = pData;
    }
    /*!\brief   Get pointer to the data object. */
    SDig::DataObject *getData(void) {
        return mData;
    }

/* ======== class string functions ======== */
    /* get the object content as a string */
    string str();
    /* get the content of an empty object as a string*/
    string strDataEmpty();
    /* get the object data as a string */
    string strData();
    /* get the object data of the neighbors as a string */
    string strNeighbors();
};


}       // namespace ObjField
}       // namespace SDig


#endif
