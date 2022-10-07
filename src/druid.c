/*
** EPITECH PROJECT, 2022
** panoramix
** File description:
** druid
*/

#include <stdio.h>
#include "panoramix.h"

bool check_refills(int nb_refills)
{
    if (!nb_refills) {
        pthread_mutex_lock(mutex_druid_is_sleeping());
        printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
        *druid_is_sleeping() = true;
        pthread_mutex_unlock(mutex_druid_is_sleeping());
        return true;
    }
    return false;
}

void *druidf(void *param)
{
    bool sleep = false;
    druid_t *attributs = param;

    while (!sleep) {
        pthread_mutex_lock(mutex_pot());
        if (*pot() < 0) {
            printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I "
                    "can only make %d more refills after this one.\n",
                --attributs->nb_refills);
            *pot() = attributs->pot_size - 1;
            sem_post(pot_filled());
        }
        sleep = check_refills(attributs->nb_refills);
        pthread_mutex_unlock(mutex_pot());
    }
    return NULL;
}
