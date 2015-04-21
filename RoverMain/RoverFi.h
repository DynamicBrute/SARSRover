#include <Energia.h>

#include <SPI.h>
#include <WiFi.h>

#define LAT1 28.603848
#define LON1 -81.199509
#define LAT2 28.603806
#define LON2 -81.199394
#define LAT3 28.603760
#define LON3 -81.199287


// your network name also called SSID
extern char ssid[];
// your network password
extern char password[];

extern WiFiClient debugClient;
extern WiFiServer debugServer;
extern WiFiServer mainServer;
extern WiFiServer teleServer;
extern WiFiClient teleClient;

extern boolean alreadyConnected, alreadyConnectedMain, alreadyConnectedTele;

void startWiFi();

void printWifiStatus();

//Wait until data is received from the CDC
void waitForTarget();

void transmitTele();
