/******************************************************************************/
/*!
 * \file    objFieldEntry.h
 * \brief   FIXME
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _OBJ_FIELD_ENTRY_H_
#define _OBJ_FIELD_ENTRY_H_

#include "SDig_DataObject.h"

#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;
using namespace SDig;

class objFieldEntry;

/*
 * objFieldEntry
 */
// FIXME: change to a template class for DataObject
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
    int pos_y;
    int pos_x;
    // FIXME: add object layer: (objFieldEntry.obj: obj.m, obj...)
#if 0
    baseMaterial *m;    /*!< the object material. A virtual class is used */
#endif
    DataObject *data;   //!< Data field that contains properties and states

public:
    /* constructor */
    objFieldEntry() :
        x_prev(NULL), x_next(NULL),
        y_prev(NULL), y_next(NULL),
        pos_y(-1), pos_x(-1),
        data(NULL)
    {};


    /*!
     *\brief  create a data object
     */
    void createDataObject(BaseDOT::DOTType type)
    {

        data = new DataObject(this, type);
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
        data = NULL;
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
