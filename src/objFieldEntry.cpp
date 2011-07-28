/* file: objFieldEntry.cpp */

// FIXME: add obj type (physic, gfx(txt output) ) as a member of objFieldEntry->obj
// FIXME: use doxygen comments

#include "objFieldEntry.h"

#include <string>
#include <sstream>
using namespace std;


/* get the object content as a string */
string objFieldEntry::str()
{
    stringstream ss;
    ss << "<idx:" << strData() << ", " <<
          "type:" << m->getName() << ", " <<
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

