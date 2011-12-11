/******************************************************************************/
/*!
 * \file    SDig_LevelConfig.h
 * \brief   Stores the configuration of a single game level as an array of
 *          characters
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_LEVEL_CONFIG_H_
#define _SDIG_LEVEL_CONFIG_H_

#include "SDig_BaseDOT.h"

//#include <string>
#include <string.h>

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
// FIXME: make attr. to private members 
private:
    string mName;   /*!< Level name */
    int mTimeLimit; /*!< Time limit of the level in seconds. */
    int mSizeX;     /*!< X size of the level */
    int mSizeY;     /*!< Y size of the level */
    char *mData;    /*!< Character array that contains the level data. */

/* ======== class init functions ======== */
public:
    /*!
     * \brief   Constructor
     * \details Set level sizes, create and initialize the level data.
     * \param   pName
     *  The name of the level.
     * \param   pSizeX
     *  Level size of the dimension x.
     * \param   pSizeY
     *  Level size of the dimension y.
     * \param   pData
     *  Character array with the level configuration.
     */
    LevelConfig(const string &pName, int pTimeLimit,
                int pSizeX, int pSizeY,
                const char *pData) :
        /* set configuration name and time limit */
        mName(pName), mTimeLimit(pTimeLimit),
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
        /* set configuration name and time limit */
        mName(pLevelConfig.mName), mTimeLimit(pLevelConfig.mTimeLimit),
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
    }   // FIXME return a reference (&) ???
    
    /*! \brief   Get the time limit of the level. */
    int getTimeLimit() const {
        return mTimeLimit;
    }
    
    /*! \brief   Get the X size of the level. */
    int getSizeX() const {
        return mSizeX;
    }
    
    /*! \brief   Get the Y size of the level. */
    int getSizeY() const {
        return mSizeY;
    }
#if 0
    char *getData() const   { return mData; }   // FIXME: don't provide the data array!
    // FIXME provide a function that copy the levelData to field Data
#endif

    /*!
     * \brief   Get the type of the object that is stored as position X, Y
     *  in the level configuration array.
     * \param   pX, pY
     *  Positions.
     */
    BaseDOT::DOTType getData(int pX, int pY) const
    {
        switch (mData[pY*mSizeX + pX])
        {
            case '#':
                return BaseDOT::wall;
            case '.':
                return BaseDOT::sand;
            case ' ':
                return BaseDOT::empty;
            case 'O':
                return BaseDOT::stone;
            case '8':
                /* set player position/object */
                return BaseDOT::player;
            case 'E':
                return BaseDOT::exit;
            default:
                return BaseDOT::unknown;
        }
     }

};


}       // namespace

#endif  // _SDIG_LEVEL_CONFIG_H_
