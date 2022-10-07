/*
** EPITECH PROJECT, 2022
** panoramix
** File description:
** mutex
*/

#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>

int *pot(void)
{
    static int pot_;

    return &pot_;
}

pthread_mutex_t *mutex_pot(void)
{
    static pthread_mutex_t mutex_pot_;

    return &mutex_pot_;
}

bool *druid_is_sleeping(void)
{
    static bool druid_is_sleeping_;

    return &druid_is_sleeping_;
}

pthread_mutex_t *mutex_druid_is_sleeping(void)
{
    static pthread_mutex_t mutex_druid_is_sleeping_;

    return &mutex_druid_is_sleeping_;
}

sem_t *pot_filled(void)
{
    static sem_t fill_pot;

    return &fill_pot;
}
