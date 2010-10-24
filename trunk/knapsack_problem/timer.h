#ifndef _TIMER_H
#define _TIMER_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BEGIN_MAIN \
struct timespec main_s, main_f ; \
clock_gettime ( CLOCK_REALTIME, &main_s ) ; \
struct timespec m_time_s, m_time_f ; \
double exp_time ;

#define END_MAIN \
clock_gettime ( CLOCK_REALTIME, &main_f ) ; \
exp_time = (double)(main_f.tv_sec - main_s.tv_sec) \
           + (double)(main_f.tv_nsec - main_s.tv_nsec) / 1e9 ; \
printf ( "total ----> %f (ms)\n", 1e3 * exp_time ) ;

#define BEGIN_EXPERIMENT \
clock_gettime(CLOCK_REALTIME, &m_time_s ) ;

#define END_EXPERIMENT \
clock_gettime(CLOCK_REALTIME, &m_time_f ) ; \
exp_time = (double)(m_time_f.tv_sec - m_time_s.tv_sec) \
           + (double)(m_time_f.tv_nsec - m_time_s.tv_nsec) / 1e9 ; \
printf ( "----------> %f (ms)\n", 1e3 * exp_time ) ;

#endif

