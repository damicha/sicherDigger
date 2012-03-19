/*! ****************************************************************************
 *
 * \file    SDig_TextEngine.cpp
 * \brief   Displays the field objects as text on the console
 * 
 * \author  damicha of defect
 * \date    2011 
 *
 * \details
 *  The TextEngine class is implemented that provices functions to get the
 *  user input and to do a ASCII text output of the game field.
 *
 * \license See license file in the main directory. 
 *
 ******************************************************************************/

#include "SDig_TextEngine.h"
#include "ObjField/Field.h"

using namespace SDig;

/* set default value for the instance counter */
int TextEngine::mInstanceCounter = 0;

/*!
 * \brief   Print the content of the object field as an array to the console
 * \param   pField
 *  Reference to the object field to print
 */
void TextEngine::drawFieldData(const ObjField::Field *pField)
{
    for (int y = 0; y < pField->size_y; y++)
    {
        for (int x = 0; x < pField->size_x; x++)
        {
            DataObject *dataObj = pField->mEntries[y*pField->size_x + x].getData();  
            char c = getSymbol(dataObj->getTypeObject());
            printw("%c ", c);
        }
        printw("\n");
    }
    refresh();
}

