/* fieldLib.cpp */

// FIXME: traverse through the array elements (print pos, prev, next pos)
// FIXME: split files
// FIXME: add 2nd dimention
// FIXME: add obj type (physic, gfx(txt output) ) as a member of baseObj

#include <stdio.h>
#include <deque>
#include <string>
#include <sstream>
using namespace std;


class baseObj;
class baseObjField;


/*
 * baseObj
 */
class baseObj
{
public:
    int pos_x;
    // neighbors
    baseObj *x_prev, *x_next;

    baseObj() : pos_x(-1), x_prev(NULL), x_next(NULL) {};

    string str()
    {
        stringstream ss;
        ss << "<idx:" << strData() << " " << strNeighbors() << ">";
        return ss.str();
    }

    string strData() {
        stringstream ss;
        ss << pos_x;
        return ss.str();
    }

    string strNeighbors() {
        stringstream ss;
        ss << "(" <<  ((x_prev == NULL) ? "-" : x_prev->strData()) << ", " <<
                      ((x_next == NULL) ? "-" : x_next->strData()) << ")";

        return ss.str();
    }
};


/*
 * baseObjField
 */
class baseObjField
{
public:
    int size_x;
    deque<baseObj> objs;

    baseObjField(int size) {
        size_x = size;
        
       baseObj defaultObj;
        objs.resize(size, defaultObj);
        
        initObj();
    };

    int initObj() {
        for (int x = 0; x < objs.size(); x++)
        {
            // set position information
            objs[x].pos_x = x;
            // set neighbors
            // FIXME: set a reference to a static dummy object instead of NULL
            if (x == 0) {
                objs[x].x_prev = NULL;
            } else {
                objs[x].x_prev = &(objs[x-1]);
            }
            if (x == objs.size()-1) {
                objs[x].x_next = NULL;
            } else {
                objs[x].x_next = &(objs[x+1]);
            }
        }
    };

};






/*
 * main
 */
int main(void)
{
    baseObjField field(10);

    for(int x = 0; x < field.objs.size(); x++) {
        printf("position: %d, data: %s\n", x, field.objs[x].str().c_str()); 
    }
    return 0;

/* error handling */
out:
    return -1;
}

