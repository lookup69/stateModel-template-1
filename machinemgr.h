/*
 * @brief
 *
 * @author  Archer Chang
 * @file
 * @date
 *
 */

#ifndef _LOOKUP69_MACHINE_MGR_H_
#define _LOOKUP69_MACHINE__MGRH_

#include <memory>
#include <vector>

#include "machine.h"

namespace lkup69
{
        class MachineMgr
        {
        public:
                MachineMgr();
                ~MachineMgr();

                void add(Machine *m)
                {
                        if(m == nullptr)
                                return;

                        m_machineVec.push_back(std::make_shared<Machine>(*m));
                }

                size_t numOfMachine(void)
                {
                        return m_machineVec.size();
                }

                std::shared_ptr<Machine> getMachine(size_t index)
                {
                        if(index < m_machineVec.size())
                                return m_machineVec[index];

                        return nullptr;
                }

                
        private:
                // Hidden
                MachineMgr(const MachineMgr &);
                MachineMgr &operator=(const MachineMgr &);
        private:
                std::vector<std::shared_ptr<Machine>> m_machineVec;

        };
}
#endif