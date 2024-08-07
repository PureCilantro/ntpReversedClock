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
- According to your time zone, in my case GMT-6, multiply the offset by 3600 (-6 * 3600 = -21600)
- On line 43 `NTPClient timeClient(ntpUDP, "3.mx.pool.ntp.org", -21600, 43200);` replace the _3.mx.pool.ntp.org_ direction with your own, and replace the _-21600_ with your time zone offset calculation.
  <br><br>
- Select the COM port and the `NodeMCU 1.0 (ESP-12E Module)` board and upload the code.

### 2. Building a case

- My design holds the acrylic sheet at 48.25°, slightly elevated and the height of the case is enough to hold the ESP8266 vertically inside.
I desoldered the VIN side headers so the board takes up less space and soldered a [USB-C port](https://es.aliexpress.com/item/1005005673073529.html?spm=a2g0o.order_list.order_list_main.67.70df194dN1B7Wq&gatewayAdapt=glo2esp) to VIN and GND that gets inserted into the back of the case and powered the display through  the VV pin.
- My case design was laser cut on 3mm thick MDF, put together with wood glue, filled in, sanded down with 220 and finished with 480 grit sandpaper.
- Finally it was painted with a chocolate color oil spray can.

_Note: I didn't glue the bottom cover for ease of access in case I need to update the software or something breaks_

### 3. Care and final notes

- Make sure to clean the acrylic regularly to maintain the transparency of it and the HUD effect.
- My desk setup is not that bright and at night the display would easily illuminate my whole room red, so I cut a piece of window tinting film to the size of the display and its fine now.
