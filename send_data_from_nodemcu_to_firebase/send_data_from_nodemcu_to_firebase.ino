#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "Virinchi LAB"
#define WIFI_PASSWORD "tech&inovation"
#define API_KEY "AIzaSyBSBcbN_RU5kOejK_xDkPwiFMKwpEK_ZcM"
// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://dietz-knots-default-rtdb.asia-southeast1.firebasedatabase.app/"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


bool signupOK = false;


void setup()
{
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
    ESP.restart();
  }
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);


}
void loop()
{
  int height = 10;
  float temp1 = 20.40;
  String humidity = "40";
  if ((WiFi.status() == WL_CONNECTED))
  {
    if (Firebase.ready() && signupOK)
    {

      if (Firebase.RTDB.setInt(&fbdo, "test/Height", height )) {
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      }
      else
      {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
        ESP.restart();
      }
      if (Firebase.RTDB.setFloat(&fbdo, "test/Temperature", temp1))
      {
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());

      }
      else
      {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
        ESP.restart();
      }

      if (Firebase.RTDB.setString(&fbdo, "test/Humidity", humidity))
      {
        Serial.println("PASSED");
        Serial.println("PATH: " + fbdo.dataPath());
        Serial.println("TYPE: " + fbdo.dataType());
      }
      else
      {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());


      }
    }
    delay(1000);
  }
}
