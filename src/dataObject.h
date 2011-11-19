/******************************************************************************/
/*!
 * \file    dataObject.h
 * \brief   Class that includes data to define the type and the property of an
 *          object.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

// FIXME: add physics properties/states (create a class or add to baseType)

#ifndef _DATA_OBJECT_H_
#define _DATA_OBJECT_H_

#include "SDig_BaseDOT.h"

#include <stdio.h> 

using namespace std;
using namespace SDig;

/*
 * \class dataObject
 */
class dataObject
{

/* ======== class attributes ======== */
private:
public:
    // FIXME: use class name objectType <- is a virtual class!
    BaseDOT *type;   //!< object type FIXME: rename class baseMaterial to baseType
    int done;       /*!< 1 if material was already used by physics engine: 
                     * FIXME: move to a physics class (maybe)
                     * FIXME: use a own data type
                     * FIXME: don't use done. use blocked by current, next, prev ..
                     */

/* ======== class initialisation functions ======== */
public:
    /*!
     * \brief   Constructor
     */
    dataObject(const BaseDOT::DOTType objType = BaseDOT::unknown)
    {
        type = BaseDOT::createDOT(objType);
        done = 0;
    }
    
    /*!
     * \brief   Destructor
     */
    ~dataObject()
    {
        delete type;
    }
};


#endif
