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
#include "objField.h"

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
bool PhysicsEngine::run(objField &pField, MovementType pPlayerMove)
{

    /* clear dones */
    for (int y = 0; y < pField.size_y; y++)
    {
        for (int x = 0; x < pField.size_x; x++)
        {
            // FIXME remove done from data
            pField.entries[y*pField.size_x + x].data->clearDone();
        }
    }

    /* increase iteration counter */
    mIterNum++;

    /* decrease time counter */
    mTimeCnt--;

    /* move player first */
    runPlayerPhysics(pField.mPlayer->getParentObject(), pPlayerMove);

    /* run physics on the other field objects */
    for (int y = 0; y < pField.size_y; y++)
    {
        for (int x = 0; x < pField.size_x; x++)
        {
            objFieldEntry *entry = &(pField.entries[y*pField.size_x + x]);

            /* call physics functions as a function of the type of the entry data */
            switch (entry->data->getType())
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
void PhysicsEngine::runStonePhysics(objFieldEntry *e)
{
    /* return if entry is already treated */
    if (e->data->isDone()) {
        return;
    }

    /* set stone object to done */
    e->data->setDone();

    /* get the entry that is under the stone */
    objFieldEntry *e_y_next = e->y_next;

    /* if it's empty */
    if (e_y_next && e_y_next->data->isDone() == false &&
        isEmpty(e_y_next))
    {
        /* set empty object to done */
        e_y_next->data->setDone();

        /* let stone fall by switching stone and empty data of the 
           field entries */
        switchDataObjects(e, e_y_next);
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
bool PhysicsEngine::runPlayerPhysics(objFieldEntry  *e,
                                     MovementType   pPlayerMove)
{
    bool plMoved = false;

    /* return if entry was already treated */
    if (e->data->isDone()) {
        return false;
    }

    /* move player as a function of the player state */
    SDig::DOTPlayer *player = (SDig::DOTPlayer *)e->data->getTypeObject();
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
                    plMoved = movePlayer(e, e->x_next);
                    break;

                /* move to left */
                case MT_LEFT:
                    plMoved = movePlayer(e, e->x_prev);
                    break;
                
                /* move up */
                case MT_UP:
                    plMoved = movePlayer(e, e->y_prev);
                    break;

                /* move down */
                case MT_DOWN:
                    plMoved = movePlayer(e, e->y_next);
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
    e->data->setDone();

    return plMoved; 

};

/*!
 * Move player's data object.
 * \param   pDest   The field to which the player (pSrc) shall be moved.
 * \return  Is true if player has been moved.
 */
bool PhysicsEngine::movePlayer(objFieldEntry  *pSrc, objFieldEntry *pDest)
{
    /* set default value for the new player object field entry */
    objFieldEntry *plEntryNew = pSrc;

    
    /* FIXME: Player destroys exit if it enter it!
     * - remove exit reference from mField
     * - strategy of player object ?
     */


    /* ==== check preconditions ==== */
    /* exit if the destination object doesn't exist or was already handeld */
    if (pDest == NULL || pDest->data->isDone()) {
        return false;
    }

    /* exit if the destination is blocking the player */
    if (isBlocking(pDest)) {
        return false;
    }
    
    /* exit if the destination is an closed exit */
    if (isClosedExit(pDest)) {
        return false;
    }


    /* ==== move the player ==== */
    /* eat sand (replace by data object: empty) */
    if (isSand(pDest)) {
        delete pDest->data;
        pDest->data = new DataObject(pDest, BaseDOT::empty);
        mSandCnt++;
    }

    /* enter exit (replace by data object empty)
     * FIXME: connect exit to players object as parent object */
    // FIXME: it was already tested if it's not an exit or if it's not closed */
    if (isExit(pDest))
    {
        delete pDest->data;
        pDest->data = new DataObject(pDest, BaseDOT::empty);
        /* Change player state to exiting player */
        // FIXME: don't set the state in this subfunction:
        //  - use signal or call back or return code of this function!
        ((SDig::DOTPlayer *)pSrc->data->getTypeObject())->setState(DOTPlayer::ST_EXITING);
    }

    /* the empty field to done */
    pDest->data->setDone();

    /* move player by switch the data objects */
    switchDataObjects(pSrc, pDest);

#if 0
    /* update the address of the object field entry that contains
     * the player data */
    plEntryNew = pDest;
#endif

    return true;
}

/*!
 * \brief   Check if this object has the type empty.
 */
bool PhysicsEngine::isEmpty(objFieldEntry *pEntry)
{
    return (pEntry->data->getType() == BaseDOT::empty) ? true : false;
}

/*!
 * \brief   Check if this object has the type sand.
 */
bool PhysicsEngine::isSand(objFieldEntry *pEntry)
{
    return (pEntry->data->getType() == BaseDOT::sand) ? true : false;
}

/*!
 * \brief   Check if this object has the type exit.
 */
bool PhysicsEngine::isExit(objFieldEntry *pEntry)
{
    return (pEntry->data->getType() == BaseDOT::exit) ? true : false;
}

/*!
 * \brief   Check if the it's and closed exit..
 */
bool PhysicsEngine::isClosedExit(objFieldEntry *pEntry)
{
    if (pEntry->data->getType() != BaseDOT::exit) {
        /* object is not an exit */
        return false;
    }

    SDig::DOTExit *exit = (SDig::DOTExit *)pEntry->data->getTypeObject();
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
bool PhysicsEngine::isBlocking(objFieldEntry *pEntry)
{
    if (pEntry->data->getType() == BaseDOT::wall    ||
        pEntry->data->getType() == BaseDOT::stone)
    {
        return true;
    } else {
        return false;
    }
}

/*!
 * \brief   Switch data objects.
 */
void PhysicsEngine::switchDataObjects(objFieldEntry *pSrc, objFieldEntry *pDest)
{
    DataObject  *doSrc     = pSrc->data;
    DataObject  *doDest    = pDest->data;
    /* switch */
    pSrc->data  = doDest;
    pSrc->data->setParentObject(pSrc);
    pDest->data = doSrc;
    pDest->data->setParentObject(pDest);
}




