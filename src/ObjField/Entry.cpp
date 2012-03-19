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
 *\brief  create a data object
 */
void Entry::createDataObject(BaseDOT::DOTType type)
{
    mData = new DataObject(this, type);
}

void Entry::deleteDataObject()
{
    if (mData != NULL) {
        delete mData;
    }
    mData = NULL;
}

/* get the object content as a string */
string Entry::str()
{
    stringstream ss;
    ss << "<idx:" << strData() << ", " <<
          "type:" << getData()->getTypeObject()->getName() << ", " <<
          "neighbors: " << strNeighbors() << ">";
    return ss.str();
}


/* get the content of an empty object as a string*/
string Entry::strDataEmpty()
{
    return stringstream("[-, -]").str();
}


/* get the object data as a string */
string Entry::strData()
{
    stringstream ss;
    ss << "[" << mPosX << ", " << mPosY << "]";
    return ss.str();
}


/* get the object data of the neighbors as a string */
string Entry::strNeighbors()
{
    stringstream ss;
    ss << "x--:" <<  ((mPrevX == NULL) ? strDataEmpty() : mPrevX->strData()) << ", " <<
          "x++:" <<  ((mNextX == NULL) ? strDataEmpty() : mNextX->strData()) << ", " <<
          "y--:" <<  ((mPrevY == NULL) ? strDataEmpty() : mPrevY->strData()) << ", " <<
          "y++:" <<  ((mNextY == NULL) ? strDataEmpty() : mNextY->strData());

    return ss.str();
}

