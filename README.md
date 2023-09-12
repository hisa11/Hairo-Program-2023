#include "mbed.h"

BufferedSerial pc(USBTX, USBRX, 2000000); // パソコンとのシリアル通信
// pwm[0] = 0;         左前タイヤ
// pwm[1] = 0;         左後ろタイヤ
// pwm[2] = 0;         右前タイヤ
// pwm[3] = 0;         右後ろタイヤ
CAN can(PA_11, PA_12, (int)1e6);
int16_t pwm[4] = {0, 0, 0, 0}; // pwm制御
CANMessage msg;
AnalogIn bekon(A0);
AnalogIn choko(A1);
int mikan = 'a'; // ←a方向とb方向がある
DigitalIn button(USER_BUTTON);

int main()
{
    while (1)
    {
        if (pc.readable())
        {
            char buf;
            pc.read(&buf, sizeof(buf));

            if (buf == 'W' || buf == 'w') // 前進
            {
                pwm[0] = 8000;
                pwm[1] = 8000;
                pwm[2] = 8000;
                pwm[3] = 8000;
                ThisThread::sleep_for(30ms);
            }
            else if (buf == 'S' || buf == 's') // 後進
            {
                pwm[0] = -8000;
                pwm[1] = -8000;
                pwm[2] = -8000;
                pwm[3] = -8000;
                ThisThread::sleep_for(30ms);
            }
            else if (buf == 'A' || buf == 'a') // 左回転
            {
                pwm[0] = -2000;
                pwm[1] = -2000;
                pwm[2] = 2000;
                pwm[3] = 2000;
                ThisThread::sleep_for(30ms);
            }
            else if (buf == 'D' || buf == 'd') // 右回転
            {
                pwm[0] = 2000;
                pwm[1] = 2000;
                pwm[2] = -2000;
                pwm[3] = -2000;
                ThisThread::sleep_for(30ms);
            }
            else if (buf == 'Q' || buf == 'q') // 微弱前進
            {
                pwm[0] = 4000;
                pwm[1] = 4000;
                pwm[2] = 4000;
                pwm[3] = 4000;
                ThisThread::sleep_for(30ms);
            }
            else if (buf == 'E' || buf == 'e') // 微弱後進
            {
                pwm[0] = -4000;
                pwm[1] = -4000;
                pwm[2] = -4000;
                pwm[3] = -4000;
                ThisThread::sleep_for(30ms);
            }
            else if (buf == 'V' || buf == 'v') // Vだっしゅ！！
            {
                pwm[0] = 15000;
                pwm[1] = 15000;
                pwm[2] = 15000;
                pwm[3] = 15000;
                ThisThread::sleep_for(30ms);
            }

            else if (mikan == 'a')
            {
                if (bekon.read() >= 0.020f)
                {
                    mikan = 'b';
                }
            }
            else if (mikan == 'b')
            {
                if (choko.read() >= 0.020f)
                {
                    mikan = 'a';
                }
            }

            else if (button == 'N' || button == 'n')
            {
                if (mikan == 'a')
                {
                    // ここにモタドラコード
                }
                if (mikan == 'b')
                {
                    // ここにモタドラコード
                }
            }
            else if (button == 'Z' || button == 'z')            { //停止
                pwm[0] = 0;
                pwm[1] = 0;
                pwm[2] = 0;
                pwm[3] = 0;
            }

            // キーに対する処理が終わったらCAN通信を行う
            // msg.id = 3;
            // msg.len = 8;

            pc.write(&button, sizeof(button));
            // ThisThread::sleep_for(1000ms);
        }
        memcpy(msg.data, pwm, sizeof(pwm));
        can.write(msg);
    }
}

