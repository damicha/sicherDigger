/*!
 * \file    baseObjField.h
 * \class   baseObjField 
 * \brief   handels a 2 dimensional field of class baseObj objects
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \todo add obj type (physic, gfx(txt output) ) as a member of baseObj
 * \todo add a configuration class 
 */

#ifndef _BASEOBJFIELD_H_
#define _BASEOBJFIELD_H_


#include "baseObjField.h"
#include "baseObj.h"
#include "config.h"

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

/* ======== class types ======== */
public:

    /*!
     * \enum    string output format of the class content
     */
    typedef enum {
        list,       //!< print the whole field content as a list
        array       //!< print the field contnet as a formated 2d array
    } stringOutputFormat_t;


/* ======== class attributes ======== */
public:
    int size_x;     /*!< size of the field dimension x */
    int size_y;     /*!< size of the field dimension y */
    deque<baseObj> objs;    /*!< field objects */


/* ======== class init functions ======== */
public:
    /*!
     * \brief   Constructor
     * \details Set field sizes, create and initialize the object field.
     * \param   size_x field size of the dimension x
     * \param   size_y field size of the dimension y
     */
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

        // create materials (Walls and Sand)
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
                if (x == 0 || x == size_x - 1 ||
                    y == 0 || y == size_y - 1)
                {
                    objs[y*size_x + x].createMaterial(baseMaterialConfig::wall);
                } else {
                    objs[y*size_x + x].createMaterial(baseMaterialConfig::sand);
                }
          }
        }
    };


    /*!
     * \brief   Constructor
     * \details Initializes the field with the given configuration.
     * \param   cfg configuration
     */
    baseObjField(const config &cfg)
    {
        // set dimensions
        this->size_x = cfg.size_x;
        this->size_y = cfg.size_y;
        
        // initialze field with an empty default object
        baseObj defaultObj;
        objs.resize(size_x * size_y, defaultObj);
        
        // do final field object initialization
        initObj();

        // create materials
        // FIXME move material conversion to a material class or somewhere else
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
                switch (cfg.data[y*size_x + x]) {
                    case '#': objs[y*size_x + x].createMaterial(baseMaterialConfig::wall); break;
                    case '.': objs[y*size_x + x].createMaterial(baseMaterialConfig::sand); break;
                    case ' ': objs[y*size_x + x].createMaterial(baseMaterialConfig::empty); break;
                    case 'O': objs[y*size_x + x].createMaterial(baseMaterialConfig::stone); break;
                }
            }
        }
    };

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
        for(int i = 0; i < objs.size(); i++) {
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

        printf("Field dimensions: (x: %d, y: %d)\n", size_x, size_y);
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
                printf("%c ", objs[y*size_x + x].m->symbol);
            }
            printf("\n");
        }
        return s;
    }

};

#endif
