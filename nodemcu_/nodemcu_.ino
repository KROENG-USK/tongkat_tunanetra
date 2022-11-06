#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Setting find WiFi Hotspot
#ifndef WIFI_SSID
#define WIFI_SSID "TP-Link_6A47"
#define WIFI_PASSWORD "44585174"
#endif

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// Setting Firebase database
#define FIREBASE_HOST "https://tongkat-proyek-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "95K52SPwsffZyQgBf0JZw9MCcaY6IjzG8SR39F7x"

// root json firebase
const String path_1 = "data-aksi/button";

FirebaseData firebaseData; //firebase function

// konfigurasi button
const int button = D2; // D2 (gpio4)
int buttonState = 0;

// reconnect wifi if disconnect
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

//void ICACHE_RAM_ATTR loop(); // jika nodemcu intrrupt

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(button, INPUT_PULLUP);
  
  // setup wifi connection
  // Register event handlers
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  initWiFi();
  Serial.print(F("RRSI : "));
  Serial.println(WiFi.RSSI());
    
  // Setup firebase auth & host link
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //Firebase.reconnectWiFi(true);
  //firebaseData.setBSSLBufferSize(1024, 1024);
  //firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //Firebase.setwriteSizeLimit(firebaseData, "tiny");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // Send Action Button
  buttonState = digitalRead(button);
  switch(buttonState){
    case 0:
      // Push data in database if case 0
      Firebase.setBool(firebaseData, path_1, false);
      Serial.println("Tidak ada bahaya...");
      delay(5);
      break;

    case 1:
      // Push data in database
      Firebase.setBool(firebaseData, path_1, true);
      Serial.println("Ada bahaya...");
      delay(5);
      break;
    
    default:
    break;
  }
  
  delay(15);
}