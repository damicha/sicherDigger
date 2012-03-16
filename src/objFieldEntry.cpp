/******************************************************************************/
/*!
 * \file    objFieldEntry.cpp
 * \brief   FIXME
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

/* FIXME:
 *  add obj type (physic, gfx(txt output) ) as a member of objFieldEntry->obj
 *  use doxygen comments
 *  needed object structure (add an extra object layer!):
 *   - objField->objFieldEntries[x,y]->Object->(.material, .state)
 */

#include "objFieldEntry.h"

#include <string>
#include <sstream>
using namespace std;


/*!
 *\brief  create a data object
 */
void objFieldEntry::createDataObject(BaseDOT::DOTType type)
{
    data = new DataObject(this, type);
}

void objFieldEntry::deleteDataObject()
{
    if (data != NULL) {
        delete data;
    }
    data = NULL;
}

/* get the object content as a string */
string objFieldEntry::str()
{
    stringstream ss;
    ss << "<idx:" << strData() << ", " <<
          "type:" << data->getTypeObject()->getName() << ", " <<
          "neighbors: " << strNeighbors() << ">";
    return ss.str();
}


/* get the content of an empty object as a string*/
string objFieldEntry::strDataEmpty()
{
    return stringstream("[-, -]").str();
}


/* get the object data as a string */
string objFieldEntry::strData()
{
    stringstream ss;
    ss << "[" << pos_x << ", " << pos_y << "]";
    return ss.str();
}


/* get the object data of the neighbors as a string */
string objFieldEntry::strNeighbors()
{
    stringstream ss;
    ss << "x--:" <<  ((x_prev == NULL) ? strDataEmpty() : x_prev->strData()) << ", " <<
          "x++:" <<  ((x_next == NULL) ? strDataEmpty() : x_next->strData()) << ", " <<
          "y--:" <<  ((y_prev == NULL) ? strDataEmpty() : y_prev->strData()) << ", " <<
          "y++:" <<  ((y_next == NULL) ? strDataEmpty() : y_next->strData());

    return ss.str();
}

