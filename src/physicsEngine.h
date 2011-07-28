/*! ****************************************************************************
 * \file    phyicsEngine.h
 * \brief   Implements the physics of the world.
 *
 * \author  damicha of defect
 * \date    2011
 *
 ******************************************************************************/


#ifndef _PHYSICSENGINE_H_
#define _PHYSICSENGINE_H_

#include "baseMaterial.h"
#include "materials.h"
#include "objField.h"

#include "stdio.h"

using namespace std;


/*!
 * \class   physicsEngine
 */
class physicsEngine
{
/* ======== class attributes ======== */    
private:
    int iter_num;    /*!< The number of proceeded iterations. */

/* ======== functions ======== */    

public:
    /*!
     * \brief   Constructor
     */
    physicsEngine() {
        resetIterNum();
    }

    /*!
     * \brief   Reset the number of iterrations.
     */
    void resetIterNum(void) {
        iter_num = 0;
    }


    /*!
     * \brief   Do one iterration on the object field.
     */
    void run(objField &field)
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

                /* a stone falls down if the field under it is free */
                if (obj->m->getType() == baseMaterialConfig::stone &&
                    field.objs[y*field.size_x + x].m->done != 1) {
                    objFieldEntry *obj_y_next = obj->y_next;

                    if (obj_y_next != NULL &&
                        obj_y_next->m->getType() == baseMaterialConfig::empty)
                    {
                        // change object types
                        // FIXME: done change object types: move objects!
                        baseMaterial *m1 = obj->m;
                        baseMaterial *m2 = obj_y_next->m;
                        obj->m          = m2;
                        obj_y_next->m   = m1;
                    }
                    obj_y_next->m->done = 1;
                }
                obj->m->done = 1;

            }    
        }
    }


    /*!
     * \brief   Get the number of iterrations since last reset.
     */
    int getIterNum(void) {
        return iter_num;
    }


};

#endif // _PHYSICSENGINE_H_
