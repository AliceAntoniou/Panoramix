/*
** EPITECH PROJECT, 2022
** panoramix
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "panoramix.h"

void print_usage(void)
{
    fprintf(stderr,
        "USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights> "
        "<nb_refills>\n");
}

void init_villagers(villager_t *villagers, pthread_t *villagers_th,
    const attributs_t attributs)
{
    for (int i = attributs.nb_villager - 1; i >= 0; i--) {
        villagers[i].nb_fight = attributs.nb_fight;
        villagers[i].num = i;
        printf("Villager %d: Going into battle!\n", i);
        pthread_create(&villagers_th[i], NULL, villagerf, &villagers[i]);
    }
}

void init_mutex(void)
{
    pthread_mutex_init(mutex_druid_is_sleeping(), NULL);
    pthread_mutex_init(mutex_pot(), NULL);
    sem_init(pot_filled(), 0, 0);
}

int panoramix(const attributs_t attributs)
{
    pthread_t *villagers_th = calloc(attributs.nb_villager, sizeof(pthread_t));
    villager_t *villagers = calloc(attributs.nb_villager, sizeof(villager_t));
    pthread_t druid_th;
    druid_t druid = {attributs.pot_size, attributs.nb_refills};

    if (!villagers_th || !villagers)
        return 84;
    init_mutex();
    *pot() = attributs.pot_size;
    printf("Druid: I'm ready... but sleepy...\n");
    pthread_create(&druid_th, NULL, druidf, &druid);
    init_villagers(villagers, villagers_th, attributs);
    for (int i = 0; i < attributs.nb_villager; ++i) {
        pthread_join(villagers_th[i], NULL);
    }
    pthread_cancel(druid_th);
    sem_destroy(pot_filled());
    free(villagers_th);
    free(villagers);
}

int main(int argc, char const *argv[])
{
    attributs_t attributs;

    if (argc != 5) {
        print_usage();
        return EPITECH_ERROR;
    }
    attributs = parser(argv + 1);
    if (attributs.nb_fight <= 0 || attributs.nb_refills <= 0 ||
        attributs.nb_villager <= 0 || attributs.pot_size <= 0) {
        print_usage();
        fprintf(stderr, "Values must be >0.\n");
        return EPITECH_ERROR;
    }
    return panoramix(attributs);
}
