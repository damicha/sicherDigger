/******************************************************************************/
/*!
 * \file    SDig_DOTs.h
 * \brief   Declarations of data object type classes; derivated from the
 *          class SDig_BaseDOT.
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#ifndef _SDIG_DOTS_H_
#define _SDIG_DOTS_H_

#include "SDig_BaseDOT.h"

#include <string>


using namespace std;

namespace SDig {


/*!
 * \class   DOTWall
 * \brief   Declaration of the data object type class: wall. 
 */
class DOTWall : public BaseDOT
{

public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTWall() {
        mName = string("Wall");
        setType(wall);
//        printf("%s: %s\n", __func__, getName().c_str());
    }
};


/*!
 * \class   DOTSand
 * \brief   Declaration of the data object type class: sand.
 */
class DOTSand : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTSand() {
        mName = string("Sand");
        setType(sand);
    };
};


/*!
 * \class   DOTEmpty
 * \brief   Declaration of the data object type class: empty.
 */
class DOTEmpty : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTEmpty() {
        mName = string("Empty");
        setType(empty);
    };
};


/*!
 * \class   DOTStone 
 * \brief   Declaration of the data object type class: stone.
 */
class DOTStone : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTStone() {
        mName = string("Stone");
        setType(stone);
    };
};


/*!
 * \class   DOTPlayer
 * \brief   Declaration of the data object type class: player.
 */
class DOTPlayer : public BaseDOT
{
private:
    /* Flags */
    bool mExiting;   //! exiting flag
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTPlayer()
    {
        mName = string("Player");
        setType(player);
        
        /* set local class members */
        mExiting = false;
    };

    bool isExiting(void) {
        return mExiting;
    }

    void setExiting(bool pExiting) {
        mExiting = pExiting;
    }
};


/*!
 * \class   DOTExit
 * \brief   Declaration of the data object type class: exit.
 */
class DOTExit : public BaseDOT
{
public:
    /*!
     * \brief   constructor
     * \details Define constant class attributes.
     */
    DOTExit() {
        mName = string("Exit");
        setType(exit);
    };
};


}       // namespace

#endif
