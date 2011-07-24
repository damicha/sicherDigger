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
    '#', 'O', 'O', 'O', 'O', 'O', 'O', '#',
    '#', 'O', 'O', '.', ' ', '.', ' ', '#',
    '#', 'O', '.', 'O', ' ', ' ', ' ', '#',
    '#', '.', '.', '.', 'O', ' ', ' ', '#',
    '#', '.', '.', '.', ' ', 'O', ' ', '#',
    '#', '.', '.', '.', ' ', ' ', 'O', '#',
    '#', '#', '#', '#', '#', '#', '#', '#',
};
config field_a = config("field_a", SIZE_X, SIZE_Y, field_a_data);

#undef SIZE_X
#undef SIZE_Y

/*! @} */


