#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h"

ESP8266WebServer server(80);

const char *ssid = "esp-led-matrix";
const char *password = "password";
String text;


void homePage();

void setup() {
  Serial.begin(9600);
  Serial.println();

  WiFi.softAP(ssid, password);
  Serial.println(WiFi.softAPIP());

  // HOMEPAGE
  server.on("/", homePage);

  // PAGE NOT FOUND HANDLER
  server.onNotFound([]() {
    return server.send(404, "text/html", "Page Not Found!");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

void homePage() {
  String textArg = server.arg("text");
  if (textArg != "") {
    text = textArg;
  }
  return server.send(200, "text/html", page);
}
