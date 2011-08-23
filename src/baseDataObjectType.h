/*!
 * \file    baseDataObjectType.h
 * \brief   Virtual class to define the interface of the used data object types
 *  and to define the data object config class.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \todo    define data object type symbols
 *  FIXME implement config and base data class and derived classes in a
 *        way that the config and base data class constructors are not called
 */

#ifndef _BASE_DATA_OBJECT_TYPE_H_
#define _BASE_DATA_OBJECT_TYPE_H_

#include <string>
#include <stdio.h> 

//#include "dataObjectTypes.h"

using namespace std;

/*
 * \class baseDataObjectConfig
 */
class baseDataObjectConfig
{
/* ======== class datatypes ======== */    
public:
    /*!
     * \enum data object types
     */
    typedef enum
    {
        empty,
        sand,
        wall,
        stone,
        unknown
    } dataObjectType_t;


/* ======== class attributes ======== */
private:
    dataObjectType_t type;


/* ======== class initialisation functions ======== */
public:
    /*!
     * \brief   Constructor
     */
    baseDataObjectConfig(const dataObjectType_t type = unknown) : type(type) {
//        printf("%s\n", __func__);
    }


    /*!
     * \brief   Set the data object type.
     * \param   Type of the data object.
     */
    void setType(dataObjectType_t type) {
        this->type = type;
    }
    
    
    /*!
     * \brief   Get the data object type.
     * \return  Data object type of the class.
     */
    dataObjectType_t getType() {
        return type;
    }


};


/*
 * \class baseDataObjectType
 */
class baseDataObjectType : public baseDataObjectConfig
{
/* ======== class attributes ======== */    
public:
    string name;      /*!< data type name */
    char   symbol;    /*!< short symbol as data type identification */
                      /* FIXME: define symbols */

public:
    /*!
     * \brief   Default constructor
     * \details Set default values to the constant class attributes.
     * \todo    make function virtual. create a unknown class
     */
    baseDataObjectType() : name("unknown"), symbol('?') {
        setType(unknown);
//        printf("%s: %s\n", __func__, getName().c_str());
    };

    /*!
     * \brief   Create a data object type object as a function of its type.
     */
    static baseDataObjectType *createDataObjectType(dataObjectType_t type);

    /*!
     * \brief   Delete a data object type object
     */
    static void deleteDataObjectType(baseDataObjectType *t);



/* ======== class string functions ======== */
public:

    /*!
     * \brief   Get the objects data type name.
     * \return  Data type name as a string object.
     */
    string getName() {return name; };
    
    /*!
     * \brief   Get the objects data type symbol.
     * \return  Data type symbol as a character.
     */
    char getSymbol() {return symbol; };

};


#endif
