/* file: baseObj.h */

#ifndef _BASEOBJ_H_
#define _BASEOBJ_H_

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
    /* define object types */
    typedef enum
    {
        empty,
        sand,
        wall,
        stone,
        unknown
    } objType_t; 


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
    objType_t type;

public:
    /* constructor */
    baseObj() : pos_x(-1), pos_y(-1), type(unknown),
                x_prev(NULL), x_next(NULL),
                y_prev(NULL), y_next(NULL) {};

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
    /* get the type as a string */
    string strType();
    /* get the type as a short string */
    string strTypeShort();
};


#endif
