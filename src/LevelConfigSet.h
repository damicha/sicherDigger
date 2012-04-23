/******************************************************************************/
/*!
 * \file    LevelConfigSet.h
 * \brief   Declaration of the LevelConfigSet class to store and handle a
 *  bunch of level configurations.
 * 
 * \author  damicha of defect
 * \date    2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_LEVEL_CONFIG_SET_H_
#define _SDIG_LEVEL_CONFIG_SET_H_

#include "LevelConfig.h"

#include <vector>

namespace SDig {

/*!
 * \class   LevelConfigSet
 * \brief   Is able to store and handle a list of level configurations via an
 *  array.
 */
class LevelConfigSet
{
/* ======== class attributes ======== */    
private:
    vector<LevelConfig>     *mConfigs;  //!< stored level configurations

/* ======== class init functions ======== */
public:
    /* Constructor */
    LevelConfigSet(void);

    /* Destructor */
    ~LevelConfigSet();
    
/* ======== function to access the level configurations ======== */
public:

    /* Get the number of stored level configurations */
    int getNumber(void) const;

    /* Get a stored level configuration by index */
    LevelConfig *getConfig(int idx) const;

    /* Add a configuration */
    int addConfig(LevelConfig *pLevelConfig);

};


}       // namespace

#endif  // _SDIG_LEVEL_CONFIG_SET_H_
