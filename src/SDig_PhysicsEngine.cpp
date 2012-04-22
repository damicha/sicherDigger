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

#include "DOT/DOTs.h"
#include "DOT/Base.h"
#include "ObjField/Field.h"
#include "ObjField/Entry.h"
#include "SDig_DataObject.h"

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

    /* decrease timer counter if timer is enabled */
    if (mTimerEnable == true) {
        mTimerCnt--;
    }

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
                case DOT::T_STONE:
                    runStonePhysics(entry);
                    break;
                case DOT::T_PLAYER:
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
        DataObject::swapDataObjects(e, eNextY);
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
    DOT::Player *player = (DOT::Player *)e->getData()->getTypeObject();
    switch (player->getState())
    {
        /* player is alive */
        case DOT::Player::ST_ALIVE:
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
        case DOT::Player::ST_EXITING:
            break;
        
        /* player has the level exited */
        case DOT::Player::ST_EXITED:
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
        pDestObj->createDataObject(DOT::T_EMPTY);
        DOT::Player *player = (DOT::Player *)pPlayerObj->getData()->getTypeObject();
        player->incrSandCnt();
    }

    /* enter exit
     * - Don't destroy the exit, because its members are needed. */
    // FIXME: it was already tested if it's not an exit or if it's not closed
    if (isExit(pDestObj))
    {
        // replace the exit object with an empty one
        pDestObj->createDataObject(DOT::T_EMPTY);
        /* Change player state to exiting player */
        // FIXME: don't set the state in this subfunction:
        //  - use signal or call back or return code of this function!
        ((DOT::Player *)pPlayerObj->getData()->getTypeObject())->setState(DOT::Player::ST_EXITING);
    }

    /* the empty field to done */
    pDestObj->getData()->setDone();

    /* move player by switch the data objects */
    DataObject::swapDataObjects(pPlayerObj, pDestObj);

    /* player was moved: return true */
    return true;
}

/*!
 * \brief   Check if this object has the type empty.
 */
bool PhysicsEngine::isEmpty(ObjField::Entry *pEntry)
{
    return (pEntry->getData()->getType() == DOT::T_EMPTY) ? true : false;
}

/*!
 * \brief   Check if this object has the type sand.
 */
bool PhysicsEngine::isSand(ObjField::Entry *pEntry)
{
    return (pEntry->getData()->getType() == DOT::T_SAND) ? true : false;
}

/*!
 * \brief   Check if this object has the type exit.
 */
bool PhysicsEngine::isExit(ObjField::Entry *pEntry)
{
    return (pEntry->getData()->getType() == DOT::T_EXIT) ? true : false;
}

/*!
 * \brief   Check if the it's and closed exit..
 */
bool PhysicsEngine::isClosedExit(ObjField::Entry *pEntry)
{
    if (pEntry->getData()->getType() != DOT::T_EXIT) {
        /* object is not an exit */
        return false;
    }

    DOT::Exit *exit = (DOT::Exit *)pEntry->getData()->getTypeObject();
    if (exit->getState() == DOT::Exit::ST_CLOSED)
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
    if (pEntry->getData()->getType() == DOT::T_WALL ||
        pEntry->getData()->getType() == DOT::T_STONE)
    {
        return true;
    } else {
        return false;
    }
}




