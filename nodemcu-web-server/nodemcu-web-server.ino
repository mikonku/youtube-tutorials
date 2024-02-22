#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "index.h"
#include "response_json.h"

ESP8266WebServer server(80);

const char *ssid = "mikonku";
const char *password = "bambang123456";

// mendefinisikan fungsi untuk setiap halaman
void homePage();
void kitchenPage();


void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ... ");

  int i = 0;
  // menunggu hingga WiFi terhubung
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println("Connection established!");
  Serial.println(WiFi.localIP());

  // route halaman utama "bedroom"
  server.on("/", homePage);
  // route kicthen
  server.on("/kitchen", kitchenPage);

  // when page not found
  server.onNotFound([]() {
    return server.send(404, "text/html", "Page not found!");
  });
  server.begin();
}

void loop() {
  server.handleClient();
}

/*
fungsi pembacaan sensor,
ini hanya simulasi 
nanti bisa diganti isinya dengan pembacaan sensor sesungguhnya
*/
float temperatureSensor(int pin = 13) {

  // buat nilai random simulasi untuk sensor
  int intValue = random(2000, 3500);

  // buat agar balikan memiliki nilai float
  return (float)intValue / 100.0;
}

/* fungsi untuk konversi progmem ke string */
String toStringConverter(const char *progmemVar) {
  // penampungan nilai string
  String result;

  // melakukan pembacaan byte per byte
  // nilai byte akan disimpan dalam variabel c
  char c;
  while ((c = pgm_read_byte(progmemVar++))) {
    // append string byte per byte
    result += c;
  }

  // kembalikan hasil string nya
  return result;
}


/*
  detil dari homePage()
*/
void homePage() {
  String title = "Bedroom";

  /*
    cek apakah ada query parameter dengan key "device"
    contoh http://0.0.0.0/?device=bedroom
    jika ada maka akan mengembalikan json sesuai file "response_json.h"
  */
  String deviceArg = server.arg("device");
  if (!deviceArg.isEmpty()) {
    String response = toStringConverter(json);

    // ubah nilai json berdasarkan pembacaat sensor suhu
    // ini pemisalan jika menggunakan sensor LM35 dengan pin 13
    int pinBedroomTemperature = 13;
    response.replace("{{value}}", String(temperatureSensor(pinBedroomTemperature), 2));

    // kembalikan json response
    return server.send(200, "application/json", response);
  }

  // jika tidak ada query parameter maka akan mengembalikan view html
  String view = toStringConverter(page);

  // replace {{device}} menjadi nilai variable title
  view.replace("{{device}}", title);

  // kembalikan response html
  return server.send(200, "text/html", view);
}


/*
  detil dari homePage()
*/
void kitchenPage() {
  String title = "Kitchen";

  /*
    cek apakah ada query parameter dengan key "device"
    contoh http://0.0.0.0/kitchen?device=bedroom
    jika ada maka akan mengembalikan json sesuai file "response_json.h"
  */
  String deviceArg = server.arg("device");
  if (!deviceArg.isEmpty()) {
    String response = toStringConverter(json);

    // ubah nilai json berdasarkan pembacaat sensor suhu
    // ini pemisalan jika menggunakan sensor LM35 dengan pin 13
    int pinBedroomTemperature = 13;
    response.replace("{{value}}", String(temperatureSensor(pinBedroomTemperature), 2));

    // kembalikan json response
    return server.send(200, "application/json", response);
  }

  // jika tidak ada query parameter maka akan mengembalikan view html
  String view = toStringConverter(page);

  // replace {{device}} menjadi nilai variable title
  view.replace("{{device}}", title);

  // kembalikan response html
  return server.send(200, "text/html", view);
}
