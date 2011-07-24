/***************************************************************************//**
 * \file    materials.h
 * \brief   Material definition classes; derivated from the virtual class
 *          baseMaterial.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 ******************************************************************************/

#ifndef _MATERIALS_H_
#define _MATERIALS_H_

#include "baseMaterial.h"

#include <string>

using namespace std;


/*!
 * \class   materialWall 
 */
class materialWall : public baseMaterial
{

public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    materialWall() {
        name = string("Wall");
        symbol = '#';
        setType(wall);
    }
};


/*!
 * \class   materialSand
 */
class materialSand : public baseMaterial
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    materialSand() {
        name = string("Sand");
        symbol = '.';
        setType(sand);
    };
};


/*!
 * \class   materialEmpty
 */
class materialEmpty : public baseMaterial
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    materialEmpty() {
        name = string("Empty");
        symbol = ' ';
        setType(empty);
    };
};


/*!
 * \class   materialStone 
 */
class materialStone : public baseMaterial
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    materialStone() {
        name = string("Stone");
        symbol = 'O';
        setType(stone);
    };
};


#endif
