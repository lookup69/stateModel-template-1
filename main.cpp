#include "timer.h"
#include "machine.h"
#include <iostream>
#include <string>

using namespace std;
using namespace lkup69;

class Foo
{
public:
        void show()
        {
                cout << __PRETTY_FUNCTION__ << endl;
        }
};

void foo()
{
                cout << __PRETTY_FUNCTION__ << endl;
}

string timer_state_to_string(TimerState_e state)
{
        if(state == TimerState_e::PAUSE)
                return string("PAUSE");
        if(state == TimerState_e::RUNNING)
                return string("RUNNING");

        return string("STOP");                
}

void timer_test()
{
        Timer<Foo> t;
        Foo        f;
        int        i;

        cout << "Timer testing start\n";
        t.regCallback(&f, &Foo::show);
        t.regCallback(foo);

        cout << "1. start" << endl;
        t.setTime(10);

        cout << "1. start\n";
        t.start();
        i = 11;
        while(i--) {
                cout << "Timer State:" << timer_state_to_string(t.state()) << endl;
                cout << "timer remain t:" << t.getTime() << endl;
                sleep(1);
        }


        cout << "2. start ---> pause ---> resume" << endl;
        t.setTime(10);

        cout << "2. start\n";
        t.start();
        i = 3;
        while(i--) {
                cout << "Timer State:" << timer_state_to_string(t.state()) << endl;
                cout << "timer remain t:" << t.getTime() << endl;
                sleep(1);
        }

        cout << "2. pause\n";
        t.pause();
        i = 3;
        while(i--) {
                cout << "Timer State:" << timer_state_to_string(t.state()) << endl;
                cout << "timer remain t:" << t.getTime() << endl;
                sleep(1);
        }

        cout << "2. resume\n";
        t.start();

        i = 10;
        while(i--) {
                cout << "Timer State:" << timer_state_to_string(t.state()) << endl;
                cout << "timer remain t:" << t.getTime() << endl;
                sleep(1);
        }

        cout << "3. start ---> stop" << endl;
        t.setTime(10);

        cout << "3. start\n";
        t.start();
        i = 3;
        while(i--) {
                cout << "Timer State:" << timer_state_to_string(t.state()) << endl;
                cout << "timer remain t:" << t.getTime() << endl;
                sleep(1);
        }

        cout << "3. stop\n";
        t.stop();
        i = 3;
        while(i--) {
                cout << "Timer State:" << timer_state_to_string(t.state()) << endl;
                cout << "timer remain t:" << t.getTime() << endl;
                sleep(1);
        }

        cout << "4. start ---> pause ---> stop" << endl;
        t.setTime(10);
        cout << "4. start\n";
        t.start();
        i = 3;
        while(i--) {
                cout << "Timer State:" << timer_state_to_string(t.state()) << endl;
                cout << "timer remain t:" << t.getTime() << endl;
                sleep(1);
        }
        cout << "4. pause\n";
        t.pause();
        i = 3;
        while(i--) {
                cout << "Timer State:" << timer_state_to_string(t.state()) << endl;
                cout << "timer remain t:" << t.getTime() << endl;
                sleep(1);
        }

        cout << "4. stop\n";
        t.stop();
        i = 3;
        while(i--) {
                cout << "Timer State:" << timer_state_to_string(t.state()) << endl;
                cout << "timer remain t:" << t.getTime() << endl;
                sleep(1);
        }

        cout << "timer test finish\n";
}

string machine_status_to_string(MachineState_e status)
{
        if(status == MachineState_e::POSTPONE)
                return string("POSTPONE");
        if(status == MachineState_e::STOP)
                return string("STOP");
        
        return string("RUNNING");
}

void machine_test()
{
        Machine m;
        int i;

        cout << "z.1......................\n";

        cout << "start" << endl;
        m.start(); 
        i = 3;
        while(i--) {
                cout << "status:" << machine_status_to_string(m.getState()) << endl;
                sleep(1);
        };

        cout << "stop" << endl;
        m.stop();
        i = 3;
        while(i--) {
                cout << "status:" << machine_status_to_string(m.getState()) << endl;
                sleep(1);
        };

        cout << "start" << endl;
        m.start(); 
        i = 3;
        while(i--) {
                cout << "status:" << machine_status_to_string(m.getState()) << endl;
                sleep(1);
        };

        cout << "postpone" << endl;
        m.postpone(3);
        i = 10;
        while(i--) {
                cout << "postpone t:" << m.getRemainTiem() << endl;
                cout << "status:" << machine_status_to_string(m.getState()) << endl;
                sleep(1);
        };

        cout << "stop" << endl;
        m.stop();
        i = 3;
        while(i--) {
                cout << "status:" << machine_status_to_string(m.getState()) << endl;
                sleep(1);
        };
}

int main()
{
        timer_test();
        //machine_test();

        return 0;
}