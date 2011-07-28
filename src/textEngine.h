/*!
 * \file    textEngine.h
 * \class   textEngine 
 * \brief   Displays the field objects as text on the console
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 */

#ifndef _TEXTENGINE_H_
#define _TEXTENGINE_H_

#include "objField.h"

#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;


class textEngine
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

    // FIXME: 2 draw functions: draw, redraw
    void draw(const objField &field,
              const drawType_t drawtype = redraw,
              const char *str = NULL)
    {
        // set the cursor to its start position if required
        if (drawtype == redraw) {
            moveCursorLinesUp(getHeaderHigh() + getFieldHigh(field) + getFooterHigh());
        }
      
        // draw the object field
        drawHeader(str);
        drawField(field);
        drawFooter();
    }

    /*!
     * \param   y   Number of lines to move up.
     */
    static void moveCursorLinesUp(int y) {
        /* set cursor position
         * help: http://www.linuxselfhelp.com/howtos/Bash-Prompt/Bash-Prompt-HOWTO-6.html
         *       (Cursor Movement)
         */
        printf("\033[%dA", y);
    }

    /*!
     * \brief   Print the content of the object field to the console
     * \param   field       Reference to the object field to print
     */
    void drawField(const objField &field)
    {
        for (int y = 0; y < field.size_y; y++)
        {
            for (int x = 0; x < field.size_x; x++)
            {
                printf("%c ", field.objs[y*field.size_x + x].m->symbol);
            }
            printf("\n");
        }
    }
    /*!
     * \brief   Get the high in lines of the field's text output
     * \param   field       Reference to the object field to print
     */
    int getFieldHigh(const objField &field) {
        return field.size_y;
    }


    /*!
     * \brief   Print the header
     */
    void drawHeader(const char *str = NULL) {
        printf("==== Header (%s) ====\n", (str != NULL) ? str : "-");
    }
    /*!
     * \brief   Get the high in lines of the header's text output
     */
    int getHeaderHigh() {
        return 1;
    }

    /*!
     * \brief   Print the footer
     */
    void drawFooter() {
        printf("==== Footer ====\n");
    }
    /*!
     * \brief   Get the high in lines of the footer's text output
     */
    int getFooterHigh() {
        return 1;
    }


};

#endif
