#include <pthread.h>

/*
** cause: global, malloc, static valibale is shared
** but stack is not shared
*/

/*
** if use default attr, set attr value to 0
** if function success, return value is 0
** if function success, save thread fd in pthread *thread
** use: pthread_create(&thread, NULL, func_name, (void *)arg)
*/
int pthread_create(pthread_t *thread, const phtread *attr, void (*start_routine)(void *), (void *)arg);


/*
** wait other thread, and get return value of other thread
** if functions success, return value is 0
** 'th' is thread descripter
*/
int pthread_join(pthread_t th, void **thread_return);

/*
** if you want to know thread return value, use pthread join
** but you don't want to now thread return value, use pthread_detatch
**
*/
int pthread_detach(pthread_t th);
