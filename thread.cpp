/*
 * @brief
 *
 * @author  Archer Chang
 * @file
 * @date
 *
 */

#include "thread.h"
using namespace lkup69;

int Thread::mutexInit(pthread_mutex_t &mtx, mutextAttr_e mutexAttr)
{
        pthread_mutexattr_t mtxAttr;
        int                 ret;

        if((ret = pthread_mutexattr_init(&mtxAttr)) < 0)
                return ret;

        if (mutexAttr == mutextAttr_e::THREAD_MUTEX_ERROR_CHECK_E)
                ret = pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_ERRORCHECK);
        else if (mutexAttr == mutextAttr_e::THREAD_MUTEX_RECURSIVE_E) 
                ret = pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_RECURSIVE);
        else 
                ret = pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_NORMAL);
        

        if(ret == 0) {
                pthread_mutex_init(&mtx, &mtxAttr);
                pthread_mutexattr_destroy(&mtxAttr);
        }

        return ret;
}

