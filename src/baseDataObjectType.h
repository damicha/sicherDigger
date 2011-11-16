/******************************************************************************/
/*!
 * \file    baseDataObjectType.h
 * \brief   Class used as basis class to define the interface of the used data
 *  object types.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 * \todo    FIXME define data object type symbols
 *
 ******************************************************************************/

#ifndef _BASE_DATA_OBJECT_TYPE_H_
#define _BASE_DATA_OBJECT_TYPE_H_

#include <string>
#include <stdio.h> 

using namespace std;

/*
 * \class baseDataObjectType
 */
class baseDataObjectType
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
        player,
        unknown
    } dataObjectType_t;


/* ======== class attributes ======== */
protected:
    dataObjectType_t type;  //!< data type
    string name;            //!< data type name
//    char   symbol;    /*!< short symbol as data type identification */
//                      /* FIXME: move to txt engine */

public:
    /*!
     * \brief   Default constructor
     * \details Set default values to the constant class attributes.
     * \todo    make function virtual. create a unknown class
     */
    baseDataObjectType() : name("unknown") {
        setType(unknown);
//        printf("%s: %s\n", __func__, getName().c_str());
    };

    /* FIXME: add virtuel destructor */


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
    
    
    /*!
     * \brief   Get the objects data type name.
     * \return  Data type name as a string object.
     */
    string getName() {return name; };
    
};


#endif
