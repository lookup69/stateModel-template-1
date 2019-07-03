/*
 * @brief
 *
 * @author  Archer Chang
 * @file
 * @date
 *
 */

#ifndef _LOOKUP69_MACHINE_H_
#define _LOOKUP69_MACHINE_H_
#include "timer.h"

namespace lkup69
{
        enum class MachineState_e
        {
                RUNNING,
                STOP,
                POSTPONE,
        };

        class Machine : public Thread
        {
        public:
                Machine();
                ~Machine();

                void start(void);
                void stop(void);
                void postpone(int sec);

                MachineState_e getState(void)
                {
                        if(m_bPostpone)
                                return MachineState_e::POSTPONE;
                        if(m_bStop)
                                return MachineState_e::STOP;

                        return MachineState_e::RUNNING;
                }
                
                int getRemainTiem(void)
                {
                        return m_timer.getTime();
                }

        private:
                // Hidden
                Machine(const Machine &);
                Machine &operator=(const Machine &);

        private:
                bool             m_bExit = false;
                bool             m_bStop = false;
                bool             m_bStuckOnWaitLock = false;
                bool             m_bPostpone = false;
                pthread_mutex_t  m_waitLock;
                pthread_cond_t   m_waitCond;
                Timer<Machine>   m_timer; 

                // boddy
                void *process(void) override;
        };
}
#endif
