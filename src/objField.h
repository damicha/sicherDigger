/******************************************************************************/
/*!
 * \file    objField.h
 * \brief   handels a 2 dimensional field of class objFieldEntry objects
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 * \todo add obj type (physic, gfx(txt output) ) as a member of objFieldEntry->obj
 * \todo add a configuration class 
 *
 ******************************************************************************/

// FIXME: in general do only function declarations -> move implementation to *.cpp file

#ifndef _OBJ_FIELD_H_
#define _OBJ_FIELD_H_


#include "SDig_BaseDOT.h"
#include "SDig_DOTs.h"
#include "objFieldEntry.h"
#include "SDig_LevelConfig.h"

using namespace std;
using namespace SDig;


class objField;
//class DOTPlayer;

/*!
 * \class   objField 
 */
class objField
{

/* ======== class types ======== */
public:

/* ======== class attributes ======== */
public:
    int size_x;     /*!< size of the field dimension x */
    int size_y;     /*!< size of the field dimension y */
    objFieldEntry   *entries;   /*!< reference to an array of the object field entries */
    // FIXME: store reference to DOTPlayer, DOTExit objects
    DataObject      *mPlayer;   /*!< reference to the player's data object */
    DataObject      *mExit;     /*!< reference to the exit's data object */

/* ======== class init functions ======== */
public:
    /*!
     * \brief   Constructor
     * \details Set field sizes, create and initialize the object field.
     * \param   size_x field size of the dimension x
     * \param   size_y field size of the dimension y
     */
    objField(int size_x, int size_y) : entries(NULL), mPlayer(NULL), mExit(NULL)
    {
        /* set dimensions */
        this->size_x = size_x;
        this->size_y = size_y;
        
        /* get memory for the field entries */
        entries = new objFieldEntry[size_x*size_y];

        /* do final field object initialization */
        initObj();
        

        /* create materials (sand surrounded with walls)
         * place the player into the left top corner */
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
                if        (x == 1 && y == 1) {
                    /* set player position/object */
                    entries[y*size_x + x].createDataObject(BaseDOT::player);
                    mPlayer = entries[y*size_x + x].data;
                } else if (x == 1 && y == 0) {
                    /* set exit position/object */
                    entries[y*size_x + x].createDataObject(BaseDOT::exit);
                    mExit = entries[y*size_x + x].data;
                } else if (x == 0 || x == size_x - 1 ||
                           y == 0 || y == size_y - 1)
                {
                    entries[y*size_x + x].createDataObject(BaseDOT::wall);
                } else {
                    entries[y*size_x + x].createDataObject(BaseDOT::sand);
                }
            }
        }
    };

    /*!
     * \brief   Constructor
     * \details Initializes the field with the given configuration.
     * \param   cfg configuration
     * FIXME: move function implementation to *.cpp
     */
    objField(const LevelConfig &pLevelConfig)
    {
        /* set dimensions */
        size_x = pLevelConfig.getSizeX();
        size_y = pLevelConfig.getSizeY();
        
        /* get memory for the field entries */
        entries = new objFieldEntry[size_x*size_y];
        
        /* do final field object initialization */
        initObj();

        /* create materials */
        // FIXME move player info data and functions to player class dotPlayer
        for (int y = 0; y < size_y; y++)
        {
            for (int x = 0; x < size_x; x++)
            {
                /* get object type */
                BaseDOT::DOTType objType = pLevelConfig.getData(x, y);
                /* create entry */
                entries[y*size_x + x].createDataObject(objType);
                
                /* store the reference of the players object */
                if (objType == BaseDOT::player) {
                    mPlayer = entries[y*size_x + x].data;
                    // set back reference
                    SDig::DOTPlayer *player = (DOTPlayer *)mPlayer->getTypeObject();
                    player->setFieldReference(this);
                }
                /* store the reference of the exit object */
                if (objType == BaseDOT::exit) {
                    mExit = entries[y*size_x + x].data;
                    // set back reference
                    SDig::DOTExit *exit = (DOTExit *)mExit->getTypeObject();
                    exit->setFieldReference(this);
                    // set properties    
                    exit->setRequiredSand(pLevelConfig.getRequiredSand()); 
                }
            }
        }

    };
    
    /*!\brief   Get player's state. */
    DOTPlayer::StateType getPlayerState(void)
    {
        SDig::DOTPlayer *player = (DOTPlayer *)mPlayer->getTypeObject();
        return player->getState();
    }
    
    /*!\brief   Get exit's state. */
    DOTExit::StateType getExitState(void)
    {
        SDig::DOTExit *exit = (DOTExit *)mExit->getTypeObject();
        return exit->getState();
    }

    /*!
     * \brief   Destructor
     */
    ~objField() {
        delete [] entries;   
    }


    /*!
     * \brief   Initialize the field objects.
     * \details Set field object data (field position, neighbors).
     */
    void initObj();

};

#endif
