//
//  Socket.h
//  Socket
//
//  Created by justin on 2020/12/17.
//

#ifndef Socket_h
#define Socket_h

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Nines_TestRoom"       // "your-ssid" 
#define STAPSK  "999999999"            // "your-password"
#endif
const char* ssid = STASSID;
const char* password = STAPSK;

IPAddress ip(192, 168, 2, 21); // 사용할 IP 주소
IPAddress gateway(192, 168, 2, 1); // 게이트웨이 주소
IPAddress subnet(255, 255, 255, 0); // 서브넷 주소

const char* host = "192.168.2.4";
const uint16_t port = 8000;

int state_ip;
int state_ip_check;

#endif /* Socket_h */
