/******************************************************************************/
/*!
 * \file    objField.cpp
 * \brief   Implementation of the class objField.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

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
            entries[y*size_x + x].pos_x = x;
            entries[y*size_x + x].pos_y = y;

            // set neighbors
            if (x == 0) {
                entries[y*size_x + x].x_prev = NULL;
            } else {
                entries[y*size_x + x].x_prev = &entries[y*size_x + x-1];
            }
            if (x == size_x-1) {
                entries[y*size_x + x].x_next = NULL;
            } else {
                entries[y*size_x + x].x_next = &entries[y*size_x + x+1];
            }
            if (y == 0) {
                entries[y*size_x + x].y_prev = NULL;
            } else {
                entries[y*size_x + x].y_prev = &entries[(y-1)*size_x + x];
            }
            if (y == size_y-1) {
                entries[y*size_x + x].y_next = NULL;
            } else {
                entries[y*size_x + x].y_next = &entries[(y+1)*size_x + x];
            }
        }
    }
};

