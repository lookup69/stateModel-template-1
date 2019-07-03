#include "machine.h"
#include <unistd.h>
#include <iostream>

using namespace lkup69;

Machine::Machine()
{
        m_timer.regCallback(this, &Machine::start);
        mutexInit(m_waitLock);
        condInit(m_waitCond);
        run();
        
        // waitting into condWait stage
        while(!m_bStuckOnWaitLock)
                usleep(100);
}

Machine::~Machine()
{
        m_bExit = true;
        m_bStop = true;
        m_timer.stop();
        condSignal(m_waitCond);

        // waiting for process event-loop end
        while (m_bExit) 
                usleep(100);

        mutexDestroy(m_waitLock);
        condDestroy(m_waitCond);
}

void Machine::start()
{
        if(m_bStuckOnWaitLock) 
                condSignal(m_waitCond);
        m_bStop = false;
}

void Machine::stop()
{
        m_bStop = true;

        if(m_bPostpone) {
                m_timer.stop();
                m_bPostpone = false;
        }
}

void Machine::postpone(int sec)
{
        m_timer.setTime(sec);
        m_bStop = true;
        m_bPostpone = true;
        m_timer.start();
}

void *Machine::process(void)
{
        while(!m_bExit) {
                lock(m_waitLock);
                m_bStuckOnWaitLock = true;
                condWait(m_waitCond, m_waitLock); 
                unlock(m_waitLock); 
                m_bStuckOnWaitLock = false;

                m_bPostpone = false;
                
                while(!m_bStop) {
                        std::cout << "in process\n";
                        sleep(1);
                }
        }
        m_bExit = false;

        return nullptr;
}

