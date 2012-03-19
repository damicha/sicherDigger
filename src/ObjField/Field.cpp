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
 * \details Set field sizes, create and initialize the object field.
 * \param   size_x field size of the dimension x
 * \param   size_y field size of the dimension y
 */
Field::Field(int size_x, int size_y) : mEntries(NULL), mPlayer(NULL), mExit(NULL)
{
    /* set dimensions */
    this->size_x = size_x;
    this->size_y = size_y;
    
    /* get memory for the field entries */
    mEntries = new ObjField::Entry[size_x*size_y];

    /* do final field object initialization */
    initEntries();
    

    /* create materials (sand surrounded with walls)
     * place the player into the left top corner */
    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++)
        {
            if        (x == 1 && y == 1) {
                /* set player position/object */
                // FIXME: put data object creation in a function
                mEntries[y*size_x + x].createDataObject(BaseDOT::player);
                mPlayer = (DOTPlayer *)mEntries[y*size_x + x].getData()->getTypeObject();
                // set back references
                mPlayer->initReferences(this, mEntries[y*size_x + x].getData());
            } else if (x == 1 && y == 0) {
                /* set exit position/object */
                mEntries[y*size_x + x].createDataObject(BaseDOT::exit);
                mExit = (DOTExit *)mEntries[y*size_x + x].getData()->getTypeObject();
                // set back references
                mExit->initReferences(this, mEntries[y*size_x + x].getData());
                // set properties    
                mExit->setRequiredSand(1); 
            } else if (x == 0 || x == size_x - 1 ||
                       y == 0 || y == size_y - 1)
            {
                mEntries[y*size_x + x].createDataObject(BaseDOT::wall);
            } else {
                mEntries[y*size_x + x].createDataObject(BaseDOT::sand);
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
    size_x = pLevelConfig.getSizeX();
    size_y = pLevelConfig.getSizeY();
    
    /* get memory for the field entries */
    mEntries = new ObjField::Entry[size_x*size_y];
    
    /* do final field object initialization */
    initEntries();

    /* create materials */
    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++)
        {
            /* get object type */
            BaseDOT::DOTType objType = pLevelConfig.getData(x, y);
            /* create entry */
            mEntries[y*size_x + x].createDataObject(objType);
            
            /* store the reference of the players object */
            if (objType == BaseDOT::player) {
                mPlayer = (DOTPlayer *)mEntries[y*size_x + x].getData()->getTypeObject();
                // set back references
                mPlayer->initReferences(this, mEntries[y*size_x + x].getData());
            }
            /* store the reference of the exit object */
            if (objType == BaseDOT::exit) {
                mExit = (DOTExit *)mEntries[y*size_x + x].getData()->getTypeObject();
                // set back reference
                mExit->initReferences(this, mEntries[y*size_x + x].getData());
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
    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++)
        {
            // set position information
            mEntries[y*size_x + x].setPosition(x, y);

            // set neighbors
            if (x == 0) {
                mEntries[y*size_x + x].setPrevX(NULL);
            } else {
                mEntries[y*size_x + x].setPrevX(&mEntries[y*size_x + x-1]);
            }
            if (x == size_x-1) {
                mEntries[y*size_x + x].setNextX(NULL);
            } else {
                mEntries[y*size_x + x].setNextX(&mEntries[y*size_x + x+1]);
            }
            if (y == 0) {
                mEntries[y*size_x + x].setPrevY(NULL);
            } else {
                mEntries[y*size_x + x].setPrevY(&mEntries[(y-1)*size_x + x]);
            }
            if (y == size_y-1) {
                mEntries[y*size_x + x].setNextY(NULL);
            } else {
                mEntries[y*size_x + x].setNextY(&mEntries[(y+1)*size_x + x]);
            }
        }
    }
};

