/*
** EPITECH PROJECT, 2022
** panoramix
** File description:
** panoramix
*/

#ifndef PANORAMIX_H_
    #define PANORAMIX_H_

    #include <pthread.h>
    #include <stdbool.h>
    #include <semaphore.h>

    #define EPITECH_ERROR 84

    typedef struct attribut {
        int nb_villager;
        int pot_size;
        int nb_fight;
        int nb_refills;
    } attributs_t;

    typedef struct villager {
        int num;
        int nb_fight;
    } villager_t;

    typedef struct druid {
        int pot_size;
        int nb_refills;
    } druid_t;

    int *pot(void);
    pthread_mutex_t *mutex_pot(void);

    bool *druid_is_sleeping(void);
    pthread_mutex_t *mutex_druid_is_sleeping(void);

    sem_t *pot_filled(void);

    void *villagerf(void *param);
    void *druidf(void *param);
    attributs_t parser(const char *av[]);

#endif /* !PANORAMIX_H_ */
