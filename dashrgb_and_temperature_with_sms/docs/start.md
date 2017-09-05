For this demo you will need 

#Required:
1. Hologram Dash (Dash Pro should work as well). With working SIM already setup on the Hologram.io site/Dashboard.
2. A common Cathode RGB or a Keys RGB Breakout board (note: My Keys breakout board has the blue and the red marked incorrectly, so be aware)
3. a DHT11 or DHT22 temerature/humidity sensor

The DHT library is required for the sketch.
https://github.com/gawadinc/adafruit-DHT-sensor-library 
https://github.com/adafruit/Adafruit_Sensor
This can either be installed from github, or using the library manager in the
Arduino IDE.

#Not required but used by this demo
Newtifry notification service for Android
https://play.google.com/store/apps/details?id=com.newtifry.android
https://newtifry.appspot.com
https://c9.io/kd8bxp/dashsms (used as another way to send messages to your device)

#Good reading
https://community.hologram.io/t/webhooks-examples/225/3 This whole thread is good and really what this demo is based on. In the thread the author was asking about using thingspeak. Hopefully you will beable to see how this works, and how it can be changed to thingspeak or any other API.

General knowledge of APIs, and webhooks as well.
https://hologram.io/docs/reference
The Cloud Services Router (CSR), Embedded APIs, and REST API are all used in this demo.

[Wire it Up.](wire.md) 



