/* file: objFieldEntry.h */

#ifndef _OBJFIELDENTRY_H_
#define _OBJFIELDENTRY_H_

#include "baseMaterial.h"
#include "materials.h"
#include "dataObject.h"

#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

class objFieldEntry;

/*
 * objFieldEntry
 */
class objFieldEntry
{
public:

    /*
     * object data
     */
public:
    /* neighbor objects */
    objFieldEntry *x_prev, *x_next;
    objFieldEntry *y_prev, *y_next;
    /* position in field */
    int pos_x, pos_y;
#if 0
    // FIXME: add object layer: (objFieldEntry.obj: obj.m, obj...)
    baseMaterial *m;    /*!< the object material. A virtual class is used */
#endif
    dataObject *data;   //!< Data field that contains properties and states

public:
    /* constructor */
    objFieldEntry() : pos_x(-1), pos_y(-1),
                      x_prev(NULL), x_next(NULL),
                      y_prev(NULL), y_next(NULL),
                      data(NULL) {};


    /*!
     *\brief  create a data object
     */
    void createDataObject(baseMaterialConfig::materialType_t type)
    {

        data = new dataObject(type);
#if 0
        baseMaterial *m = createMaterial(type);
        data->type = m;
#endif
    }

    void deleteDataObject()
    {
        if (data != NULL) {
            delete data;
        }
    }


#if 0
    /*! \brief  create a material object
     *  \todo   use copy contructor
     * FIXME: move to dataObject class
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
#endif
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
