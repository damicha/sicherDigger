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

#include "SDig_BaseDOT.h"
#include "SDig_DataObject.h"
#include "objField.h"

#include "stdio.h"

using namespace SDig;


/*!
 * \brief   Do one iteration on the object field.
 * \param mField
 *          Object field with the objects to modify/move.
 *
 * FIXME: add mechanism to lock source and destination field
 */
void PhysicsEngine::run(objField &pField, MovementType pPlayerMove)
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

    /* move player first */
    {
        objFieldEntry *pl_entry_new;
        pl_entry_new = runPlayerPhysics(pField.pl_entry, pPlayerMove);
        pField.pl_entry = pl_entry_new; 
    }

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

};


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
 * \param e
 *          selected object
 * \return  address of the new object field entry that carries the player
 *
 * Players movement rules:\n
 *  - a player can move if no items block its way
 *
 * FIXME add player commands: move left, right, up, down, push..., pull ...
 * FIXME add usefull subfunction (check, move)
 */
objFieldEntry *PhysicsEngine::runPlayerPhysics(objFieldEntry  *e,
                                               MovementType   pPlayerMove)
{
    /* set default value for the new player object field entry */
    objFieldEntry *pl_entry_new = e;

    /* return if entry is already treated */
    if (e->data->isDone()) {
        return pl_entry_new;
    }

    /* set player object to done */
    e->data->setDone();

    /* move player */
    switch (pPlayerMove)
    {
        /* move to right */
        case MT_RIGHT:
            pl_entry_new = movePlayer(e, e->x_next);
            break;

        /* move to left */
        case MT_LEFT:
            pl_entry_new = movePlayer(e, e->x_prev);
            break;
        
        /* move up */
        case MT_UP:
            pl_entry_new = movePlayer(e, e->y_prev);
            break;

        /* move down */
        case MT_DOWN:
            pl_entry_new = movePlayer(e, e->y_next);
            break;

        // FIXME: there shouldn't be a default state
        default:
            break;

    } // switch m

    return pl_entry_new; 

};


objFieldEntry *PhysicsEngine::movePlayer(objFieldEntry  *pSrc, objFieldEntry *pDest)
{
    /* set default value for the new player object field entry */
    objFieldEntry *plEntryNew = pSrc;

    /* move the player if it is not blocked */
    if (pDest && pDest->data->isDone() == false &&
        isBlocking(pDest) == false)
    {
        /* eat sand */
        if (isSand(pDest)) {
            delete pDest->data;
            pDest->data = new DataObject(BaseDOT::empty);
        }

        /* enter exit */
        if (isExit(pDest)) {
            delete pDest->data;
            pDest->data = new DataObject(BaseDOT::empty);
            // FIXME: change player to exiting player and exit level !
        }

        /* the empty field to done */
        pDest->data->setDone();

        /* move player by switch the data objects */
        switchDataObjects(pSrc, pDest);

        /* update the address of the object field entry that contains
         * the player data */
        plEntryNew = pDest;
    }

    return plEntryNew;
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
    pDest->data = doSrc;
}




