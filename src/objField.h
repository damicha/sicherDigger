/*!
 * \file    objField.h
 * \brief   handels a 2 dimensional field of class objFieldEntry objects
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \todo add obj type (physic, gfx(txt output) ) as a member of objFieldEntry->obj
 * \todo add a configuration class 
 */

#ifndef _OBJFIELD_H_
#define _OBJFIELD_H_


#include "baseDataObjectType.h"
#include "objFieldEntry.h"
#include "config.h"

#include <deque>
#include <string>
#include <sstream>
using namespace std;


class objField;


/*!
 * \class   objField 
 */
class objField
{

/* ======== class types ======== */
public:

    /*!
     * \enum    string output format of the class content
     */
    typedef enum {
        list,       //!< print the whole field content as a list
        array       //!< print the field contnet as a formated 2d array
    } stringOutputFormat_t;

    /*!
     * \struct  player object info
     */
    typedef struct {
        objFieldEntry *obj;     /*!< reference to the player object */
        int x, y;               /*!< current position in the object field */
    } playerObjectInfo_t;



/* ======== class attributes ======== */
public:
    int size_x;     /*!< size of the field dimension x */
    int size_y;     /*!< size of the field dimension y */
    objFieldEntry       *objs;   /*!< pointer to an array of the field objects */
    playerObjectInfo_t  plInfo;  /*!< infos about the player object */

/* ======== class init functions ======== */
public:
    /*!
     * \brief   Constructor
     * \details Set field sizes, create and initialize the object field.
     * \param   size_x field size of the dimension x
     * \param   size_y field size of the dimension y
     */
    objField(int size_x, int size_y) : objs(NULL)
    {
        /* set dimensions */
        this->size_x = size_x;
        this->size_y = size_y;
        
        /* get memory for the field entries */
        objs = new objFieldEntry[size_x*size_y];

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
                    objs[y*size_x + x].createDataObject(baseDataObjectType::player);
                    plInfo.obj  = &objs[y*size_x + x];
                    plInfo.x    = x;
                    plInfo.y    = y;
                } else if (x == 0 || x == size_x - 1 ||
                           y == 0 || y == size_y - 1)
                {
                    objs[y*size_x + x].createDataObject(baseDataObjectType::wall);
                } else {
                    objs[y*size_x + x].createDataObject(baseDataObjectType::sand);
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
    objField(const config &cfg)
    {
        /* set dimensions */
        this->size_x = cfg.size_x;
        this->size_y = cfg.size_y;
        
        /* get memory for the field entries */
        objs = new objFieldEntry[size_x*size_y];
        
        /* do final field object initialization */
        initObj();

        /* create materials */
        // FIXME do type conversion in function of the config class
        // FIXME move player info data and functions to player class dotPlayer
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
                switch (cfg.data[y*size_x + x])
                {
                    case '#':
                        objs[y*size_x + x].createDataObject(baseDataObjectType::wall);
                        break;
                    case '.':
                        objs[y*size_x + x].createDataObject(baseDataObjectType::sand);
                        break;
                    case ' ':
                        objs[y*size_x + x].createDataObject(baseDataObjectType::empty);
                        break;
                    case 'O':
                        objs[y*size_x + x].createDataObject(baseDataObjectType::stone);
                        break;
                    case '8':
                        /* set player position/object */
                        objs[y*size_x + x].createDataObject(baseDataObjectType::player);
                        plInfo.obj  = &objs[y*size_x + x];
                        plInfo.x    = x;
                        plInfo.y    = y;
                        break;
                    default:
                        objs[y*size_x + x].createDataObject(baseDataObjectType::unknown);
                        break;
                }
            }
        }
    };
    
    /*!
     * \brief   Destructor
     */
    ~objField() {
        delete [] objs;   
    }


    /*!
     * \brief   Initialize the field objects.
     * \details Set field object data (field position, neighbors).
     */
    void initObj();


/* ======== class string functions ======== */
public:
    /*!
     * \brief   Get the class data content as a string.
     * \param   format Select a string format.
     * \return  The generated string.
     */
    string str(stringOutputFormat_t format = array)
    {
        switch(format)
        {
            case list:  return strList();
            case array: return strArray();
        }
    }

    /*!
     * \brief   Get the class data content as a string in the list format.
     * \details The content of all members of the field will be listed.
     * \return  The generated string.
     */
    string strList()
    {
        string s;

        printf("Field dimensions: (x: %d, y: %d) - %d\n", size_x, size_y, s.max_size());
        for(int i = 0; i < size_x*size_y; i++) {
            printf("position: %2d, data: %s\n", i, objs[i].str().c_str());
        }
        return s;
    }

    /*!
     * \brief   Get the class data content as a string in the array format.
     * \details The content of all entries of the field will be printed as a
     *          2 dimensional array of characters that symbolize the field
     *          entry type.
     * \return  The generated string.
     */
    string strArray()
    {
        string s;
        
        // FIXME use textEngine

        printf("Field dimensions: (x: %d, y: %d)\n", size_x, size_y);
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
        //        printf("%c ", objs[y*size_x + x].data->type->symbol);
            }
            printf("\n");
        }
        return s;
    }

};

#endif
