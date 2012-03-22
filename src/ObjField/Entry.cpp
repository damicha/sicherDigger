/******************************************************************************/
/*!
 * \file    ObjField/Entry.cpp
 * \brief   Implementation of the ObjField::Entry class.
 * 
 * \author  damicha of defect
 * \date    2011-2012 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/


#include "ObjField/Entry.h"
#include "SDig_DataObject.h"

#include <string>
#include <sstream>
using namespace std;

using namespace SDig;
using namespace SDig::ObjField;

/*!
 * \brief  Create field entry's data object.
 * \param[in] pType Object type.
 */
void Entry::createDataObject(DOT::Type pType)
{
    mData = new DataObject(this, pType);
}

/*!
 * \brief  Delete field entry's data object.
 */
void Entry::deleteDataObject()
{
    if (mData != NULL) {
        delete mData;
    }
    mData = NULL;
}

/*!
 * \brief   Get the object content as a string
 */
string Entry::str()
{
    stringstream ss;
    ss << "<idx:" << strData() << ", " <<
          "type:" << getData()->getTypeObject()->getName() << ", " <<
          "neighbors: " << strNeighbors() << ">";
    return ss.str();
}


/*!
 * \brief   Get the content of an empty object as a string
 */
string Entry::strDataEmpty()
{
    return stringstream("[-, -]").str();
}


/*!
 * \brief   Get the object data as a string.
 */
string Entry::strData()
{
    stringstream ss;
    ss << "[" << mPosX << ", " << mPosY << "]";
    return ss.str();
}


/*!
 * \brief   Get the object data of the neighbors as a string
 */
string Entry::strNeighbors()
{
    stringstream ss;
    ss << "x--:" <<  ((mPrevX == NULL) ? strDataEmpty() : mPrevX->strData()) << ", " <<
          "x++:" <<  ((mNextX == NULL) ? strDataEmpty() : mNextX->strData()) << ", " <<
          "y--:" <<  ((mPrevY == NULL) ? strDataEmpty() : mPrevY->strData()) << ", " <<
          "y++:" <<  ((mNextY == NULL) ? strDataEmpty() : mNextY->strData());

    return ss.str();
}

