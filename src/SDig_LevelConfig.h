/*!
 * \file    SDig_LevelConfig.h
 * \brief   Stores the configuration of a single game level as an array of
 *  characters
 * 
 * \author  damicha of defect
 * \date    2011 
 */

#ifndef _SDIG_LEVEL_CONFIG_H_
#define _SDIG_LEVEL_CONFIG_H_

#include <string>

#include <string.h>

using namespace std;


namespace SDig {

/*
 * \class LevelConfig
 */
class LevelConfig
{
/* ======== class attributes ======== */    
// FIXME: make attr. to private members 
private:
    string mName;   /*!< Level name */
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
    LevelConfig(const string &pName,
                int pSizeX, int pSizeY,
                const char *pData) :
        /* set configuration name */
        mName(pName),
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
        /* set configuration name */
        mName(pLevelConfig.mName),
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
    string getName() const  { return mName; }   // FIXME return a reference (&) ???
    
    /*! \brief   Get the X size of the level. */
    int getSizeX() const    { return mSizeX; }
    
    /*! \brief   Get the Y size of the level. */
    int getSizeY() const    { return mSizeY; }

    char *getData() const   { return mData; }   // FIXME: don't provide data!
    // FIXME provide a function that copy the levelData to field Data

};


}       // namespace

#endif  // _SDIG_LEVEL_CONFIG_H_
