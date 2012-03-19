/******************************************************************************/
/*!
 * \file    ObjField/Field.h
 * \brief   Handels a 2 dimensional field of class ObjField::Entry objects
 * 
 * \author  damicha of defect
 * \date    2011-2012 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

// FIXME: in general do only function declarations -> move implementation to *.cpp file

#ifndef _OBJFIELD_FIELD_H_
#define _OBJFIELD_FIELD_H_

namespace SDig {
namespace ObjField {
    class Field;            // pre-declaration
}
}

#include "SDig_BaseDOT.h"
#include "SDig_DOTs.h"
#include "SDig_LevelConfig.h"
#include "ObjField/Entry.h"


namespace SDig {
/*!\brief The namespace ObjField stores the object field classes. */
namespace ObjField {


/*!
 * \class   Field 
 * The Field class provides a field (x,y) of entries.
 */
class Field
{

/* ======== class types ======== */
public:

/* ======== class attributes ======== */
//FIXME: make members as private
public:
    int size_x;     /*!< size of the field dimension x */
    int size_y;     /*!< size of the field dimension y */
    ObjField::Entry *mEntries;  /*!< reference to an array of the field entries */
    DOTPlayer       *mPlayer;   /*!< reference to the player object */
    DOTExit         *mExit;     /*!< reference to the exit object */

/* ======== class init functions ======== */
public:
    /* Constructors */
    Field(int size_x, int size_y);
    Field(const LevelConfig &pLevelConfig);
    
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
    ~Field() {
        // FIXME: delete mPlayer and mExit objects and their DOT objects
        // FIXME: delete entry DOT objects
        delete [] mEntries;   
    }


    /* Initialize the field entries. */
    void initEntries();

};

}       // namespace ObjField
}       // namespace SDig


#endif
