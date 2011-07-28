/* objField.cpp */

#include "objFieldEntry.h"
#include "objField.h"

#include <deque>
#include <string>
#include <sstream>
using namespace std;


/* initialize the field objects */
void objField::initObj()
{

    /* initialize all field objects */
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

