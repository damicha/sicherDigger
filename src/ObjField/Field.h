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

#ifndef _OBJFIELD_FIELD_H_
#define _OBJFIELD_FIELD_H_

namespace SDig {
namespace ObjField {
    class Field;            // pre-declaration
}
}

#include "DOT/Base.h"
#include "DOT/DOTs.h"
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
private:
    int mSizeX;     /*!< size of the field dimension x */
    int mSizeY;     /*!< size of the field dimension y */
    ObjField::Entry *mEntries;  /*!< reference to an array of the field entries */
    DOT::Player     *mPlayer;   /*!< reference to the player object */
    DOT::Exit       *mExit;     /*!< reference to the exit object */

/* ======== class init/destroy functions ======== */
public:
    /* Constructors */
    Field(int pSizeX, int pSizeY);
    Field(const LevelConfig &pLevelConfig);
    
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

/* ======== class set/get functions ======== */
public:
    /*!\brief   Get size of field's dimension x. */
    int getSizeX(void) const {
        return mSizeX;
    }
    /*!\brief   Get size of field's dimension y. */
    int getSizeY(void) const {
        return mSizeY;
    }
#if 0    
    /*!\brief   Get entry array. */
    ObjField::Entry *getEntryArray(void) const {
        return mEntries;
    }
#endif    
    /*!\brief   Get entry from array via index.
     *\param[in] pIdx   Index of the entry to get.
     */
    ObjField::Entry *getEntry(int pIdx) const {
        return &(mEntries[pIdx]);
    }
    /*!\brief   Get entry from array via coordinates.
     *\param[in] pX x coordinate of the entry to get.
     *\param[in] pY y coordinate of the entry to get.
     */
    ObjField::Entry *getEntry(int pX, int pY) const {
        return &(mEntries[pY*mSizeX + pX]);
    }

    /*!\brief   Get player's object */
    DOT::Player *getPlayer(void) const {
        return mPlayer;
    }
    /*!\brief   Get exits's object */
    DOT::Exit *getExit(void) const {
        return mExit;
    }
    
    
    /*!\brief   Get player's state. */
    DOT::Player::StateType getPlayerState(void) const {
        return mPlayer->getState();
    }
    
    /*!\brief   Get exit's state. */
    DOT::Exit::StateType getExitState(void) const {
        return mExit->getState();
    }


};

}       // namespace ObjField
}       // namespace SDig


#endif
