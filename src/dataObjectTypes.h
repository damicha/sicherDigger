/******************************************************************************/
/*!
 * \file    dataObjectTypes.h
 * \brief   Declarations of Data object type classes; derivated from the
 *  class baseDataObjectType.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 ******************************************************************************/

#ifndef _DATA_OBJECT_TYPES_H_
#define _DATA_OBJECT_TYPES_H_

#include "baseDataObjectType.h"

#include <string>

using namespace std;


/*!
 * \class   dotWall
 * \brief   Declaration of the data object type class: wall. 
 */
class dotWall : public baseDataObjectType
{

public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    dotWall() {
        name = string("Wall");
        setType(wall);
//        printf("%s: %s\n", __func__, getName().c_str());
    }
};


/*!
 * \class   dotSand
 * \brief   Declaration of the data object type class: sand.
 */
class dotSand : public baseDataObjectType
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    dotSand() {
        name = string("Sand");
        setType(sand);
    };
};


/*!
 * \class   dotEmpty
 * \brief   Declaration of the data object type class: empty.
 */
class dotEmpty : public baseDataObjectType
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    dotEmpty() {
        name = string("Empty");
        setType(empty);
    };
};


/*!
 * \class   dotStone 
 * \brief   Declaration of the data object type class: stone.
 */
class dotStone : public baseDataObjectType
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    dotStone() {
        name = string("Stone");
        setType(stone);
    };
};


/*!
 * \class   dotPlayer
 * \brief   Declaration of the data object type class: player.
 */
class dotPlayer : public baseDataObjectType
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    dotPlayer() {
        name = string("Player");
        setType(player);
    };
};


#endif
