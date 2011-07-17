/*!
 * \file    materials.h
 * \brief   Material definition classes; derivated from the virtual class
 *          baseMaterial.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 */

#ifndef _MATERIALS_H_
#define _MATIRIALS_H_

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
    };
};


#endif