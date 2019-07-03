/*
 * @brief
 *
 * @author  Archer Chang
 * @file
 * @date
 *
 */

#ifndef _LOOKUP69_TIMER_H_
#define _LOOKUP69_TIMER_H_
#include "thread.h"
#include <unistd.h>
#include <vector>

namespace lkup69
{
        enum class TimerState_e
        {
                RUNNING,
                STOP,
                PAUSE
        };

        template<typename callbackClass>
        class Timer : public Thread
        {
                typedef struct 
                {
                        callbackClass *pClass;
                        void (callbackClass::*pMemfunc)();
                } callbackmfc;
        public:

                Timer()
                {
                        mutexInit(m_waitLock);
                        condInit(m_waitCond);
                        run();
                        while(!m_bStuckOnWaitLock)
                                usleep(100);
                }

                ~Timer() override
                {
                        m_bExit = true;
                        m_bStart = false;
                        condSignal(m_waitCond);
                        while (m_bExit) 
                                usleep(100);

                        mutexDestroy(m_waitLock);
                        condDestroy(m_waitCond);
                }

                void setTime(int sec)
                {
                        m_sec = sec;
                }
                
                int getTime(void)
                {
                        return m_sec;
                }
                
                void start()
                {
                        if(m_bPause)
                                m_bPause = false;

                        if((!m_bStart) && (m_sec > 0)) {
                                condSignal(m_waitCond);
                                m_bLaunchCallback = true;
                        }
                }

                void stop()
                {
                        if(m_bStart) 
                                m_bStart = false;
                        m_bLaunchCallback = false;                                
                }

                void pause()
                {
                        if(m_bStart)
                                m_bPause = true;

                }

                TimerState_e state()
                {
                        if(m_bPause)
                                return TimerState_e::PAUSE;
                        if(m_bStart)
                                return TimerState_e::RUNNING;

                        return TimerState_e::STOP;
                }

                void regCallback(callbackClass *pclass, void (callbackClass::*pmemfunc)())
                {
                        callbackmfc cb;

                        if((pclass != nullptr) && (pmemfunc != nullptr)) {
                                cb.pClass = pclass;
                                cb.pMemfunc = pmemfunc;
                                m_cbMfcVec.push_back(cb);
                        }
                }

                void regCallback(void (*func)())
                {
                        if(func != nullptr)
                                m_cbFuncVec.push_back(func);
                }
        private:
                // Hidden
                Timer(const Timer &);
                Timer operator=(const Timer &);

        private:
                int                      m_sec = 0;
                bool                     m_bExit = false;
                bool                     m_bStart = false;
                bool                     m_bPause = false;
                bool                     m_bStuckOnWaitLock = false;
                bool                     m_bLaunchCallback = false;
                pthread_mutex_t          m_waitLock;
                pthread_cond_t           m_waitCond; 
                std::vector<callbackmfc> m_cbMfcVec;  // callback for member function
                std::vector<void (*)()>  m_cbFuncVec; // callback for normal function

                void *process(void) override
                {
                        while(!m_bExit) {
                                lock(m_waitLock);
                                m_bStuckOnWaitLock = true;
                                condWait(m_waitCond, m_waitLock);
                                unlock(m_waitLock); 
                                m_bStuckOnWaitLock = false;
                                m_bStart = true;
                                while(m_bStart) {
                                        sleep(1);
                                        if(m_bPause) {
                                                continue;
                                        }
                                        --m_sec;
                                        if(m_sec <= 0)
                                                break;
                                }

                                if(m_bLaunchCallback) {
                                        for(callbackmfc &cbMfc : m_cbMfcVec) 
                                                (cbMfc.pClass->*cbMfc.pMemfunc)();
                                        
                                        for(auto &cbfunc : m_cbFuncVec)
                                                cbfunc();
                                }
                                m_bStart = false;
                                m_bPause = false;
                                m_sec = 0;
                        }
                        m_bExit = false;

                        return nullptr;
                }
        };
};
#endif
