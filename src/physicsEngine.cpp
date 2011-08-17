/*!
 * \file    physicsEngine.cpp
 * \brief   Implements the physics of the world.
 *
 * \author  damicha of defect
 * \date    2011
 *
 */

#include "physicsEngine.h"

#include "baseMaterial.h"
#include "materials.h"
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
            field.objs[y*field.size_x + x].m->done = 0;

        }
    }

    iter_num++;

    for (int y = 0; y < field.size_y; y++)
    {
        for (int x = 0; x < field.size_x; x++)
        {
            objFieldEntry *obj = &(field.objs[y*field.size_x + x]);

            /* call physics functions as a function of the object type */
            switch (obj->m->getType())
            {
                case baseMaterialConfig::stone:
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
    //if (field.objs[y*field.size_x + x].m->done != 1) {
    if (obj->m->done != 1) {
        objFieldEntry *obj_y_next = obj->y_next;

        if (obj_y_next && obj_y_next->m->getType() == baseMaterialConfig::empty)
        {
            // change object types
            // FIXME: don't switch object types: move/switch objects!
            baseMaterial *m1 = obj->m;
            baseMaterial *m2 = obj_y_next->m;
            obj->m          = m2;
            obj_y_next->m   = m1;
        }
        obj_y_next->m->done = 1;
    }
    obj->m->done = 1;

};





