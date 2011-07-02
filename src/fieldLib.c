/* fieldLib.cpp */

// FIXME: improve txt output
// FIXME: split files
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
    int pos_x, pos_y;
    // neighbors
    baseObj *x_prev, *x_next;
    baseObj *y_prev, *y_next;

    baseObj() : pos_x(-1),
                x_prev(NULL), x_next(NULL),
                y_prev(NULL), y_next(NULL) {};

    string str()
    {
        stringstream ss;
        ss << "<idx:" << strData() << " " << strNeighbors() << ">";
        return ss.str();
    }

    string strDataEmpty() {
        stringstream ss;
        ss << "<-, ->";
        return ss.str();
    }
    
    string strData() {
        stringstream ss;
        ss << "<" << pos_y << ", " << pos_x << ">";
        return ss.str();
    }

    string strNeighbors() {
        stringstream ss;
        ss << "(y:" <<  ((y_prev == NULL) ? strDataEmpty() : y_prev->strData()) << ", " <<
                        ((y_next == NULL) ? strDataEmpty() : y_next->strData()) << ", " <<
               "x:" <<  ((x_prev == NULL) ? strDataEmpty() : x_prev->strData()) << ", " <<
                        ((x_next == NULL) ? strDataEmpty() : x_next->strData()) << ")";

        return ss.str();
    }
};


/*
 * baseObjField
 */
class baseObjField
{
public:
    int size_x, size_y;
    deque<baseObj> objs;

    baseObjField(int size_x, int size_y)
    {
        this->size_x = size_x;
        this->size_y = size_y;
        
        baseObj defaultObj;
        objs.resize(size_x * size_y, defaultObj);
        
        initObj();
    };

    int initObj()
    {
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
                // set position information
                objs[y*size_x + x].pos_x = x;
                objs[y*size_x + x].pos_y = y;
                // set neighbors
                if (x == 0) {
                    objs[y*size_x + x].x_prev = NULL;
                } else {
                    objs[y*size_x + x].x_prev = &(objs[y*size_x + x-1]);
                }
                if (x == size_x-1) {
                    objs[y*size_x + x].x_next = NULL;
                } else {
                    objs[y*size_x + x].x_next = &(objs[y*size_x + x+1]);
                }
                if (y == 0) {
                    objs[y*size_x + x].y_prev = NULL;
                } else {
                    objs[y*size_x + x].y_prev = &(objs[(y-1)*size_x + x]);
                }
                if (y == size_y-1) {
                    objs[y*size_x + x].y_next = NULL;
                } else {
                    objs[y*size_x + x].y_next = &(objs[(y+1)*size_x + x]);
                }
            }
        }
    };

};






/*
 * main
 */
int main(void)
{
    baseObjField field(5, 5);

    for(int i = 0; i < field.objs.size(); i++) {
        printf("position: %d, data: %s\n", i, field.objs[i].str().c_str()); 
    }
    return 0;

/* error handling */
out:
    return -1;
}

