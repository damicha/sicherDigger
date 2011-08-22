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
 */
void physicsEngine::run(objField &field)
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
            baseDataObjectType *t1 = obj->data->type;
            baseDataObjectType *t2 = obj_y_next->data->type;
            obj->data->type         = t2;
            obj_y_next->data->type  = t1;
        }
        obj_y_next->data->done = 1;
    }
    obj->data->done = 1;

};





