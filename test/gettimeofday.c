#include <sys/time.h>

/*
** set null to tz
*/
int gettimeofday(struct timeval *tv, struct timezone *tz);

/*
** tv structure(total == sec + usec)
*/
struct timeval
{
    long tv_sec;       // 초
    long tv_usec;      // 마이크로초
}
