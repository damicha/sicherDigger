/* file: baseObj.cpp */

// FIXME: add obj type (physic, gfx(txt output) ) as a member of baseObj
// FIXME: use doxygen comments

#include "baseObj.h"

#include <string>
#include <sstream>
using namespace std;


/* get the object content as a string */
string baseObj::str()
{
    stringstream ss;
    ss << "<idx:" << strData() << ", neighbors: " << strNeighbors() << ">";
    return ss.str();
}


/* get the content of an empty object as a string*/
string baseObj::strDataEmpty()
{
    return stringstream("[-, -]").str();
}


/* get the object data as a string */
string baseObj::strData()
{
    stringstream ss;
    ss << "[" << pos_x << ", " << pos_y << "]";
    return ss.str();
}


/* get the object data of the neighbors as a string */
string baseObj::strNeighbors()
{
    stringstream ss;
    ss << "x--:" <<  ((x_prev == NULL) ? strDataEmpty() : x_prev->strData()) << ", " <<
          "x++:" <<  ((x_next == NULL) ? strDataEmpty() : x_next->strData()) << ", " <<
          "y--:" <<  ((y_prev == NULL) ? strDataEmpty() : y_prev->strData()) << ", " <<
          "y++:" <<  ((y_next == NULL) ? strDataEmpty() : y_next->strData());

    return ss.str();
}



