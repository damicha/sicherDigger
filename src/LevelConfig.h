/******************************************************************************/
/*!
 * \file    LevelConfig.h
 * \brief   Stores the configuration of a single game level as an array of
 *          characters
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

using namespace std;


namespace SDig {

/*!
 * \class   LevelConfig
 * \brief   Is able to store a configuration of a single game level as an
 *          array of characters.
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
    /*!
     * \brief   Constructor
     * \details Set level sizes, create and initialize the level data.
     * \param[in] pName       The name of the level.
     * \param[in] pInfo       Level information string.
     * \param[in] pTimeLimit  Time limit of the level.
     * \param[in] pSandReq    Required amount of eaten sand to open the exit.
     * \param[in] pSizeX      Level size of the dimension x.
     * \param[in] pSizeY      Level size of the dimension y.
     * \param[in] pData       Character array with the level configuration.
     */
    LevelConfig(const string &pName, const string &pInfo,
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
     */
    LevelConfig(const LevelConfig &pLevelConfig) :
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
    ~LevelConfig() {
        /* destroy the level data array */
        delete [] mData;
    }
    

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

    /*!
     * \brief   Get the type of the object that is stored on position X, Y
     *  in the level configuration array.
     * \param[in]   pX, pY  x,y coordinates
     */
    DOT::Type getData(int pX, int pY) const
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

};


}       // namespace

#endif  // _SDIG_LEVEL_CONFIG_H_
