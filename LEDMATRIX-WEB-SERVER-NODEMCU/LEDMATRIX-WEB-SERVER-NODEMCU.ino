#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN D4
String text_led;

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
ESP8266WebServer server(80);

String responseHTML = "<!DOCTYPE html>"
                      "<html>"
                      "<body>"
                      "<h2>Change Text</h2>"
                      "<form action='/' method='GET'>"
                      "  <label for='text'>Text:</label><br>"
                      "  <input type='text' id='text' name='text'><br>"
                      "  <input type='submit' value='Submit'>"
                      "</form>" 
                      "</body>"
                      "</html>";
void handleRoot() {
  String text = server.arg("text"); // Mengambil nilai parameter 'name'

  if(text != ""){
    text_led = text;
  }

  Serial.println(text);
  server.send(200, "text/html", responseHTML);  
}

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const char *ssid = "mikonku-led-matrix"; // The name of the Wi-Fi network that will be created
const char *password = "mikonku123";  // The password required to connect to it, leave blank for an open network
void setup(void) {
  P.begin();
  Serial.begin(9600);  // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  text_led = "Hello World";
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid);
  // WiFi.softAP(ssid, password);

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  server.onNotFound(handleRoot);
  server.begin();
}

void loop(void) {
  dnsServer.processNextRequest();
  server.handleClient();
  
  if (P.displayAnimate())
    P.displayText(text_led.c_str(), PA_CENTER, 100, 100, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}
