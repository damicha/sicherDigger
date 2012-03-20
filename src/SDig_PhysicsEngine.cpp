/******************************************************************************/
/*!
 * \file    SDig_PhysicsEngine.cpp
 * \brief   Implements the physics of the world.
 *
 * \author  damicha of defect
 * \date    2011
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "SDig_PhysicsEngine.h"

#include "SDig_DOTs.h"
#include "SDig_BaseDOT.h"
#include "SDig_DataObject.h"
#include "ObjField/Field.h"
#include "ObjField/Entry.h"

#include "stdio.h"

using namespace SDig;

    

/*!
 * \brief   Do one iteration on the object field.
 * \param mField
 *  Object field with the objects to modify/move.
 *
 * \return
 *  Currently not used.
 * FIXME: add mechanism to lock source and destination field
 * FIXME: update data->mParentObj after an object was moved !!!
 */
bool PhysicsEngine::run(ObjField::Field *pField, MovementType pPlayerMove)
{

    /* clear dones */
    for (int y = 0; y < pField->getSizeY(); y++)
    {
        for (int x = 0; x < pField->getSizeX(); x++)
        {
            // FIXME remove done from data
            pField->getEntry(x, y)->getData()->clearDone();
        }
    }

    /* increase iteration counter */
    mIterNum++;

    /* decrease time counter */
    mTimeCnt--;

    /* move player first */
    runPlayerPhysics(pField->getPlayer()->getFieldEntry(), pPlayerMove);

    /* run physics on the other field objects */
    for (int y = 0; y < pField->getSizeY(); y++)
    {
        for (int x = 0; x < pField->getSizeX(); x++)
        {
            ObjField::Entry *entry = pField->getEntry(x, y);

            /* call physics functions as a function of the type of the entry data */
            switch (entry->getData()->getType())
            {
                case BaseDOT::stone:
                    runStonePhysics(entry);
                    break;
                case BaseDOT::player:
                    // do nothing, because the player should already be moved
                    break;
                default:
                    break;
            }
        }    
    }

    return false;
}


/*!
 * \brief   Stone physics
 * \param e       
 *          Selected object. The stone to handle.
 *
 * Movement Rules:\n
 *  - a stone falls down if the field under it is free.
 */
void PhysicsEngine::runStonePhysics(ObjField::Entry *e)
{
    /* return if entry is already treated */
    if (e->getData()->isDone()) {
        return;
    }

    /* set stone object to done */
    e->getData()->setDone();

    /* get the entry that is under the stone */
    ObjField::Entry *eNextY = e->getNextY();

    /* if it's empty */
    if (eNextY && eNextY->getData()->isDone() == false &&
        isEmpty(eNextY))
    {
        /* set empty object to done */
        eNextY->getData()->setDone();

        /* let stone fall by switching stone and empty data of the 
           field entries */
        switchDataObjects(e, eNextY);
    }

};




/*!
 * \brief   Player physics
 * \param e     Selected object that contains the player
 * \return  True if the player was moved. 
 *
 * Players movement rules:\n
 *  - a player can move if no items block its way
 *
 * FIXME add player commands: move left, right, up, down, push..., pull ...
 * FIXME add usefull subfunction (check, move)
 */
bool PhysicsEngine::runPlayerPhysics(ObjField::Entry    *e,
                                     MovementType       pPlayerMove)
{
    bool plMoved = false;

    /* return if entry was already treated */
    if (e->getData()->isDone()) {
        return false;
    }

    /* move player as a function of the player state */
    SDig::DOTPlayer *player = (SDig::DOTPlayer *)e->getData()->getTypeObject();
    switch (player->getState())
    {
        /* player is alive */
        case DOTPlayer::ST_ALIVE:
        {
            switch (pPlayerMove)
            {
                /* move to right */
                case MT_RIGHT:
                    // FIXME: set new player with call back function ?
                    plMoved = movePlayer(e, e->getNextX());
                    break;

                /* move to left */
                case MT_LEFT:
                    plMoved = movePlayer(e, e->getPrevX());
                    break;
                
                /* move up */
                case MT_UP:
                    plMoved = movePlayer(e, e->getPrevY());
                    break;

                /* move down */
                case MT_DOWN:
                    plMoved = movePlayer(e, e->getNextY());
                    break;

                /* ... */
                default:
                    break;
            }
            break;
        }

        /* player is exiting the level */
        case DOTPlayer::ST_EXITING:
            break;
        
        /* player has the level exited */
        case DOTPlayer::ST_EXITED:
            break;
    };

    /* proceed internal player states */
    player->run();
    

    /* set player object to done */
    e->getData()->setDone();

    return plMoved; 

};

