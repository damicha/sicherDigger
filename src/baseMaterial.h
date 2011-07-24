/*!
 * \file    baseMaterial.h
 * \brief   virtual class to define the interface of the used materials
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \todo    define material symbols
 */

#ifndef _BASEMATERIAL_H_
#define _BASEMATERIAL_H_

#include <string>
#include <stdio.h> 

using namespace std;

/*
 * \class baseMaterialConfig
 */
class baseMaterialConfig
{
/* ======== class datatypes ======== */    
public:
    /*!
     * \enum material types
     */
    typedef enum
    {
        empty,
        sand,
        wall,
        stone,
        unknown
    } materialType_t;


/* ======== class attributes ======== */
private:
    materialType_t type;


/* ======== class initialisation functions ======== */
public:
    /*!
     * \brief   Constructor
     */
    baseMaterialConfig(const materialType_t type = unknown) : type(type) {}


    /*!
     * \brief   Set the material type.
     * \param   material type of the class
     */
    void setType(materialType_t type) {
        this->type = type;
    }
    
    
    /*!
     * \brief   Get the material type.
     * \return  material type of the class
     */
    materialType_t getType() {
        return type;
    }


};


/*
 * \class baseMaterial
 */
class baseMaterial : public baseMaterialConfig
{
/* ======== class attributes ======== */    
public:
    string name;      /*!< material name */
    char   symbol;    /*!< short symbol as material identification */
                      /* FIXME: define symbols */
    int done;       /*!< 1 if material was already used by physics engine: 
                     * FIXME: move to a physics class
                     * FIXME: use a own data type
                     * FIXME: don't use done. use blocked by current, next, prev ..
                     */

public:
    /*!
     * \brief   virtual constructor
     * \details Set default values to the constant class attributes.
     * \todo    FIXME how to call the constructor of baseMaterialConfig ?
     */
    baseMaterial() : name("unknown"), symbol('?') {
        setType(unknown);        
    };


/* ======== class string functions ======== */
public:

    /*!
     * \brief   Get the objects material name.
     * \return  Material name as a string object.
     */
    string getName() {return name; };
    
    /*!
     * \brief   Get the objects material symbol.
     * \return  Material symbol as a character.
     */
    char getSymbol() {return symbol; };

};


#endif
