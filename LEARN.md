# How to build
### 1. Materials

- A MAX7219 1x4 dot matrix display ([here is the exact one I used](https://es.aliexpress.com/item/1005006191542573.html?spm=a2g0o.cart.0.0.6aea7a9dQa4QHf&mp=1&gatewayAdapt=glo2esp))
- A ESP8266 board ([here is the exact one I used](https://es.aliexpress.com/item/1005005977505151.html?spm=a2g0o.cart.0.0.6aea7a9dQa4QHf&mp=1&gatewayAdapt=glo2esp))

_Note: the displays usually come with their own cables, the ESP8266 don't so you just need a micro USB cable to upload the code and or power the board._

### 2. Uploading the code

- First you need to add the ESP8266 board family to your Arduino IDE, you can follow [this](https://projecthub.arduino.cc/PatelDarshil/getting-started-with-nodemcu-esp8266-on-arduino-ide-b193c3) tutorial.
- On line 35 `const char *ssid     = "";` insert the SSID for your WiFi.
- On line 36 `const char *password = "";` insert the password for your WiFi.
  <br><br>
- Go to [ntp pool](https://www.ntppool.org/en/) and copy the direction for a server of your country or continent.
- Acording to your timezone, in my case GMT-6, multiply the offset by 3600 (-6 * 3600 = -21600)
- On line 43 `NTPClient timeClient(ntpUDP, "3.mx.pool.ntp.org", -21600, 43200);` replace the _3.mx.pool.ntp.org_ direction with your own, and replace the _-21600_ with your timezone calculation.
  <br><br>
- Select the COM port and the `NodeMCU 1.0 (ESP-12E Module)` board and upload the code.