/*!
 * \brief Move player's data object.
 * \param pPlayerObj    Players object
 * \param pDestObj      The field object to which pPlayerObj shall be moved.
 * \return  Is true if player has been moved.
 */
bool PhysicsEngine::movePlayer(ObjField::Entry *pPlayerObj, ObjField::Entry *pDestObj)
{
    
    /* FIXME: Player destroys exit if it enter it!
     * - remove exit reference from mField
     * - strategy of player object ?
     */


    /* ==== check preconditions ==== */
    /* exit if the destination object doesn't exist or was already handeld */
    if (pDestObj == NULL || pDestObj->getData()->isDone()) {
        return false;
    }

    /* exit if the destination is blocking the player */
    if (isBlocking(pDestObj)) {
        return false;
    }
    
    /* exit if the destination is an closed exit */
    if (isClosedExit(pDestObj)) {
        return false;
    }


    /* ==== move the player ==== */
    /* eat sand (replace by data object: empty) */
    if (isSand(pDestObj)) {
        pDestObj->deleteDataObject();
        pDestObj->createDataObject(BaseDOT::empty);
        DOTPlayer *player = (DOTPlayer *)pPlayerObj->getData()->getTypeObject();
        player->incrSandCnt();
    }

    /* enter exit
     * - Don't destroy the exit, because its members are needed. */
    // FIXME: it was already tested if it's not an exit or if it's not closed
    if (isExit(pDestObj))
    {
        // replace the exit object with an empty one
        pDestObj->createDataObject(BaseDOT::empty);
        /* Change player state to exiting player */
        // FIXME: don't set the state in this subfunction:
        //  - use signal or call back or return code of this function!
        ((DOTPlayer *)pPlayerObj->getData()->getTypeObject())->setState(DOTPlayer::ST_EXITING);
    }

    /* the empty field to done */
    pDestObj->getData()->setDone();

    /* move player by switch the data objects */
    switchDataObjects(pPlayerObj, pDestObj);

    /* player was moved: return true */
    return true;
}

/*!
 * \brief   Check if this object has the type empty.
 */
bool PhysicsEngine::isEmpty(ObjField::Entry *pEntry)
{
    return (pEntry->getData()->getType() == BaseDOT::empty) ? true : false;
}

/*!
 * \brief   Check if this object has the type sand.
 */
bool PhysicsEngine::isSand(ObjField::Entry *pEntry)
{
    return (pEntry->getData()->getType() == BaseDOT::sand) ? true : false;
}

/*!
 * \brief   Check if this object has the type exit.
 */
bool PhysicsEngine::isExit(ObjField::Entry *pEntry)
{
    return (pEntry->getData()->getType() == BaseDOT::exit) ? true : false;
}

/*!
 * \brief   Check if the it's and closed exit..
 */
bool PhysicsEngine::isClosedExit(ObjField::Entry *pEntry)
{
    if (pEntry->getData()->getType() != BaseDOT::exit) {
        /* object is not an exit */
        return false;
    }

    SDig::DOTExit *exit = (SDig::DOTExit *)pEntry->getData()->getTypeObject();
    if (exit->getState() == DOTExit::ST_CLOSED)
    {
        /* exit is closed */
        return true;
    } else {
        /* exit is not closed */
        return false;
    }
}
 
/*!
 * \brief   Check if this object is able to block others.
 * FIXME: give object type properties like blocking, moveable,...
 */
bool PhysicsEngine::isBlocking(ObjField::Entry *pEntry)
{
    if (pEntry->getData()->getType() == BaseDOT::wall    ||
        pEntry->getData()->getType() == BaseDOT::stone)
    {
        return true;
    } else {
        return false;
    }
}

/*!
 * \brief   Switch data objects.
 * FIXME: move to DataObject class
 */
void PhysicsEngine::switchDataObjects(ObjField::Entry *pSrc, ObjField::Entry *pDest)
{
    DataObject  *doSrc     = pSrc->getData();
    DataObject  *doDest    = pDest->getData();
    /* switch references */
    pSrc->setData(doDest);
    pSrc->getData()->setParentObject(pSrc);
    pDest->setData(doSrc);
    pDest->getData()->setParentObject(pDest);
}




