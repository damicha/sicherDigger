/*!
 * \file    config.h
 * \class   config 
 * \brief   Stores the configuration for the field as an array of characters
 * 
 * \author  damicha of defect
 * \date    2011 
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

using namespace std;

/*
 * config
 */
class config
{
/* ======== class attributes ======== */    
public:
    int size_x;     /*!< size of the field dimension x */
    int size_y;     /*!< size of the field dimension y */
    string name;    /*!< name od the configuration */
    char *data;     /*!< character array that contains the configuration */

/* ======== class init functions ======== */
public:
    /*!
     * \brief   Constructor
     * \details Set field sizes, create and initialize the object field.
     * \param   size_x field size of the dimension x
     * \param   size_y field size of the dimension y
     * \param   cfg character array with the configuration
     */
    config(const string &name,
                 int size_x, int size_y,
                 const char *data)
    {
        /* set configuration name */
        this->name = name;
        /* set dimensions */
        this->size_x = size_x;
        this->size_y = size_y;

        /* copy the configuration array */
        this->data = new char[size_x*size_y];

        /* check and copy */
        // FIXME: check
        int cnt = 0;
        for (int y = 0; y < size_y; y++) {
            for (int x = 0; x < size_x; x++) {
                this->data[cnt] = data[cnt];
                cnt++;
            }
        }
    }

    /*!
     * \brief   Constructor
     */
    ~config() {
        /* destroy the configuration array */
        delete this->data;
    }
    

public:

};


#endif
