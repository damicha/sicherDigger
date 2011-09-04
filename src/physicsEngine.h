/******************************************************************************/
/*!
 * \file    physicsEngine.h
 * \brief   Class definition.
 *
 * \author  damicha of defect
 * \date    2011
 *
 ******************************************************************************/


#ifndef _PHYSICS_ENGINE_H_
#define _PHYSICS_ENGINE_H_

#include "baseDataObjectType.h"
#include "dataObjectTypes.h"
#include "objField.h"

#include "stdio.h"

using namespace std;


/*!
 * \class   physicsEngine
 */
class physicsEngine
{
/* ======== class types ======== */    
public:
    /*!
     * \enum Object movement type. Used for player movement
     */
    typedef enum {
        mtLeft,
        mtRight,
        mtUp,
        mtDown
    } movement_t;

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
     * \brief   Reset the number of iterations.
     */
    void resetIterNum(void) {
        iter_num = 0;
    }

    /*!
     * \brief   Get the number of iterations since last reset.
     * \return  Number of done iterations.
     */
    int getIterNum(void) {
        return iter_num;
    }

    /*!
     * \brief   Do one iteration on the object field.
     */
    void run(objField &field, movement_t m_pl);

    /*!
     * \brief   Stone physics
     */
    void stonePhysics(objFieldEntry *e);
    
    /*!
     * \brief   Player physics
     */
    objFieldEntry *playerPhysics(objFieldEntry *e, movement_t m);


};

#endif // _PHYSICSENGINE_H_
