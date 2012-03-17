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


/*!
 * \brief   Constructor
 * \details Set field sizes, create and initialize the object field.
 * \param   size_x field size of the dimension x
 * \param   size_y field size of the dimension y
 */
objField::objField(int size_x, int size_y) : entries(NULL), mPlayer(NULL), mExit(NULL)
{
    /* set dimensions */
    this->size_x = size_x;
    this->size_y = size_y;
    
    /* get memory for the field entries */
    entries = new objFieldEntry[size_x*size_y];

    /* do final field object initialization */
    initObj();
    

    /* create materials (sand surrounded with walls)
     * place the player into the left top corner */
    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++)
        {
            if        (x == 1 && y == 1) {
                /* set player position/object */
                // FIXME: put data object creation in a function
                entries[y*size_x + x].createDataObject(BaseDOT::player);
                mPlayer = (DOTPlayer *)entries[y*size_x + x].data->getTypeObject();
                // set back references
                mPlayer->initReferences(this, entries[y*size_x + x].data);
            } else if (x == 1 && y == 0) {
                /* set exit position/object */
                entries[y*size_x + x].createDataObject(BaseDOT::exit);
                mExit = (DOTExit *)entries[y*size_x + x].data->getTypeObject();
                // set back references
                mExit->initReferences(this, entries[y*size_x + x].data);
                // set properties    
                mExit->setRequiredSand(1); 
            } else if (x == 0 || x == size_x - 1 ||
                       y == 0 || y == size_y - 1)
            {
                entries[y*size_x + x].createDataObject(BaseDOT::wall);
            } else {
                entries[y*size_x + x].createDataObject(BaseDOT::sand);
            }
        }
    }
}

/*!
 * \brief   Constructor
 * \details Initializes the field with the given configuration.
 * \param cfg   configuration
 */
objField::objField(const LevelConfig &pLevelConfig)
{
    /* set dimensions */
    size_x = pLevelConfig.getSizeX();
    size_y = pLevelConfig.getSizeY();
    
    /* get memory for the field entries */
    entries = new objFieldEntry[size_x*size_y];
    
    /* do final field object initialization */
    initObj();

    /* create materials */
    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++)
        {
            /* get object type */
            BaseDOT::DOTType objType = pLevelConfig.getData(x, y);
            /* create entry */
            entries[y*size_x + x].createDataObject(objType);
            
            /* store the reference of the players object */
            if (objType == BaseDOT::player) {
                mPlayer = (DOTPlayer *)entries[y*size_x + x].data->getTypeObject();
                // set back references
                mPlayer->initReferences(this, entries[y*size_x + x].data);
            }
            /* store the reference of the exit object */
            if (objType == BaseDOT::exit) {
                mExit = (DOTExit *)entries[y*size_x + x].data->getTypeObject();
                // set back reference
                mExit->initReferences(this, entries[y*size_x + x].data);
                // set properties    
                mExit->setRequiredSand(pLevelConfig.getRequiredSand()); 
            }
        }
    }

};


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

