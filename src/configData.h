/*! ****************************************************************************
 *
 * \file    configData
 * \brief   Field configuration data
 *          FIXME: Include only once!
 *
 * \author  damicha of defect
 * \date    2011
 *
 ******************************************************************************/

#ifndef _SDIG_CONFIG_DATA_H_
#define _SDIG_CONFIG_DATA_H_


#include "config.h"



/*!
 * \name field_a configuration data
 *
 * FIXME: correct doxygen tags
 * @{
 */
#define SIZE_X 8
#define SIZE_Y 8
char field_a_data[SIZE_X*SIZE_Y] =
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
config field_a = config("field_a", SIZE_X, SIZE_Y, field_a_data);

#undef SIZE_X
#undef SIZE_Y

/*! @} */

#endif  // _SDIG_CONFIG_DATA_H_

