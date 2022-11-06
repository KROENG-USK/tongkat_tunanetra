#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Setting WiFi Hotspot
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

// konfigurasi pin buzzer
#define buzzPin D1

// reconnect wifi if disconnect
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buzzPin, OUTPUT);
  
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
  // Get Action Button
  bool buttonState;
  Firebase.getBool(firebaseData, path_1, &buttonState);
  if(buttonState == true){
    tone(buzzPin, 5000, 60);
    // digitalWrite(buzzPin, HIGH);
    Serial.println("Hidup");
  }
  else if(buttonState == false){
    noTone(buzzPin);
    // digitalWrite(buzzPin, LOW);
    Serial.println("Mati");
  }

  delay(20);

}
