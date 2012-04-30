/******************************************************************************/
/*!
 * \file    LevelConfig.cpp
 * \brief   Implementation of the LevelConfig class to store level
 *  configuration data.
 * 
 * \author  damicha of defect
 * \date    2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "DOT/Base.h"
#include "LevelConfig.h"

#include <string>
#include <string.h>     // memcpy

using namespace SDig;

/* ==========================================================================
* init functions
* ========================================================================== */

/*!
 * \brief   Constructor
 * \details Set level sizes, create and initialize the level data.
 * \param[in] pName      The name of the level.
 * \param[in] pInfo      Level information string.
 * \param[in] pTimeLimit  Time limit of the level.
 * \param[in] pSandReq    Required amount of eaten sand to open the exit.
 * \param[in] pSizeX      Level size of the dimension x.
 * \param[in] pSizeY      Level size of the dimension y.
 * \param[in] *pData      Character array with the level configuration.
 */
LevelConfig::LevelConfig(const string &pName, const string &pInfo,
                         int pTimeLimit, int pSandReq,
                         int pSizeX, int pSizeY,
                         const char *pData) :
    /* set configuration names and limits */
    mName(pName), mInfo(pInfo), mTimeLimit(pTimeLimit), mSandReq(pSandReq),
    /* set array dimensions */
    mSizeX(pSizeX), mSizeY(pSizeY)
{
    /* create configuration array */
    mData = new char[mSizeX * mSizeY];

    /* check and copy */
    // FIXME: check
    int cnt = 0;
    for (int y = 0; y < mSizeY; y++) {
        for (int x = 0; x < mSizeX; x++) {
            mData[cnt] = pData[cnt];
            cnt++;
        }
    }
}


/*!
 * \brief   Copy Constructor
 * \param[in] pLevelConfig  Configuration to copy.
 */
LevelConfig::LevelConfig(const LevelConfig &pLevelConfig) :
    /* set configuration names and limits */
    mName(pLevelConfig.mName), mInfo(pLevelConfig.mInfo),
    mTimeLimit(pLevelConfig.mTimeLimit), mSandReq(pLevelConfig.mSandReq),
    /* set array dimensions */
    mSizeX(pLevelConfig.mSizeX), mSizeY(pLevelConfig.mSizeY)
{
    /* create a new configuration array */
    mData = new char[mSizeX * mSizeY];

    /* copy */
    memcpy(mData, pLevelConfig.mData, sizeof(char) * mSizeX * mSizeY);
}


/*!
 * \brief   Destructor
 */
LevelConfig::~LevelConfig() {
    /* destroy the level data array */
    delete [] mData;
}
    


/* ==========================================================================
 * functions to get private member values
 * ========================================================================== */

/*!
 * \brief   Get the type of the object that is stored on position X, Y
 *  in the level configuration array.
 * \param[in]   pX, pY  x,y coordinates
 */
DOT::Type LevelConfig::getData(int pX, int pY) const
{
    switch (mData[pY*mSizeX + pX])
    {
        case '#':
            return DOT::T_WALL;
        case '.':
            return DOT::T_SAND;
        case ' ':
            return DOT::T_EMPTY;
        case 'O':
            return DOT::T_STONE;
        case '8':
            /* set player position/object */
            return DOT::T_PLAYER;
        case 'E':
            return DOT::T_EXIT;
        default:
            return DOT::T_UNKNOWN;
    }
}

