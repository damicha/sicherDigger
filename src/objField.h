/******************************************************************************/
/*!
 * \file    objField.h
 * \brief   handels a 2 dimensional field of class objFieldEntry objects
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \todo add obj type (physic, gfx(txt output) ) as a member of objFieldEntry->obj
 * \todo add a configuration class 
 *
 ******************************************************************************/

// FIXME: in general do only function declarations -> move implementation to *.cpp file

#ifndef _OBJ_FIELD_H_
#define _OBJ_FIELD_H_


#include "baseDataObjectType.h"
#include "objFieldEntry.h"
#include "SDig_LevelConfig.h"

using namespace std;
using namespace SDig;


class objField;


/*!
 * \class   objField 
 */
class objField
{

/* ======== class types ======== */
public:

/* ======== class attributes ======== */
public:
    int size_x;     /*!< size of the field dimension x */
    int size_y;     /*!< size of the field dimension y */
    objFieldEntry   *entries;   /*!< reference to an array of the object field entries */
    objFieldEntry   *pl_entry;  /*!< reference to the object field entry that stores the player data */

/* ======== class init functions ======== */
public:
    /*!
     * \brief   Constructor
     * \details Set field sizes, create and initialize the object field.
     * \param   size_x field size of the dimension x
     * \param   size_y field size of the dimension y
     */
    objField(int size_x, int size_y) : entries(NULL), pl_entry(NULL)
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
                if (x == 1 && y == 1)
                {
                    /* set player position/object */
                    entries[y*size_x + x].createDataObject(baseDataObjectType::player);
                    pl_entry  = &entries[y*size_x + x];
                } else if (x == 0 || x == size_x - 1 ||
                           y == 0 || y == size_y - 1)
                {
                    entries[y*size_x + x].createDataObject(baseDataObjectType::wall);
                } else {
                    entries[y*size_x + x].createDataObject(baseDataObjectType::sand);
                }
            }
        }
    };

    /*!
     * \brief   Constructor
     * \details Initializes the field with the given configuration.
     * \param   cfg configuration
     * FIXME: move function implementation to *.cpp
     */
    objField(const LevelConfig &pLevelConfig)
    {
        /* set dimensions */
        size_x = pLevelConfig.getSizeX();
        size_y = pLevelConfig.getSizeY();
        char *cfgData = pLevelConfig.getData(); 
        
        /* get memory for the field entries */
        entries = new objFieldEntry[size_x*size_y];
        
        /* do final field object initialization */
        initObj();

        /* create materials */
        // FIXME do type conversion in function of the config class
        // FIXME move player info data and functions to player class dotPlayer
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
                switch (cfgData[y*size_x + x])
                {
                    case '#':
                        entries[y*size_x + x].createDataObject(baseDataObjectType::wall);
                        break;
                    case '.':
                        entries[y*size_x + x].createDataObject(baseDataObjectType::sand);
                        break;
                    case ' ':
                        entries[y*size_x + x].createDataObject(baseDataObjectType::empty);
                        break;
                    case 'O':
                        entries[y*size_x + x].createDataObject(baseDataObjectType::stone);
                        break;
                    case '8':
                        /* set player position/object */
                        entries[y*size_x + x].createDataObject(baseDataObjectType::player);
                        pl_entry = &entries[y*size_x + x];
                        break;
                    default:
                        entries[y*size_x + x].createDataObject(baseDataObjectType::unknown);
                        break;
                }
            }
        }
    };
    
    /*!
     * \brief   Destructor
     */
    ~objField() {
        delete [] entries;   
    }


    /*!
     * \brief   Initialize the field objects.
     * \details Set field object data (field position, neighbors).
     */
    void initObj();

};

#endif
