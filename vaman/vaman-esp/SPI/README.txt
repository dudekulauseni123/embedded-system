README
------

CONNECTIONS
-----------

-----------------------------------
|  PIN ID   | VAMAN-ESP | ARDUINO |
-----------------------------------
|    CLK    |    14     |   D13   |
-----------------------------------
| MISO/CIPO |    12     |   D12   |
-----------------------------------
| MOSI/COPI |    13     |   D11   |
-----------------------------------
|   SS/CS   |    15     |   D10   |
-----------------------------------
|    GND    |    GND    |   GND   |
-----------------------------------

CREDENTIALS
-----------

You need to create a header file "./esp32/src/credentials.h" with the following
contents:

const char *ssid = "YOUR-SSID-HERE";
const char *password = "YOUR-PASSWORD-HERE";
const char *spiURL = "SERVER-URL-TO-DISPLAY-MESSAGE";

SETUP
-----

Flash the Arduino and ESP32 with the platformio projects in their respective
directories.

To run the server, you require a Python 3 virtual environment with Flask
installed. You can run it by entering the following commands at a terminal
window:

# Activate your virtual environment if you haven't already
source <PATH-TO-VENV>/bin/activate
cd ./server
flask run --host <HOST-IP>
