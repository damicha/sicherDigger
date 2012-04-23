/******************************************************************************/
/*!
 * \file    LevelConfig.h
 * \brief   Declaration of the LevelConfig class to store level
 *  configuration data.
 * 
 * \author  damicha of defect
 * \date    2012
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_LEVEL_CONFIG_H_
#define _SDIG_LEVEL_CONFIG_H_

#include "DOT/Base.h"

#include <string>
#include <string.h>     // memcpy

namespace SDig {

/*!
 * \class   LevelConfig
 * \brief   Is able to store a configuration of a single game level as an
 *  array of characters and the game's configuration data like time limit,
 *  sizes, etc.
 */
class LevelConfig
{
/* ======== class attributes ======== */    
private:
    string mName;   /*!< Level name */
    string mInfo;   /*!< Level information string */
    int mTimeLimit; /*!< Time limit of the level. */
    int mSandReq;   /*!< Required sand to eat before the exit opens */
    int mSizeX;     /*!< X size of the level */
    int mSizeY;     /*!< Y size of the level */
    char *mData;    /*!< Character array that contains the level data. */

/* ======== class init functions ======== */
public:
    /* Constructor */
    LevelConfig(const string &pName, const string &pInfo,
                int pTimeLimit, int pSandReq,
                int pSizeX, int pSizeY,
                const char *pData);

    /* Copy Constructor */
    LevelConfig(const LevelConfig &pLevelConfig);

    /* Destructor */
    ~LevelConfig();
    

public:
/* ======== functions to get private member values ======== */
    
    /*! \brief   Get the name of the level. */
    string getName() const {
        return mName;
    }
    
    /*! \brief   Get level information. */
    string getInfo() const {
        return mInfo;
    }
    
    /*! \brief   Get the time limit of the level. */
    int getTimeLimit() const {
        return mTimeLimit;
    }
    
    /*! \brief   Get required amount of sand to open the exit. */
    int getRequiredSand() const {
        return mSandReq;
    }
    
    /*! \brief   Get the X size of the level. */
    int getSizeX() const {
        return mSizeX;
    }
    
    /*! \brief   Get the Y size of the level. */
    int getSizeY() const {
        return mSizeY;
    }

    /* Get the type of the object that is stored on position X, Y
     * in the level configuration array. */
    DOT::Type getData(int pX, int pY) const;

};


}       // namespace

#endif  // _SDIG_LEVEL_CONFIG_H_
