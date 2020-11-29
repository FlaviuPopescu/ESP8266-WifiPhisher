<p align="center"><img alt="PICTURE logo" src="https://i.imgur.com/QVJjB9k.jpg" width="200"></p>

<p align="center">
🌍 <a href="http://wifiphisher.tk">wifiphisher.tk</a><br>
<br></p>

# ESP8266 WifiPhisher
A super portable evil device, based on the ESP8266 board.

## Attacks

- **Wi-Fi deauthentication attack**: Scan for WiFi devices, block selected connections.

- **Captive Portal**: it creates a "free hotspot" and redirects the users to a registration page, where they - hopefully - enter their usual facebook/password combination. Anyway, it never makes them sign in

- **Evil Twin**: it looks for nearby protected networks and lets you select the target one, then it sets up an open access point with the same ESSID of the victim and it uses a captive portal to redirect the users to a page which requires the WiFi password "in order to complete the firmware upgrade".

- **Beacon Spammer**: it spams multiple WiFi beacons to make appear many fake access points on the nearby devices.

## Video demo
[![Watch the video](https://img.youtube.com/vi/pXWLexnZQmU/0.jpg)](https://youtu.be/pXWLexnZQmU)

## Pinout
<p><img alt="PICTURE logo" src="https://hackster.imgix.net/uploads/attachments/1212694/244v234_pe3ov4zwv9_xBZN30K1NU.jpg?auto=compress%2Cformat&w=740&h=555&fit=max" width="200"></p>

## Installation  
***YOU ONLY NEED TO DO ONE OF THE INSTALLATION METHODS!***

#### 1.Uploading the .bin files 
* recommended! Tutorials are available on youtube
#### 2.Compiling the source with Arduino
First you have to install and open the Arduino IDE.
* Add the required libraries
* In Arduino go to File -> Preferences add URL in Additional Boards Manager URLs 
https://raw.githubusercontent.com/SpacehuhnTech/arduino/main/package_spacehuhn_index.json
* Go to Tools -> Board -> Boards Manager, search "deauther" and install Deauther ESP8266 Boards
* Select your board at Tools -> Board and be sure it is at Deauther ESP8266 Boards (and not at ESP8266 Modules)!
* Clone the project to get the latest changes, but you will also get the latest bugs ;)
* Extract the whole .zip file, and open ESP8266-WifiPhisher.ino with Arduino.
* Check your upload settings and press upload!

## :octocat: Contribute
All contributions are welcome! Code, documentation, graphics, or even design suggestions are welcome; use GitHub to its fullest. Submit pull requests, contribute tutorials -- whatever you have to offer, it'll be appreciated.

## Under Development
Currently, the ESP8266 WifiPhisher has limited software capabilities. New firmware features will be added over time and will eventually reach the point where this project becomes the smallest hacking machine.

## Disclaimer
Usage of ESp8266 Wifiphisher for attacking infrastructures without prior mutual consistency can be considered as an illegal activity. It is the final user's responsibility to obey all applicable local, state and federal laws. Authors assume no liability and are not responsible for any misuse or damage caused by this program.

## Note
* Beware of websites pretending to be related to the ESP8266 WifiPhisher Project. They may be distributing malware.
* WifiPhisher does not work on esp32. There is no way to inject packets on the ESP32.

##### This source code is built on Deauther
