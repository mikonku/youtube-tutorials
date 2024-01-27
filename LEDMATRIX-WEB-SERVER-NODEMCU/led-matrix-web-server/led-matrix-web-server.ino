#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h"

#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN D4
String text;

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
ESP8266WebServer server(80);

const char *ssid = "esp-led-matrix";
const char *password = "password";

textEffect_t animation[]={
  PA_SCROLL_LEFT,
  PA_SCROLL_RIGHT
};

int animationIndex = 0;

void homePage();

void setup(void) {
  P.begin();
  text = "Hello World!";
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

void loop(void) {
  server.handleClient();

  if (P.displayAnimate()) {
    P.displayText(text.c_str(), PA_CENTER, 100, 100, animation[animationIndex], animation[animationIndex]);
  }
}

void homePage() {
  String textArg = server.arg("text");
  String animationArg = server.arg("animation");
  int animationArgInt = animationArg.toInt();
  if (textArg != "") {
    text = textArg;
  }
  if (animationArgInt <= 1 && animationArgInt >= 0) {
    animationIndex = animationArgInt;
  }

  return server.send(200, "text/html", page);
}