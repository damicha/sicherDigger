/******************************************************************************/
/*!
 * \file    LevelData.h
 * \brief   Level configuration data
 *
 * \author  damicha of defect
 * \date    2011-2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_LEVEL_DATA_H_
#define _SDIG_LEVEL_DATA_H_


#include "LevelConfig.h"

namespace SDig {

/*!
 * \name field_a configuration data
 *
 * FIXME: correct doxygen tags
 * @{
 */
#define LEVEL_NAME          "field_a"
#define LEVEL_TIME_LIMIT    50
#define LEVEL_SAND_REQUIRED 2               // required sand to eat before exit opens
#define LEVEL_SIZE_X        8
#define LEVEL_SIZE_Y        8
static char field_a_data[LEVEL_SIZE_X * LEVEL_SIZE_Y] =
{
    '#', '#', '#', '#', '#', '#', '#', '#',
    '#', 'O', 'O', 'O', 'O', 'O', ' ', '#',
    '#', 'O', 'O', '.', ' ', ' ', 'O', '#',
    '#', 'O', '.', 'O', ' ', ' ', '.', '#',
    '#', '.', ' ', ' ', 'O', ' ', '.', '#',
    '#', '.', ' ', '.', ' ', 'O', ' ', '#',
    'E', '.', '8', '.', ' ', ' ', 'O', '#',
    '#', '#', '#', '#', '#', '#', '#', '#',
};
static LevelConfig field_a = LevelConfig(
    LEVEL_NAME, LEVEL_TIME_LIMIT, LEVEL_SAND_REQUIRED,
    LEVEL_SIZE_X, LEVEL_SIZE_Y, field_a_data
);

#undef LEVEL_NAME
#undef LEVEL_TIME_LIMIT
#undef LEVEL_SAND_REQUIRED
#undef LEVEL_SIZE_X    
#undef LEVEL_SIZE_Y    

/*! @} */


/*!
 * \name field_a configuration data
 *
 * FIXME: correct doxygen tags
 * @{
 */
#define LEVEL_NAME          "field_b"
#define LEVEL_TIME_LIMIT    30
#define LEVEL_SAND_REQUIRED 9               // required sand to eat before exit opens
#define LEVEL_SIZE_X        10
#define LEVEL_SIZE_Y        6
static char field_b_data[LEVEL_SIZE_X * LEVEL_SIZE_Y] =
{
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', '8', 'O', '#', 'O', 'O', 'O', 'O', 'O', '#',
    '#', '.', 'O', '#', '.', '.', '.', '.', '.', '#',
    '#', ' ', '.', '#', ' ', ' ', ' ', ' ', '.', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', 'E',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
};
static LevelConfig field_b = LevelConfig(
    LEVEL_NAME, LEVEL_TIME_LIMIT, LEVEL_SAND_REQUIRED,
    LEVEL_SIZE_X, LEVEL_SIZE_Y, field_b_data
);

#undef LEVEL_NAME
#undef LEVEL_TIME_LIMIT
#undef LEVEL_SAND_REQUIRED
#undef LEVEL_SIZE_X    
#undef LEVEL_SIZE_Y    

/*! @} */


}       // namespace

#endif  // _SDIG_LEVEL_DATA_H_

