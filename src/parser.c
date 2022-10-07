/*
** EPITECH PROJECT, 2022
** panoramix
** File description:
** parser
*/

#include <stdio.h>
#include <stdlib.h>
#include "panoramix.h"

attributs_t parser(const char *av[])
{
    attributs_t attributs;

    attributs.nb_villager = atoi(av[0]);
    attributs.pot_size = atoi(av[1]);
    attributs.nb_fight = atoi(av[2]);
    attributs.nb_refills = atoi(av[3]);
    return attributs;
}
