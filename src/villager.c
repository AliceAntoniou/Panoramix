/*
** EPITECH PROJECT, 2022
** panoramix
** File description:
** villager
*/

#include <stdio.h>
#include <unistd.h>
#include "panoramix.h"

static bool is_pano_sleeping(void)
{
    bool rt = false;

    pthread_mutex_lock(mutex_druid_is_sleeping());
    if (*druid_is_sleeping()) {
        rt = true;
    }
    pthread_mutex_unlock(mutex_druid_is_sleeping());
    return rt;
}

static bool drink_potion(int num)
{
    bool rt = false;

    pthread_mutex_lock(mutex_pot());
    if (*pot() >= 0) {
        printf("Villager %d: I need a drink... I see %d servings left.\n", num,
            (*pot())--);
        if (*pot() == -1 && !is_pano_sleeping()) {
            printf(
                "Villager %d: Hey Pano wake up! We need more potion.\n", num);
            pthread_mutex_unlock(mutex_pot());
            sem_wait(pot_filled());
            return true;
        }
    }
    if (*pot() >= 0) {
        rt = true;
    }
    pthread_mutex_unlock(mutex_pot());
    return rt;
}

void *villagerf(void *param)
{
    villager_t *attributs = param;

    while (attributs->nb_fight) {
        if (drink_potion(attributs->num)) {
            printf("Villager %d: Take that roman scum! Only %d left.\n",
                attributs->num, --attributs->nb_fight);
        } else if (is_pano_sleeping()) {
            break;
        }
    }
    printf("Villager %d: I'm going to sleep now.\n", attributs->num);
    return NULL;
}
