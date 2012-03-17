/******************************************************************************/
/*!
 * \file    objField.h
 * \brief   handels a 2 dimensional field of class objFieldEntry objects
 * 
 * \author  damicha of defect
 * \date    2011-2012 
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

using namespace SDig;

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
    DOTPlayer       *mPlayer;   /*!< reference to the player object */
    DOTExit         *mExit;     /*!< reference to the exit object */

/* ======== class init functions ======== */
public:
    /* Constructors */
    objField(int size_x, int size_y);
    objField(const LevelConfig &pLevelConfig);
    
    /*!\brief   Get player's state. */
    DOTPlayer::StateType getPlayerState(void) {
        return mPlayer->getState();
    }
    
    /*!\brief   Get exit's state. */
    DOTExit::StateType getExitState(void) {
        return mExit->getState();
    }

    /*!
     * \brief   Destructor
     */
    ~objField() {
        // FIXME: delete mPlayer and mExit objects and their DOT objects
        // FIXME: delete entry DOT objects
        delete [] entries;   
    }


    /*!
     * \brief   Initialize the field objects.
     * \details Set field object data (field position, neighbors).
     */
    void initObj();

};

#endif
