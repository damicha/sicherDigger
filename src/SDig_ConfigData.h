/******************************************************************************/
/*!
 * \file    SDig_ConfigData.h
 * \brief   Field configuration data
 *          FIXME: Include only once!
 *
 * \author  damicha of defect
 * \date    2011
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_CONFIG_DATA_H_
#define _SDIG_CONFIG_DATA_H_


#include "SDig_LevelConfig.h"

namespace SDig {

/*!
 * \name field_a configuration data
 *
 * FIXME: correct doxygen tags
 * @{
 */
#define LEVEL_NAME          "field_a"
#define LEVEL_TIME_LIMIT    25
#define LEVEL_SIZE_X        8
#define LEVEL_SIZE_Y        8
char field_a_data[LEVEL_SIZE_X * LEVEL_SIZE_Y] =
{
    '#', '#', '#', '#', '#', '#', '#', '#',
    '#', 'O', 'O', 'O', 'O', 'O', ' ', '#',
    '#', 'O', 'O', '.', ' ', ' ', 'O', '#',
    '#', 'O', '.', 'O', ' ', '8', '.', '#',
    '#', '.', ' ', ' ', 'O', ' ', '.', '#',
    '#', '.', ' ', '.', ' ', 'O', ' ', '#',
    '#', '.', ' ', '.', ' ', ' ', 'O', '#',
    '#', '#', '#', '#', '#', '#', '#', '#',
};
LevelConfig field_a = LevelConfig(
    LEVEL_NAME, LEVEL_TIME_LIMIT,
    LEVEL_SIZE_X, LEVEL_SIZE_Y, field_a_data
);

#undef LEVEL_NAME
#undef LEVEL_TIME_LIMIT
#undef LEVEL_SIZE_X    
#undef LEVEL_SIZE_Y    

/*! @} */


}       // namespace

#endif  // _SDIG_CONFIG_DATA_H_

