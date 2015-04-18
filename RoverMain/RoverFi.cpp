#include "RoverFi.h"
#include "GPS.h"
//#include "RoverMain.h"

char ssid[] = "42";
// your network password
char password[] = "brainNet";


WiFiClient debugClient;

//Server object, the argument is the port that it listens too
WiFiServer debugServer(3284);
WiFiServer mainServer(7277);

boolean alreadyConnected, alreadyConnectedMain;

//Connect to a WiFi network
void startWiFi()
{
  // attempt to connect to Wifi network:
    Serial.print("Attempting to connect to Network named: ");
    // print the network name (SSID);
    Serial.println(ssid); 
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, password);
    while ( WiFi.status() != WL_CONNECTED) {
      // print dots while we wait to connect
      Serial.print(".");
      delay(300);
    }
    
    Serial.println("\nYou're connected to the network");
    Serial.println("Waiting for an ip address");
    
    while (WiFi.localIP() == INADDR_NONE) {
      // print dots while we wait for an ip addresss
      Serial.print(".");
      delay(300);
    }
  
    Serial.println("\nIP Address obtained");
  
    // you're connected now, so print out the status:
    printWifiStatus();
    
    alreadyConnectedMain = false;
}
 

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  
  debugClient.print("SSID: ");
  debugClient.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  debugClient.print("IP Address: ");
  debugClient.println(ip);

  // print the received signal strength:
  debugClient.print("signal strength (RSSI):");
  debugClient.print(rssi);
  debugClient.println(" dBm");
}

void waitForTarget()
{
  //define a client object to connect to the server
  /*WiFiClient mainClient;
  
  //debug LED
  digitalWrite(LED1, HIGH);
  
  //wait for a client to connect to the server
  while(!alreadyConnectedMain)
  {
    //attempt to save a client connecting to the server
    mainClient = mainServer.available();
    
    //if a client is connected, begin communication
    if (mainClient) {
      if (!alreadyConnectedMain) {
        // clead out the input buffer:
        mainClient.flush();
        Serial.println("We have a new client");
        debugServer.println("We have a new client");
        mainClient.println("Hello, client!");
        alreadyConnectedMain = true;
        
      }
    }
    
    delay(100);
    
    delay(100);
  }
  Serial.println("writing");
  debugClient.println("writing");
  
  //mainServer.println("ready");
  delay(1000);
  
  //Strings to read in latitude and longitude from the client
  char lat[50] = "";
  char lon[50] = "";
  
  int ind = 0;
  
  //Wait for input to be on the buffer
  while(!mainClient.available());
  
  //Read in characters from the input buffer until a new line character is reached
  //this will be the latitude
  while(mainClient.available())
    {
      char c = mainClient.read();
      lat[ind] = c;
      
      if(c == '\n')
      {
        lat[ind] = NULL;
        break;
      }
      
      ind++; 
    }
  
  ind = 0;
  
  //Read in characters from the input buffer until a new line character is reached
  //this will be the longitude
  while(mainClient.available())
    {
      char c = mainClient.read();
      lon[ind] = c;
      
      if(c == '\n')
      {
        lon[ind] = NULL;
        break;
      }
      
      ind++; 
    }
    
  mainClient.stop();
  
  //convert from a string to a float
  tarLat = strtof(lat, NULL);
  tarLon = strtof(lon, NULL);
*/
  
  //digitalWrite(LED1, LOW);
  
  //tarLat = atof(lat);
  //tarLon = atof(lon);
  
  Serial.print("Lat: ");
  Serial.print(lat);
  Serial.print(" ");
  Serial.println(tarLat, 6);
  Serial.print("Lon: ");
  Serial.print(lon);
  Serial.print(" ");
  Serial.println(tarLon, 6);
  
  debugClient.print("Lat: ");
  debugClient.print(lat);
  debugClient.print(" ");
  debugClient.println(tarLat, 6);
  debugClient.print("Lon: ");
  debugClient.print(lon);
  debugClient.print(" ");
  debugClient.println(tarLon, 6);
  
  //Erick's
  //tarLat = 28.504906f;
  //tarLon = -81.457456f;
  
  //apt
  //tarLat = 28.582183f;
  //tarLon = -81.202770f;
  
  //curLat = 28.628811f;
  //curLon = -81.199479f;
  
  //mem mall
  //curLat = 28.603492;
  //curLon = -81.198982;
  
  //matt's
  tarLat = 28.628391;
  tarLon = -81.200013;
}
