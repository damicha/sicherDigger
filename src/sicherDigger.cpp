/******************************************************************************/
/*!
 * \file    sicherDigger.cpp
 * \brief   Main program of the project sicherDigger
 *
 * \author  damicha of defect
 * \date    2011-2012
 *
 * \license See license file in the main directory.
 *
 ******************************************************************************/

#include "sicherDigger.h"
#include "GameEngine.h"

#include <stdio.h>
#include <stdlib.h>

/*!
 * \brief   main
 */
int main(void)
{
    /* create and run game enine */
    SDig::GameEngine    game;
    game.run();

    return 0;
}

