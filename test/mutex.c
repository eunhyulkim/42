/*
** mutex is snycronize mechanism in pthread
** security section(at time, one thread) is critical section
** gcc -o mutex_lock mutex_lock.c -lpthread
*/

/*
** initialize mutex strucutre varaible
*/
pthread_mutex_t a_mutex;
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutex_attr *attr);

/*
** if mutex is locked already, user is wait to mutex is unlocked for relock
*/
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destory(pthread_mutex_t *mutex);
