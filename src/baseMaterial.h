/*!
 * \file    baseMaterial.h
 * \class   baseMaterial 
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

using namespace std;


/*
 * baseMaterial
 */
class baseMaterial
{
/* ======== class attributes ======== */    
public:
    string name;      /*!< material name */
    char   symbol;    /*!< short symbol as material identification */
                      /* FIXME: define symbols */

public:
    /*!
     * \brief   virtual constructor
     * \details Set default values to the constant class attributes.
     */
    baseMaterial() : name("unknown"), symbol('?') {};


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
