/******************************************************************************/
/*!
 * \file    dataObject.h
 * \brief   Class that includes data to define the type and the property of an
 *          object.
 * 
 * \author  damicha of defect
 * \date    2011 
 ******************************************************************************/

// FIXME: add physics properties/states (create a class or add to baseType)

#ifndef _DATA_OBJECT_H_
#define _DATA_OBJECT_H_

#include "baseDataObjectType.h"
#include "dataObjectTypes.h"

#include <stdio.h> 

using namespace std;

/*
 * \class dataObject
 */
class dataObject
{

/* ======== class attributes ======== */
private:
public:
    // FIXME: use class name objectType <- is a virtual class!
    baseDataObjectType *type;   //!< object type FIXME: rename class baseMaterial to baseType
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
    dataObject(const baseDataObjectType::dataObjectType_t objType = baseDataObjectType::unknown)
    {
        // FIXME use new materialXYZ() copied from objFieldEntry.h
        type = createDataObjectType(objType);
        done = 0;
    }
    
    /*!
     * \brief   Destructor
     */
    ~dataObject()
    {
        deleteDataObjectType(type);
    }

    // FIXME move to baseDataObjectType
    baseDataObjectType *createDataObjectType(baseDataObjectType::dataObjectType_t type)
    {
        baseDataObjectType *t;

        switch(type)
        {
            case baseDataObjectType::wall:  t = (dotWall  *)new dotWall();  break;
            case baseDataObjectType::sand:  t = (dotSand  *)new dotSand();  break;
            case baseDataObjectType::empty: t = (dotEmpty *)new dotEmpty(); break;
            case baseDataObjectType::stone: t = (dotStone *)new dotStone(); break;
            default:                        t = new baseDataObjectType(); break;
        }

        return t;
    }

    void deleteDataObjectType(baseDataObjectType *t)
    {
        if (t != NULL) {
            delete t;
        }
    }


};


#endif
