/******************************************************************************/
/*!
 * \file    LevelConfigSet.cpp
 * \brief   Implementation of the LevelConfigSet class to store and handle a
 *  bunch of level configurations.
 * 
 * \author  damicha of defect
 * \date    2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "LevelConfigSet.h"
#include "LevelConfig.h"

#include <vector>

using namespace SDig;

/* ==========================================================================
 * init functions
 * ========================================================================== */
    
/*!\brief Constructor */
LevelConfigSet::LevelConfigSet(void)
{
    mConfigs = new vector<LevelConfig *>;
}

/* Destructor */
LevelConfigSet::~LevelConfigSet() {
    delete mConfigs;
}
    


/* ==========================================================================
 * function to access the level configurations
 * ========================================================================== */

/*!
 * \brief   Get the number of stored level configurations
 * \return  Number of stored configurations.
 */
int LevelConfigSet::getNumber(void) const {
    return mConfigs->size();
}

/*!
 * \brief   Get a stored level configuration by index
 * \return  Reference to the configuration to get
 */
LevelConfig *LevelConfigSet::getConfig(int idx) const {
    return mConfigs->at(idx);
}

/*!
 * \brief   Add a configuration at the end of the list
 * \param[in] pLevelConfig   Configuration to add
 * \return  New number of the stored configurations.
 */
int LevelConfigSet::addConfig(LevelConfig *pLevelConfig) {
    mConfigs->push_back(pLevelConfig);
    return mConfigs->size();
}



