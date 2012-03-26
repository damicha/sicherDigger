/******************************************************************************/
/*!
 * \file    SDig_DataObject.cpp
 * \brief   Stores the properties and states of an data objects.
 * 
 * \author  damicha of defect
 * \date    2012 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "SDig_DataObject.h"
#include "ObjField/Entry.h"


using namespace SDig;

/*!
 * \brief   Swap the data objects of the given entries.
 */
void DataObject::swapDataObjects(ObjField::Entry *pEntryA, ObjField::Entry *pEntryB)
{
    DataObject  *doA    = pEntryA->getData();
    DataObject  *doB    = pEntryB->getData();
    
    /* swap references and back-references */
    pEntryA->setData(doB);
    doB->setParentObject(pEntryA);
    
    pEntryB->setData(doA);
    doA->setParentObject(pEntryB);
}


