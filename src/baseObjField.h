/* baseObjField.h */

// FIXME: add obj type (physic, gfx(txt output) ) as a member of baseObj

#ifndef _BASEOBJFIELD_H_
#define _BASEOBJFIELD_H_


#include "baseObjField.h"
#include "baseObj.h"

#include <deque>
#include <string>
#include <sstream>
using namespace std;


class baseObjField;


/*
 * baseObjField
 */
class baseObjField
{
    /*
     * class ojects
     */
public:
    /* size of the field dimensions */
    int size_x, size_y;
    /* field */
    deque<baseObj> objs;

public:
    /* constructor */
    baseObjField(int size_x, int size_y)
    {
        // set dimensions
        this->size_x = size_x;
        this->size_y = size_y;
        
        // initialze field with an empty default object
        baseObj defaultObj;
        objs.resize(size_x * size_y, defaultObj);
        
        // do final field object initialization
        initObj();
    };

    /* initialize the field objects
     * - set field object data (field position, neighbors)
     */
    void initObj();

};

#endif
