/*!
 * \file    baseDataObjectType.cpp
 * \brief   FIXME Virtual class to define the interface of the used data object types
 *  and to define the data object config class.
 * 
 * \author  damicha of defect
 * \date    2011 
 */

#include <string>
#include <stdio.h> 

#include "dataObjectTypes.h"
#include "baseDataObjectType.h"

using namespace std;

/*!
 * \brief   Create a data object type object as a function of its type.
 */
baseDataObjectType *baseDataObjectType::createDataObjectType(dataObjectType_t type)
{
    baseDataObjectType *t;
    switch(type)
    {
        case wall:  t = (dotWall  *)new dotWall();  break;
        case sand:  t = (dotSand  *)new dotSand();  break;
        case empty: t = (dotEmpty *)new dotEmpty(); break;
        case stone: t = (dotStone *)new dotStone(); break;
        case player:t = (dotStone *)new dotPlayer(); break;
        default:    t = new baseDataObjectType();   break;
    }
    return t;
};

/*!
 * \brief   Delete a data object type object
 */
void baseDataObjectType::deleteDataObjectType(baseDataObjectType *t)
{
    if (t != NULL) {
        delete t;
    }
};

