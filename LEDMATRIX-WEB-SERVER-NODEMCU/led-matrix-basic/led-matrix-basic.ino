#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN D4
String text;

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup(void) {
  P.begin();
  text = "Hello World!";
}

void loop(void) {
  if (P.displayAnimate()) {
    P.displayText(text.c_str(), PA_CENTER, 100, 100, animation[2], animation[2]);
  }
}
