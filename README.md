<p align="center"><img alt="PICTURE logo" src="https://i.imgur.com/QVJjB9k.jpg" width="200"></p>

<p align="center">
  🐦<a href="https://twitter.com/244v234">Twitter</a>
| 📺 <a href="https://www.youtube.com/channel/UC5yaB0VU_u4sY-DiE0BGuSw/featured?view_as=subscriber">YouTube</a>
| 🌍 <a href="https://wifiphisher.tk">wifiphisher.tk</a><br>
<br></p>

## ESP8266 WifiPhisher
This software allows you to easily perform a variety of actions to test 802.11 wireless networks by using an inexpensive ESP8266 WiFi SoC (System On A Chip).

## Main feature
* The deauthentication attack, is used to disconnect devices from their WiFi network.	
* It is capable of performing a social engineering attack to get a secret WPA / WPA2 password
<p><img alt="PICTURE logo" src="https://hackster.imgix.net/uploads/attachments/1212751/z2157794471160_228d60f39af25e94bedaa5f43a7ae730_0KtXp9MOEw.jpg?auto=compress%2Cformat&w=740&h=555&fit=max" width="200"</p>
## Video demo
[![Watch the video](https://img.youtube.com/vi/9W9xHPFy9rc/0.jpg)](https://youtu.be/9W9xHPFy9rc)
## Pinout
<p><img alt="PICTURE logo" src="https://hackster.imgix.net/uploads/attachments/1212694/244v234_pe3ov4zwv9_xBZN30K1NU.jpg?auto=compress%2Cformat&w=740&h=555&fit=max" width="200"></p>

## [Flashing the firmware bin file](https://www.hackster.io/234v244/esp8266-wifiphisher-4ed3d3)

## Compiling using Arduino IDE
First you have to install and open the Arduino IDE.
- Add the required [libraries](https://drive.google.com/drive/folders/1QKlt-UVW6BszD1YrvQ47xcYCMHJUfeuS?usp=sharing)
- In Arduino go to File -> Preferences add both URLs in Additional Boards Manager URLs https://raw.githubusercontent.com/SpacehuhnTech/arduino/main/package_spacehuhn_index.json
- Go to Tools -> Board -> Boards Manager, search "deauther" and install Deauther ESP8266 Boards
- Select your board at Tools -> Board and be sure it is at Deauther ESP8266 Boards (and not at ESP8266 Modules)!
- Download the source code for this project from the releases page. You can also clone the project to get the latest changes, but you will also get the latest bugs ;)
- Extract the whole .zip file, and open WifiPhisher.ino with Arduino.
- Check your upload settings and press upload!
[Libraries](https://drive.google.com/drive/folders/1QKlt-UVW6BszD1YrvQ47xcYCMHJUfeuS?usp=sharing)

## :octocat: Contribute
All contributions are welcome! Code, documentation, graphics, or even design suggestions are welcome; use GitHub to its fullest. Submit pull requests, contribute tutorials -- whatever you have to offer, it'll be appreciated

## Under Development
Currently, the ESP8266 WifiPhisher has limited software capabilities. New firmware features will be added over time and will eventually reach the point where this project becomes the smallest hacking machine.

## Disclaimer
Usage of ESp8266 Wifiphisher for attacking infrastructures without prior mutual consistency can be considered as an illegal activity. It is the final user's responsibility to obey all applicable local, state and federal laws. Authors assume no liability and are not responsible for any misuse or damage caused by this program.

## Note
* Beware of websites pretending to be related to the ESP8266 WifiPhisher Project. They may be distributing malware.
* WifiPhisher does not work on esp32. There is no way to inject packets on the ESP32

##### This source code is built on [Deauther](https://github.com/SpacehuhnTech/esp8266_deauther)
