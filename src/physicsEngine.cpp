/******************************************************************************/
/*!
 * \file    physicsEngine.cpp
 * \brief   Implements the physics of the world.
 *
 * \author  damicha of defect
 * \date    2011
 *
 ******************************************************************************/

#include "physicsEngine.h"

#include "baseDataObjectType.h"
#include "dataObject.h"
#include "objField.h"

#include "stdio.h"

using namespace std;


/*!
 * \brief   Do one iteration on the object field.
 * \param field
 *          Object field with the objects to modify/move.
 *
 * FIXME: add mechanism to lock source and destination field
 * FIXME: add player movement
 */
void physicsEngine::run(objField &field, int mx)
{

    /* clear dones */
    for (int y = 0; y < field.size_y; y++)
    {
        for (int x = 0; x < field.size_x; x++)
        {
            // FIXME remove done from data
            field.entries[y*field.size_x + x].data->done = 0;
        }
    }

    iter_num++;

    /* move player first */
    {
        objFieldEntry *pl_entry_new;
        pl_entry_new = playerPhysics(field.pl_entry, mx, 0);
        field.pl_entry = pl_entry_new; 
    }

    /* run physics on the other field objects */
    for (int y = 0; y < field.size_y; y++)
    {
        for (int x = 0; x < field.size_x; x++)
        {
            objFieldEntry *entry = &(field.entries[y*field.size_x + x]);

            /* call physics functions as a function of the type of the entry data */
            switch (entry->data->type->getType())
            {
                case baseDataObjectType::stone:
                    stonePhysics(entry);
                    break;
                case baseDataObjectType::player:
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
void physicsEngine::stonePhysics(objFieldEntry *e)
{
    /* return if entry is already treated */
    if (e->data->done == 1) {
        return;
    }

    /* set stone object to done */
    e->data->done = 1;

    /* get the entry that is under the stone */
    objFieldEntry *e_y_next = e->y_next;

    /* if it's empty */
    if (e_y_next &&
        e_y_next->data->done != 1 &&
        e_y_next->data->type->getType() == baseDataObjectType::empty)
    {
        /* let stone fall by switching stone and empty data of the 
           field entries */
        dataObject  *do_src     = e->data;
        dataObject  *do_dest    = e_y_next->data;
        // do_src->done    = 1;        // set stone object done
        do_dest->done   = 1;        // set empty object done
        /* switch */
        e->data         = do_dest;
        e_y_next->data  = do_src;
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
 * FIXME cleanup like in stonePhysics
 * FIXME add usefull subfunction
 */
objFieldEntry *
physicsEngine::playerPhysics(objFieldEntry *e, int x, int y)
{
    /* set default value for the new player object field entry */
    objFieldEntry *pl_entry_new = e;

    /* return if entry is already treated */
    if (e->data->done == 1) {
        return pl_entry_new;
    }

    /* set player object to done */
    e->data->done = 1;

    /* move right */
    if      (x ==  1)
    {
        /* get the entry that is on the right side of the player */
        objFieldEntry *e_x_next = e->x_next;

        /* move the player if it is not blocked */
        if (e_x_next &&
            e_x_next->data->done != 1 &&
            e_x_next->data->type->getType() != baseDataObjectType::stone &&
            e_x_next->data->type->getType() != baseDataObjectType::wall)
        {
            /* move player by switching the object field entry data */
            dataObject  *do_src     = e->data;
            dataObject  *do_dest    = e_x_next->data;
            /* eat sand */
            if (do_dest->type->getType() == baseDataObjectType::sand) {
                delete do_dest;
                do_dest = new dataObject(baseDataObjectType::empty);
            }
            do_dest->done   = 1;        // set other object done
            /* switch */
            e->data           = do_dest;
            e_x_next->data    = do_src;

            /* update the address of the object field entry that contains
             * the player data */
            pl_entry_new = e_x_next;
        }
    }
    /* move left */
    else if (x == -1)
    {
        /* get the entry that is on the left side of the player */
        objFieldEntry *e_x_prev = e->x_prev;

        /* move the player if it is not blocked */
        if (e_x_prev &&
            e_x_prev->data->done != 1 &&
            e_x_prev->data->type->getType() != baseDataObjectType::stone &&
            e_x_prev->data->type->getType() != baseDataObjectType::wall)
        {
            /* move player by switching the object field entry data */
            dataObject  *do_src     = e->data;
            dataObject  *do_dest    = e_x_prev->data;
            /* eat sand */
            if (do_dest->type->getType() == baseDataObjectType::sand) {
                delete do_dest;
                do_dest = new dataObject(baseDataObjectType::empty);
            }
            do_dest->done = 1;          // set other object done
            /* switch */
            e->data           = do_dest;
            e_x_prev->data    = do_src;
            
            /* update the address of the object field entry that contains
             * the player data */
            pl_entry_new = e_x_prev;
        }
    }

    return pl_entry_new; 

};





