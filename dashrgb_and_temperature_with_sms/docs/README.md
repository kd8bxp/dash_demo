# Demo Of Hologram.io Dash Cell Device

based on the RGBleds sketch 
https://github.com/hologram-io/hologram-dash-arduino-examples/blob/master/rgbleds/rgbleds.ino

and a Temperature sketch found in the hologram community.
https://community.hologram.io/t/recommended-temperature-sensor-tutorials/446

This sketch waits for a SMS message of a color or the word "temperature".
It also has a "Party" and "Blink" mode (Thou, I am not sure blink works)
If you text your device a color it knows, it will change (fade) the LED to that color.  IF you text it the word "temperature" it will send back a NEWTIFRY message with the temperature.

You will need to setup a webhook with your newtifry information.

I also setup a website, that uses the hologram SMS api. This is nothing more than a couple of simple PHP scripts running on C9.io - but the way I made them they could turn into a easier to use api for other apps to send colors/temperature to your device.
https://c9.io/kd8bxp/dashsms

## Installation

Documentation is coming soon.
 

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request

## Credits

Hologram.io team (Ryan and Reuben) 
Community user torchris for asking questions on how to make thingspeak work -
even thou I'm not using thingspeak, it was thanks to his question I was able to figure out what needed to be done for my sketch.
(https://community.hologram.io/t/webhooks-examples/225/3) 
LeRoy Miller 2017

## License

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses
