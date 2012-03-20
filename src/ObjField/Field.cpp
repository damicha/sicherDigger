/******************************************************************************/
/*!
 * \file    Field.cpp
 * \brief   Implementation of the class ObjField::Field.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "ObjField/Entry.h"
#include "ObjField/Field.h"

using namespace SDig;
using namespace SDig::ObjField;


/*!
 * \brief   Constructor
 * \details Set field sizes, create and initialize a default object field
 *  surrounded by walls with one player an one exit.
 *  
 * \param pSizeX    field size of the dimension x
 * \param pSizeY    field size of the dimension y
 */
Field::Field(int pSizeX, int pSizeY) : mEntries(NULL), mPlayer(NULL), mExit(NULL)
{
    /* set dimensions */
    mSizeX = pSizeX;
    mSizeY = pSizeY;
    
    /* get memory for the field entries */
    mEntries = new ObjField::Entry[mSizeX*mSizeY];

    /* do final field object initialization */
    initEntries();
    

    /* create materials (sand surrounded with walls)
     * place the player into the left top corner */
    for (int y = 0; y < mSizeY; y++)
    {
        for (int x = 0; x < mSizeX; x++)
        {
            if        (x == 1 && y == 1) {
                /* set player position/object */
                // FIXME: put data object creation in a function
                mEntries[y*mSizeX + x].createDataObject(BaseDOT::player);
                mPlayer = (DOTPlayer *)mEntries[y*mSizeX + x].getData()->getTypeObject();
                // set back references
                mPlayer->initReferences(this, mEntries[y*mSizeX + x].getData());
            } else if (x == 1 && y == 0) {
                /* set exit position/object */
                mEntries[y*mSizeX + x].createDataObject(BaseDOT::exit);
                mExit = (DOTExit *)mEntries[y*mSizeX + x].getData()->getTypeObject();
                // set back references
                mExit->initReferences(this, mEntries[y*mSizeX + x].getData());
                // set properties    
                mExit->setRequiredSand(1); 
            } else if (x == 0 || x == mSizeX - 1 ||
                       y == 0 || y == mSizeY - 1)
            {
                mEntries[y*mSizeX + x].createDataObject(BaseDOT::wall);
            } else {
                mEntries[y*mSizeX + x].createDataObject(BaseDOT::sand);
            }
        }
    }
}

/*!
 * \brief   Constructor
 * \details Initializes the field with the given configuration.
 * \param pLevelConfig   configuration
 */
Field::Field(const LevelConfig &pLevelConfig)
{
    /* set dimensions */
    mSizeX = pLevelConfig.getSizeX();
    mSizeY = pLevelConfig.getSizeY();
    
    /* get memory for the field entries */
    mEntries = new ObjField::Entry[mSizeX*mSizeY];
    
    /* do final field object initialization */
    initEntries();

    /* create materials */
    for (int y = 0; y < mSizeY; y++)
    {
        for (int x = 0; x < mSizeX; x++)
        {
            /* get object type */
            BaseDOT::DOTType objType = pLevelConfig.getData(x, y);
            /* create entry */
            mEntries[y*mSizeX + x].createDataObject(objType);
            
            /* store the reference of the players object */
            if (objType == BaseDOT::player) {
                mPlayer = (DOTPlayer *)mEntries[y*mSizeX + x].getData()->getTypeObject();
                // set back references
                mPlayer->initReferences(this, mEntries[y*mSizeX + x].getData());
            }
            /* store the reference of the exit object */
            if (objType == BaseDOT::exit) {
                mExit = (DOTExit *)mEntries[y*mSizeX + x].getData()->getTypeObject();
                // set back reference
                mExit->initReferences(this, mEntries[y*mSizeX + x].getData());
                // set properties    
                mExit->setRequiredSand(pLevelConfig.getRequiredSand()); 
            }
        }
    }

};


/*!\brief   Initialize the field entires.
 * References between the entries are set.
 */
void Field::initEntries()
{

    /* initialize all field objects */
    for (int y = 0; y < mSizeY; y++)
    {
        for (int x = 0; x < mSizeX; x++)
        {
            // set position information
            mEntries[y*mSizeX + x].setPosition(x, y);

            // set neighbors
            if (x == 0) {
                mEntries[y*mSizeX + x].setPrevX(NULL);
            } else {
                mEntries[y*mSizeX + x].setPrevX(&mEntries[y*mSizeX + x-1]);
            }
            if (x == mSizeX-1) {
                mEntries[y*mSizeX + x].setNextX(NULL);
            } else {
                mEntries[y*mSizeX + x].setNextX(&mEntries[y*mSizeX + x+1]);
            }
            if (y == 0) {
                mEntries[y*mSizeX + x].setPrevY(NULL);
            } else {
                mEntries[y*mSizeX + x].setPrevY(&mEntries[(y-1)*mSizeX + x]);
            }
            if (y == mSizeY-1) {
                mEntries[y*mSizeX + x].setNextY(NULL);
            } else {
                mEntries[y*mSizeX + x].setNextY(&mEntries[(y+1)*mSizeX + x]);
            }
        }
    }
};

