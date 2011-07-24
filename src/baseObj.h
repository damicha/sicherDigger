/* file: baseObj.h */

#ifndef _BASEOBJ_H_
#define _BASEOBJ_H_

#include "baseMaterial.h"
#include "materials.h"

#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

class baseObj;

/*
 * baseObj
 */
class baseObj
{
public:

#if 0
    /* define object types */
    typedef enum
    {
        empty,
        sand,
        wall,
        stone,
        unknown
    } objType_t; 
#endif

    /*
     * object data
     */
public:
    /* neighbor objects */
    baseObj *x_prev, *x_next;
    baseObj *y_prev, *y_next;
    /* position in field */
    int pos_x, pos_y;
    /* object type */
#if 0
    objType_t type;
#endif
    // FIXME: add object layer: (baseObj.obj: obj.m, obj...)
    baseMaterial *m;    /*!< the object material. A virtual class is used */

public:
    /* constructor */
    baseObj() : pos_x(-1), pos_y(-1), // type(unknown),
                x_prev(NULL), x_next(NULL),
                y_prev(NULL), y_next(NULL) {};

    /*! \brief  create a material object
     *  \todo   use copy contructor
     */
    baseMaterial *createMaterial(baseMaterialConfig::materialType_t type)
    {
        switch(type)
        {
            case baseMaterialConfig::wall:  m = (materialWall  *)new materialWall();  break;
            case baseMaterialConfig::sand:  m = (materialSand  *)new materialSand();  break;
            case baseMaterialConfig::empty: m = (materialEmpty *)new materialEmpty(); break;
            case baseMaterialConfig::stone: m = (materialStone *)new materialStone(); break;
        }

        return m;
    }

    void deleteMaterial()
    {
        if (m != NULL) {
            delete m;
        }
    }

    /*
     * functions to get the object data as a string 
     */

    /* get the object content as a string */
    string str();
    /* get the content of an empty object as a string*/
    string strDataEmpty();
    /* get the object data as a string */
    string strData();
    /* get the object data of the neighbors as a string */
    string strNeighbors();
#if 0
    /* get the type as a string */
    string strType();
    /* get the type as a short string */
    string strTypeShort();
#endif
};


#endif
