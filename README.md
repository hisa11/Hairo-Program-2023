#include "mbed.h"

PwmOut my_servo(D3);
AnalogIn ain(A5);
BufferedSerial pc(USBTX, USBRX, 2000000); // パソコンとのシリアル通信

int main()
{
    my_servo.period(0.020); // servo requires a 20ms period
    while (1)
    {
        if (pc.readable())
        {
            char buf;
            pc.read(&buf, sizeof(buf));

            if (buf == 'W' || buf == 'w') // 前進
            {

                ThisThread::sleep_for(30ms);
            }
        }
    }
}
