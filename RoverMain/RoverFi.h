#include <Energia.h>

#include <SPI.h>
#include <WiFi.h>

// your network name also called SSID
extern char ssid[];
// your network password
extern char password[];

extern WiFiClient debugClient;
extern WiFiServer debugServer;
extern WiFiServer mainServer;

extern boolean alreadyConnected, alreadyConnectedMain;

void startWiFi();

void printWifiStatus();

//Wait until data is received from the CDC
void waitForTarget();
