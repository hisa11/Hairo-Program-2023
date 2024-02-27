#include <mbed.h>
#include "FIRSTPENGUIN.hpp"
#include "SolenoidController.hpp"
#include "ServoController.hpp"

constexpr uint32_t can_id = 30;

BufferedSerial pc{PB_6, PA_10, 4800};
CAN can{PA_11, PA_12, (int)1e6};
CANMessage msg;
Timer timer;
FirstPenguin penguin{can_id, can};

int main()
{
    timer.start();
    SolenoidController solenoidController(can, pc);
    ServoController servoController(can, pc);

    char command[11]; // Command and number combination array
    int16_t pwm0[4] = {0, 0, 0, 0}; // Motor control array

    auto pre = timer.elapsed_time(); // Declaration of 'pre'

    while (1)
    {
        pc.set_blocking(false);
        int idx = 0;
        while (idx < sizeof(command) / sizeof(command[0])) // Fix comparison warning
        {
            int n = pc.read(&command[idx], sizeof(command) - idx);
            if (n <= 0)
            {
                ThisThread::sleep_for(10ms);
            }
            else
            {
                idx += n;
            }
        }
        command[idx] = '\0'; // Add string terminator
        printf("%s\n", command);

        char buf;
        pc.read(&buf,sizeof(buf));
        if(buf == 'D' ){
            penguin.pwm[0] = 7000;
            buf = ' ';
        }
        else if (buf == 'd')
        {
            penguin.pwm[0] = -7000;
            buf = ' ';
        }
        else if (buf == 'k')
        {
            penguin.pwm[1] = 7000;
            buf = ' ';
        }
        else if(buf == 'y'){
            penguin.pwm[1] = -7000;
            buf = ' ';
        }
        
        auto now = timer.elapsed_time();

        int number_r = 0, number_R = 0, number_L = 0;
        if (command[0] == 'r')
        {
            number_r = atoi(&command[1]);
        }
        else if (command[0] == 'R')
        {
            number_R = atoi(&command[1]);
        }
        else if (command[0] == 'L')
        {
            number_L = atoi(&command[1]);
        }
        
        pwm0[0] = static_cast<int16_t>((number_r + number_R) * 60 + number_L * 60);
        pwm0[1] = static_cast<int16_t>((number_r - number_R) * 60 - number_L * 60);
        pwm0[2] = static_cast<int16_t>((number_r - number_R) * 60 + number_L * 60);
        pwm0[3] = static_cast<int16_t>((number_r + number_R) * 60 - number_L * 60);

        if (command[0] == 'D')
        {
            penguin.pwm[0] = 6000;
        }
        else if (command[0] == 'd')
        {
            penguin.pwm[1] = -6000;
        }

        if (can.read(msg))
        {
            penguin.read(msg);
        }

        if (now - pre > 20ms)
        {
            for (auto e : penguin.receive)
                printf("% 5ld\t", e.enc);
            for (auto e : penguin.receive)
                printf("% 5ld\t", e.adc);
            printf("\n");

            for (auto &e : penguin.pwm)
                e = penguin.max / 4;

            servoController.run();
            solenoidController.run();

            pre = now;
            int res = penguin.send();
            if (!res)
            {
                // printf("fail\n");
            }
        }
        CANMessage msg0(2, (const uint8_t *)pwm0, 8);
        can.write(msg0);
    }
}
