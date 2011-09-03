/*!
 * \file    physicsEngine.cpp
 * \brief   Implements the physics of the world.
 *
 * \author  damicha of defect
 * \date    2011
 *
 */

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
 * FIXME: create a subfunction for each material
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
            field.objs[y*field.size_x + x].data->done = 0;

        }
    }

    iter_num++;

    /* move player */
    // FIXME: obj switches from player object to another object !
    // FIXME: update plInfi.obj
    objFieldEntry *obj_new;
    obj_new = playerPhysics(field, field.plInfo.obj, mx, 0);
    field.plInfo.obj = obj_new; 

    /* run physics on the other field objects */
    for (int y = 0; y < field.size_y; y++)
    {
        for (int x = 0; x < field.size_x; x++)
        {
            objFieldEntry *obj = &(field.objs[y*field.size_x + x]);

            /* call physics functions as a function of the object type */
            switch (obj->data->type->getType())
            {
                case baseDataObjectType::stone:
                    stonePhysics(field, obj);
                    break;
                case baseDataObjectType::player:
                    // do nothing, because the player should already be moved
            //       playerPhysics(field, obj, mx, 0);
                    break;
                default:
                    break;
            }
        }    
    }

};


/*!
 * \brief   Stone physics
 * \param   field   object field
 * \param   obj     selected object
 */
void physicsEngine::stonePhysics(objField &field, objFieldEntry *obj)
{
    /* a stone falls down if the field under it is free */
    //if (field.objs[y*field.size_x + x].data->done != 1) {
    if (obj->data->done != 1) {
        objFieldEntry *obj_y_next = obj->y_next;

        if (obj_y_next && obj_y_next->data->type->getType() == baseDataObjectType::empty)
        {
            // change object types
            // FIXME: don't switch object types: move/switch objects!
            dataObject  *do1 = obj->data;
            dataObject  *do2 = obj_y_next->data;
            obj->data           = do2;
            obj_y_next->data    = do1;
            obj_y_next->data->done = 1;
        }
    }
    obj->data->done = 1;

};


/*!
 * \brief   Player physics
 * \param   field   object field
 * \param   obj     selected object
 * \return  address of the new object field entry that carries the player
 * FIXME add player commands: move left, right, up, down, push..., pull ...
 * FIXME eat sand
 */
objFieldEntry *
physicsEngine::playerPhysics(objField &field, objFieldEntry *obj,
                             int x, int y)
{
    objFieldEntry *obj_new = obj;   // new player object field entry

//    printf("                            switch 0\n");
    /* a player can move if no item blocks its way */
    if (obj->data->done != 1) {

//        printf("                            switch 1\n");
        if      (x ==  1)
        {
//            printf("                            switch 2a\n");
            objFieldEntry *obj_x_next = obj->x_next;
            if (obj_x_next &&
                obj_x_next->data->type->getType() != baseDataObjectType::stone &&
                obj_x_next->data->type->getType() != baseDataObjectType::wall)
            {
                // FIXME: don't switch object types: move objects!
                dataObject  *do1 = obj->data;
                dataObject  *do2 = obj_x_next->data;
                obj->data           = do2;
                obj_x_next->data    = do1;
                obj_x_next->data->done = 1;

                obj_new = obj_x_next;
            }
            obj->data->done = 1;
        }
        else if (x == -1)
        {
//            printf("                            switch 2b\n");
            objFieldEntry *obj_x_prev = obj->x_prev;
            if (obj_x_prev &&
                obj_x_prev->data->type->getType() != baseDataObjectType::stone &&
                obj_x_prev->data->type->getType() != baseDataObjectType::wall)
            {
                // FIXME: don't switch object types: move objects!
                dataObject  *do1 = obj->data;
                dataObject  *do2 = obj_x_prev->data;
                /* eat sand - FIXME: always eat */
                if (do2->type->getType() == baseDataObjectType::sand) {
                    delete do2;
                    do2 = new dataObject(baseDataObjectType::empty);
                }
                obj->data           = do2;
                obj_x_prev->data    = do1;
                obj_x_prev->data->done = 1;
//                printf("                            switch 3\n");
                
                obj_new = obj_x_prev;
            }
            obj->data->done = 1;
        }

    }

    return obj_new; 

};





