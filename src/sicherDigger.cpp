/******************************************************************************/
/*!
 * \file    sicherDigger.cpp
 * \brief   Main program of the project sicherDigger
 *
 * \author  damicha of defect
 * \date    2011
 *
 * \license See license file in the main directory.
 *
 ******************************************************************************/

#include "sicherDigger.h"
#include "SDig_GameEngine.h"

#include <stdio.h>
#include <stdlib.h>

using namespace std;

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

