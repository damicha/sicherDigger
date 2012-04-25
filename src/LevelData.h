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
 * \name level_01 configuration data
 *
 * FIXME: correct doxygen tags
 * @{
 */
// FIXME use some kind of struct of for the configuration
#define LEVEL_NAME          "Level 01"
#define LEVEL_INFO          "Simple, simple."
#define LEVEL_TIME_LIMIT    50
#define LEVEL_SAND_REQUIRED 2               // required sand to eat before exit opens
#define LEVEL_SIZE_X        8
#define LEVEL_SIZE_Y        8
static char level_01_data[LEVEL_SIZE_X * LEVEL_SIZE_Y] =
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
static LevelConfig level_01 = LevelConfig(
    LEVEL_NAME, LEVEL_INFO, LEVEL_TIME_LIMIT, LEVEL_SAND_REQUIRED,
    LEVEL_SIZE_X, LEVEL_SIZE_Y, level_01_data
);

#undef LEVEL_NAME
#undef LEVEL_INFO
#undef LEVEL_TIME_LIMIT
#undef LEVEL_SAND_REQUIRED
#undef LEVEL_SIZE_X    
#undef LEVEL_SIZE_Y    

/*! @} */


/*!
 * \name level_02 configuration data
 *
 * FIXME: correct doxygen tags
 * @{
 */
#define LEVEL_NAME          "Level 02"
#define LEVEL_INFO          "Don't waste time."
#define LEVEL_TIME_LIMIT    30
#define LEVEL_SAND_REQUIRED 9               // required sand to eat before exit opens
#define LEVEL_SIZE_X        10
#define LEVEL_SIZE_Y        6
static char level_02_data[LEVEL_SIZE_X * LEVEL_SIZE_Y] =
{
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    '#', '8', 'O', '#', 'O', 'O', 'O', 'O', 'O', '#',
    '#', '.', 'O', '#', '.', '.', '.', '.', '.', '#',
    '#', ' ', '.', '#', ' ', ' ', ' ', ' ', '.', '#',
    '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', 'E',
    '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
};
static LevelConfig level_02 = LevelConfig(
    LEVEL_NAME, LEVEL_INFO, LEVEL_TIME_LIMIT, LEVEL_SAND_REQUIRED,
    LEVEL_SIZE_X, LEVEL_SIZE_Y, level_02_data
);

#undef LEVEL_NAME
#undef LEVEL_INFO
#undef LEVEL_TIME_LIMIT
#undef LEVEL_SAND_REQUIRED
#undef LEVEL_SIZE_X    
#undef LEVEL_SIZE_Y    

/*! @} */


/*!
 * \name level_03 configuration data
 *
 * FIXME: correct doxygen tags
 * @{
 */
#define LEVEL_NAME          "Level 03"
#define LEVEL_INFO          "Mini"
#define LEVEL_TIME_LIMIT    30
#define LEVEL_SAND_REQUIRED 5               // required sand to eat before exit opens
#define LEVEL_SIZE_X        6
#define LEVEL_SIZE_Y        6
static char level_03_data[LEVEL_SIZE_X * LEVEL_SIZE_Y] =
{
    '#', '#', '#', '#', '#', '#',
    '#', '8', 'O', 'O', 'O', '#',
    '#', '.', 'O', ' ', '.', '#',
    '#', ' ', 'O', ' ', '.', '#',
    '#', ' ', ' ', '.', '.', 'E',
    '#', '#', '#', '#', '#', '#',
};
static LevelConfig level_03 = LevelConfig(
    LEVEL_NAME, LEVEL_INFO, LEVEL_TIME_LIMIT, LEVEL_SAND_REQUIRED,
    LEVEL_SIZE_X, LEVEL_SIZE_Y, level_03_data
);

#undef LEVEL_NAME
#undef LEVEL_INFO
#undef LEVEL_TIME_LIMIT
#undef LEVEL_SAND_REQUIRED
#undef LEVEL_SIZE_X    
#undef LEVEL_SIZE_Y    

/*! @} */

/* FIXME: move to common header */
#define ARRAYSIZE(a) (sizeof(a)/sizeof(*a))

/* level sets */
//static LevelConfig LevelSetA[] = {level_01, level_02};
//static int LevelSetA_size = ARRAYSIZE(LevelSetA);




}       // namespace

#endif  // _SDIG_LEVEL_DATA_H_

