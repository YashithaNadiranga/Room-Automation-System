#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
#include <FirebaseJson.h>

#include <ESP8266WiFi.h>

#define FIREBASE_HOST "room-automation-28ec2.firebaseio.com"
#define FIREBASE_AUTH "qhGzyp5n318UST0gdGkQ69HXeNRMeEg3besrtwZo"
#define WIFI_SSID "Yashitha"
#define WIFI_PASSWORD "ymax26574ymax"

FirebaseData firebaseData;
String arrays;

String l1;
String l2;
String l3;
String l4;
String responce;

String bLight01;
String bLight02;
String bLight03;
String bLight04;

void setup() {
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  
  Serial.begin(115200);
  // Serial.setTimeout(20);
  // connect to wifi.

  connectWIFI();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  while (WiFi.status() == WL_CONNECTED) {
      Serial.println(WiFi.status());
      Firebase.getString(firebaseData, "Home");
      arrays = firebaseData.stringData();
      arrays.replace("[", "");
      arrays.replace("]", "");
      l1 = getValue(arrays, ',', 0);
      l2 = getValue(arrays, ',', 1);
      l3 = getValue(arrays, ',', 2);
      l4 = getValue(arrays, ',', 3);
      Firebase.getString(firebaseData, "Device Respond");
      responce = firebaseData.stringData();
      Serial.println(l1+" "+l2+" "+l3+" "+l4);

//===============================================
      if(responce.equals("1")){
        Firebase.set(firebaseData, "Device Respond", "2");
      }

//====================L1=========================      
      if (!l1.equals(NULL)) {
        if(l1 != bLight01){
          bLight01 = l1;
        }
      }
      if (l1.equals("1")) {
        Serial.println("Light01 ON");
        digitalWrite(D5, HIGH);
        Firebase.set(firebaseData, "L1 Respond", "1");
      } else {
        Serial.println("Light01 OFF");
        digitalWrite(D5, LOW);
        Firebase.set(firebaseData, "L1 Respond", "0");
      } 
//=================================================

//====================L2==========================      
      if (!l2.equals(NULL)) {
        if(l2 != bLight02){
          bLight02 = l2;
        }
      }
      if (l2.equals("1")) {
        Serial.println("Light02 ON");
        digitalWrite(D6, HIGH);
        Firebase.set(firebaseData, "L2 Respond", "1");
      } else {
        Serial.println("Light02 OFF");
        digitalWrite(D6, LOW);
        Firebase.set(firebaseData, "L2 Respond", "0");
      } 
//================================================

//====================L3==========================      
      if (!l3.equals(NULL)) {
        if(l3 != bLight03){
          bLight03 = l3;
        }
      }
      if (l3.equals("1")) {
        Serial.println("Light03 ON");
        digitalWrite(D7, HIGH);
        Firebase.set(firebaseData, "L3 Respond", "1");
      } else {
        Serial.println("Light03 OFF");
        digitalWrite(D7, LOW);
        Firebase.set(firebaseData, "L3 Respond", "0");
      } 
//================================================

//====================L4==========================      
      if (!l4.equals(NULL)) {
        if(l4 != bLight04){
          bLight04 = l4;
        }
      }
      if (l4.equals("1")) {
        Serial.println("Light04 ON");
        digitalWrite(D8, HIGH);
        Firebase.set(firebaseData, "L4 Respond", "1");
      } else {
        Serial.println("Light04 OFF");
        digitalWrite(D8, LOW);
        Firebase.set(firebaseData, "L4 Respond", "0");
      } 
}

  //=================================================================

  if(bLight01.equals("1")){
    digitalWrite(D5, HIGH);
  }else if(bLight01.equals("0")){
    digitalWrite(D5, LOW);
  }

  if(bLight02.equals("1")){
    digitalWrite(D6, HIGH);
  }else if(bLight02.equals("0")){
    digitalWrite(D6, LOW);
  }

  if(bLight03.equals("1")){
    digitalWrite(D7, HIGH);
  }else if(bLight03.equals("0")){
    digitalWrite(D7, LOW);
  }

  if(bLight04.equals("1")){
    digitalWrite(D8, HIGH);
  }else if(bLight04.equals("0")){
    digitalWrite(D8, LOW);
  }
}

//====================================================================

void firebasereconnect() {
  connectWIFI();
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(1000);
}

void connectWIFI() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());
}

void correctRespond(){
  Firebase.set(firebaseData, "L1 Respond", l1);
  Firebase.set(firebaseData, "L2 Respond", l2);
  Firebase.set(firebaseData, "L3 Respond", l3);
  Firebase.set(firebaseData, "L4 Respond", l4);
}
