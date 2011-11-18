/******************************************************************************/
/*!
 * \file    dataObjectTypes.h
 * \brief   Declarations of Data object type classes; derivated from the
 *  class baseDataObjectType.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _DATA_OBJECT_TYPES_H_
#define _DATA_OBJECT_TYPES_H_

#include "SDig_BaseDOT.h"

#include <string>


using namespace std;
using namespace SDig;

/*!
 * \class   dotWall
 * \brief   Declaration of the data object type class: wall. 
 */
class dotWall : public BaseDOT
{

public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    dotWall() {
        mName = string("Wall");
        setType(wall);
//        printf("%s: %s\n", __func__, getName().c_str());
    }
};


/*!
 * \class   dotSand
 * \brief   Declaration of the data object type class: sand.
 */
class dotSand : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    dotSand() {
        mName = string("Sand");
        setType(sand);
    };
};


/*!
 * \class   dotEmpty
 * \brief   Declaration of the data object type class: empty.
 */
class dotEmpty : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    dotEmpty() {
        mName = string("Empty");
        setType(empty);
    };
};


/*!
 * \class   dotStone 
 * \brief   Declaration of the data object type class: stone.
 */
class dotStone : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    dotStone() {
        mName = string("Stone");
        setType(stone);
    };
};


/*!
 * \class   dotPlayer
 * \brief   Declaration of the data object type class: player.
 */
class dotPlayer : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    dotPlayer() {
        mName = string("Player");
        setType(player);
    };
};


#endif
