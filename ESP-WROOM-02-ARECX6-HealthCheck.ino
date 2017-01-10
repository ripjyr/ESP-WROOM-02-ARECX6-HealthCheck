#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <Time.h>
#include <TimeLib.h>

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "SSID"
#define WLAN_PASS       "PASS"
WiFiClient client;

/************ Connection to ARECX6 Setting ******************/
const char* host = "192.168.XX.XX";
const int httpPort = 80;

/************ Global State  ******************/
#define DEBUG
//#define HTTP_DEBUG

/************ Sleep Settings ******************/
extern "C" {
#include <user_interface.h>
}
// DeepSleep 2min.
long sleep_interval = 2 * 60 * 1000 * 1000;

/************ Debug Settings ******************/
void setupWiFi() {
#ifdef DEBUG
  Serial.println(); Serial.println();
  Serial.println(F("WiFi Connection->AP=================="));
  Serial.println(F("Connecting to ")); Serial.print(WLAN_SSID);
#endif

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  int wifiCounter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(450);
    Serial.print(F("."));
    if (wifiCounter > 20) {
      Serial.println(F("Failed to connect WiFi. Reset now."));
      delay(500);
      ESP.deepSleep(2 * 1000 * 1000);
      delay(1000);
    }
    delay(50);
    wifiCounter++;
  }
#ifdef DEBUG
  Serial.println(F("WiFi connected"));
  Serial.print(F("IP address: ")); Serial.println(WiFi.localIP());
#endif
  wifi_set_sleep_type(LIGHT_SLEEP_T);
};

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println(F("Serial start..."));

  delay(10);
  Serial.println(F("=========================================================================="));
  setupWiFi();
};

boolean httpget(String temp_uri) {
  HTTPClient http_update;
  http_update.begin(temp_uri); //HTTP
  int httpCode = http_update.GET();
  if (httpCode == HTTP_CODE_OK) {
    String payload = http_update.getString();
#ifdef HTTP_DEBUG
    Serial.println(payload);
#endif
    http_update.end();
    return true;
  } else {
#ifdef HTTP_DEBUG
    Serial.print(F("HTTP Code: "));
    Serial.println(httpCode);
#endif
    http_update.end();
    return false;
  }
};

void loop() {
  Serial.println(F("ARECX6 status========================"));
#ifdef DEBUG
  Serial.print(F("ARECX6: "));
  Serial.println(host);
#endif

if (!client.connect(host, httpPort)) {
    Serial.println(F("ARECX6 connection failed"));
    return;
  }

  // We now create a URI for the request
  // ARECX6 Can't HTTP Get by httpget(). so RAW HTTP Get.
  String url = "/cgi/get.cgi?type=top";
#ifdef DEBUG
  Serial.print(F("Requesting URL: "));
  Serial.println(url);
#endif

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  //delay(5000);
  unsigned long timeout = millis();

  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  int rec_status_value;
  String rec_status_check;
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    line.trim();

    rec_status_check = line.substring(0, 10);
    if (rec_status_check.equals("rec_status")) {
      rec_status_value = line.substring(11, 12).toInt();
#ifdef DEBUG
      Serial.print(F("rec_status: "));
      Serial.println(rec_status_value);
#endif
      if (rec_status_value == 1) {
#ifdef DEBUG
        Serial.println(F("Rec status is OK!"));
#endif
      } else {
        Serial.println(F("Rec status is Error!\nNeed to reboot!!"));
        Serial.println(F("Reboot ARECX6"));
        // reboot
        String reboot_url = "http://"+String(host)+"/cgi/get.cgi?type=reboot&rnd=1";
        httpget(reboot_url);
#ifdef DEBUG
        Serial.println(F("Sleep 2 minits"));
#endif
        delay(2 * 60  * 1000); // delay 2min to boot ARECX6
        // rec start
        Serial.println(F("Rec Start ARECX6"));
        String recstart_url = "http://"+String(host)+"/cgi/get.cgi?type=rec_start&rnd=1";
        httpget(recstart_url);
      }
    }

#ifdef HTTP_DEBUG
    Serial.println(F("---"));
    Serial.println(line);
    Serial.println(F("---"));
#endif
    line = "";
  }
  Serial.println(F("closing ARECX6 connection============"));
  Serial.println(F("=========================================================================="));
  delay(1000);
  ESP.deepSleep(sleep_interval, WAKE_RF_DEFAULT);
};

