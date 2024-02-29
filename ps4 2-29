#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WiFiUdp.h>
#include <PS4Controller.h>
#include <HardwareSerial.h>

const char *ssid = "GL-SFT1200-19f";
const char *password = "goodlife";

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  PS4.begin("70:b8:f6:5c:80:16");
  WiFi.begin(ssid, password);
#if 0
  while (WiFi.status() != WL_CONNECTED) {
     delay(1000);
     Serial.println("つないでるぜ");
  }
#endif
  Serial.println("つながったぜ");
}

extern void print_and_udp(char *buf, char flag, int val);
/////////////////////////////////
int tien = 20;

int souryou = 60;
// int souryou2 = 20;
/////////////////////////////////
void loop() {
  if (PS4.isConnected()) {
    /////if (PS4.ボタンのなまえ()) print_and_udp(送る文字,引数があるか*あったら1*、引数、送る量）
    if (PS4.Right()) print_and_udp("DDDDDDDDDD", 0, 0, souryou);
    if (PS4.Left()) print_and_udp("AAAAAAAAAA", 0, 0, souryou);
    if (PS4.Up()) print_and_udp("WWWWWWWWWW", 0, 0, souryou);
    if (PS4.Down()) print_and_udp("SSSSSSSSSS", 0, 0, souryou);
    if (PS4.Circle()) print_and_udp("dddddddddd", 0, 0, souryou);
    if (PS4.Square()) print_and_udp("aaaaaaaaaa", 0, 0, souryou);
    if (PS4.Triangle()) print_and_udp("wwwwwwwwww", 0, 0, souryou);
    if (PS4.Cross()) print_and_udp("ssssssssss", 0, 0, souryou);
    if (PS4.L1()) print_and_udp("yyyyyyyyyy", 0, 0, souryou);
    if (PS4.R1()) print_and_udp("iiiiiiiiii", 0, 0, souryou);
    if (PS4.L3()) print_and_udp("rrrrrrrrrr", 0, 0, souryou);
    if (PS4.R3()) print_and_udp("llllllllll", 0, 0, souryou);

    if (PS4.R2()) {
      int R2 = PS4.R2Value();
      if (R2 > 90) print_and_udp("9999999999", 0, 0, souryou);
    }
    if (PS4.L2()) {
      int L2 = PS4.L2Value();
      if (L2 > 90) print_and_udp("7777777777", 0, 0, souryou);
    }

    int gosa = 12;


    int Rx = PS4.RStickX();
    if (Rx < -80 && Rx > -130) {
      print_and_udp("1111111111", 0, 0, souryou);
    } else if (Rx < -40 && Rx > -80) {
      print_and_udp("2222222222", 0, 0, souryou);
    } else if (Rx < -12 && Rx > -40) {
      print_and_udp("3333333333", 0, 0, souryou);
    } else if (Rx < 40 && Rx > 12) {
      print_and_udp("4444444444", 0, 0, souryou);
    } else if (Rx < 80 && Rx > 40) {
      print_and_udp("5555555555", 0, 0, souryou);
    } else if (Rx < 130 && Rx > 80) {
      print_and_udp("6666666666", 0, 0, souryou);
    }
    // int Ly = PS4.LStickY();
    // if (Ly < gosa && Ly > -gosa) {
    //   print_and_udp("l", 1, 0, souryou);
    // } else {
    //   print_and_udp("l", 1, Ly, souryou);
    // }



    int Lx = PS4.LStickX();
    if (Lx < -80 && Lx > -130) {
      print_and_udp("zzzzzzzzzzz", 0, 0, souryou);
    } else if (Lx < -40 && Lx > -80) {
      print_and_udp("xxxxxxxxxx", 0, 0, souryou);
    } else if (Lx < -12 && Lx > -40) {
      print_and_udp("cccccccccc", 0, 0, souryou);
    } else if (Lx < 40 && Lx > 12) {
      print_and_udp("vvvvvvvvvv", 0, 0, souryou);
    } else if (Lx < 80 && Lx > 40) {
      print_and_udp("bbbbbbbbbb", 0, 0, souryou);
    } else if (Lx < 130 && Lx > 80) {
      print_and_udp("nnnnnnnnnn", 0, 0, souryou);
    }

    int Ly = PS4.LStickY();
    if (Ly < -80 && Ly > -130) {
      print_and_udp("NNNNNNNNNN", 0, 0, souryou);
    } else if (Ly < -40 && Ly > -80) {
      print_and_udp("BBBBBBBBBB", 0, 0, souryou);
    } else if (Ly < -12 && Ly > -40) {
      print_and_udp("VVVVVVVVVV", 0, 0, souryou);
    } else if (Ly < 40 && Ly > 12) {
      print_and_udp("CCCCCCCCCC", 0, 0, souryou);
    } else if (Ly < 80 && Ly > 40) {
      print_and_udp("XXXXXXXXXX", 0, 0, souryou);
    } else if (Ly < 130 && Ly > 80) {
      print_and_udp("ZZZZZZZZZZ", 0, 0, souryou);
    }








    delay(tien);
  }
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    udp.read(incomingPacket, packetSize);
    incomingPacket[packetSize] = '\0';
    Serial.print(incomingPacket);
    Serial.print("\n");
  }
}

void print_and_udp(char *buf, char flag, int val, int val2) {
  int l = 0;
  while (val2 > l) {
    char buffer[16];
    if (flag) {
      sprintf(buffer, "%s%d", buf, val);
    } else {
      sprintf(buffer, "%s", buf);
    }
    Serial.printf(buffer);
    udp.beginPacket(IPAddress(192, 168, 8, 116), 1234);  // IP address and port of the receiver ESP32
    udp.print(buffer);
    udp.print("\n");
    Serial.printf("\n");
    udp.endPacket();
    l++;
  }
}
