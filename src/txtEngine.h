/*!
 * \file    txtEngine.h
 * \class   txtEngine 
 * \brief   Displays the field objects as text on the console
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 */

#ifndef _TXTENGINE_H_
#define _TXTENGINE_H_

#include "baseObjField.h"

#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;


/*!
 * \class txtEngine
 */
class txtEngine
{
public:
    /*!
     * \enum output type
     */
    typedef enum {
        firstdraw,  //!< Draw without placing the cursor
        redraw      //!< Set cursor to start position and draw
    } drawType_t;

/* ======== functions ======== */
public:
    /*!
     * \brief   Print the content of the object field to the console
     * \param   field       Reference to the object field to print
     * \param   drawtype    Set draw mode
     */
    void draw(const baseObjField &field, const drawType_t drawtype = redraw)
    {
        /* set cursor position
         * help: http://www.linuxselfhelp.com/howtos/Bash-Prompt/Bash-Prompt-HOWTO-6.html (Cursor Movement)
         */
        if (drawtype == redraw) {
            // Move the cursor N lines up: \033[<N>A
            printf("\033[%dA", field.size_y+2);
        }
#if 0
        printf("\033[%d;%dH", 3, 3);
        printf("x<--\n");
#endif
        // print header
        printf("==== Header ====\n");
       
        // draw field
        for (int y = 0; y < field.size_y; y++)
        {
            for (int x = 0; x < field.size_x; x++)
            {
                printf("%c ", field.objs[y*field.size_x + x].m->symbol);
            }
            printf("\n");
        }

        // print footer
        printf("==== Footer ====\n");
    }


};

#endif
