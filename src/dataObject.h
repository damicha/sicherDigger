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

#ifndef _DATAOBJECT_H_
#define _DATAOBJECT_H_

#include "baseMaterial.h"
#include "materials.h"

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
    baseMaterial *type;  //!< object type FIXME: rename class baseMaterial to baseType
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
    dataObject(const baseMaterial::materialType_t objType = baseMaterial::unknown)
    {
        // FIXME use new materialXYZ() copied from objFieldEntry.h
        type = createMaterial(objType);
        done = 0;
    }
    
    /*!
     * \brief   Destructor
     */
    ~dataObject()
    {
        deleteMaterial(type);
    }

    baseMaterial *createMaterial(baseMaterialConfig::materialType_t type)
    {
        baseMaterial *t;

        switch(type)
        {
            case baseMaterialConfig::wall:  t = (materialWall  *)new materialWall();  break;
            case baseMaterialConfig::sand:  t = (materialSand  *)new materialSand();  break;
            case baseMaterialConfig::empty: t = (materialEmpty *)new materialEmpty(); break;
            case baseMaterialConfig::stone: t = (materialStone *)new materialStone(); break;
            default:                        t = new baseMaterial(); break;
        }

        return t;
    }

    void deleteMaterial(baseMaterial *t)
    {
        if (t != NULL) {
            delete t;
        }
    }


};


#endif
