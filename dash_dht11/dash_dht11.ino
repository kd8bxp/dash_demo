/* Test code for DHT 11 Temperature Module w/ Hologram Dash
  * Modified by Hologram for the Hologram Dash
  * This is based off of the Adafruit Arduino DHT example at:
  * https://github.com/adafruit/DHT-sensor-library/tree/master/examples/DHTtester
  * This modified Hologram version sends the humidity, temperature 
  * data back to the Hologram cloud
  * 
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  * 
  */
#include <DHT.h>
#define Serial SerialUSB
#define DHTPIN R04     // DHT Sensor output pin connected to Dash GPIO
#define DHTTYPE DHT11   // DHT 11
//Change this to change how often the DHT11 data is printed and sent to the cloud
#define DASH_SERIAL_SEND_TIME 10000 // in ms
#define DASH_CLOUD_SEND_TIME 3000000 // in ms
#define LED_DATA_INDICATOR_DURATION 200
#define LED_DATA_INDICATOR_FLICKER_OFF_DURATION 50
#define LED_DATA_INDICATOR_FLICKER_ON_DURATION 5
// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
/* globals */
unsigned ledStartMillis;
unsigned ledNextFlickerMillis;
bool uplinkDataDetected;
bool downlinkDataDetected;
bool ledOn;
uint32_t nextDHTSerialOutput;
uint32_t nextDHTCloudOutput;
unsigned lastMillis;
void setup()  
{
    Dash.begin();
    dht.begin();
    Serial2.begin(9600);
    SerialUSB.begin(9600);
    SerialUSB.println("Hologram DHT Sketch");
    SerialCloud.begin(115200);
    ledStartMillis = 0; /* LED off by default */  
ledNextFlickerMillis = 0;
uplinkDataDetected = false;
downlinkDataDetected = false;
ledOn = false;
ledIndicateData();

nextDHTSerialOutput = 0;
nextDHTCloudOutput = 0;

delay(1000);
lastMillis = millis();
SerialCloud.println("Init");
}
void loop() {
  // open Dash Serial Gateway for Serial Cloud and Modem Debugging Output
  dashSerialGateway();
  // print out the current stats and send to cloud
    if (nextDHTSerialOutput < millis()) {
        nextDHTSerialOutput = millis() + DASH_SERIAL_SEND_TIME; // reset the timer
        dhtPrint(); // Print serial reading of DHT reading
 
}
if (nextDHTCloudOutput < millis()) {
    nextDHTCloudOutput = millis() + DASH_CLOUD_SEND_TIME; // reset the timer

    SerialCloud.println(dhtJSON()); // Send JSON DHT data to Hologram Cloud

}

if (lastMillis > millis()) {
   nextDHTSerialOutput = millis();
   nextDHTCloudOutput = millis();
   lastMillis = millis();
}
lastMillis = millis();
}
void dashSerialGateway() {
  char currChar;
  if(ledOn) {
    Dash.onLED();
  } else {
    Dash.offLED();
  }
  if (uplinkDataDetected) {
    /* for uplink data, we turn on LED for duration */
    ledOn=true;
    if(millis() > (ledStartMillis + LED_DATA_INDICATOR_DURATION)) {
      uplinkDataDetected=false;
      ledOn=false;
    }
  }
  if (!uplinkDataDetected && downlinkDataDetected) {
    /* for downlink data, we flash LED for duration */
    if(millis() > ledNextFlickerMillis) {
      if(ledOn) {
        ledOn=false;
        ledNextFlickerMillis = millis() + LED_DATA_INDICATOR_FLICKER_OFF_DURATION;
      } else {
        ledOn=true;
        ledNextFlickerMillis = millis() + LED_DATA_INDICATOR_FLICKER_ON_DURATION;
      }
    }
    if(millis() > (ledStartMillis + LED_DATA_INDICATOR_DURATION)) {
      downlinkDataDetected=false;
      ledOn=false;
    }
  }
  while(Serial2.available()) {
    SerialCloud.write(Serial2.read());
    uplinkDataDetected=true;
    ledIndicateData();
  }
  while(SerialUSB.available()) {
    SerialCloud.write(SerialUSB.read());
    uplinkDataDetected=true;
    ledIndicateData();
  }
  while(SerialCloud.available()) {
    currChar = (char)SerialCloud.read();
    SerialUSB.write(currChar);
    Serial2.write(currChar);
    downlinkDataDetected=true;
    ledNextFlickerMillis = millis() + LED_DATA_INDICATOR_FLICKER_ON_DURATION;
    ledIndicateData();
  }
}
void ledIndicateData() {
  ledStartMillis=millis();
  ledOn=true;
}
void dhtPrint() {
  Serial.print("Humidity: ");
  Serial.print(dht.readHumidity());
  Serial.println(" %\t");
  Serial.println("Temperature: ");
  Serial.print(dht.readTemperature());
  Serial.print(" *C ");
  Serial.print(dht.readTemperature(true));
  Serial.println(" *F\t");
}
String dhtJSON() {
  char buf[8];
  dtostrf(dht.readTemperature(true),4,2,buf);
  String ret = "{\"temp\":";
  ret.concat(buf);
  ret.concat(", ");
  dtostrf(dht.readHumidity(),4,2,buf);
  ret.concat("\"humidity\":");
  ret.concat(buf);
  
  ret.concat("}");
  Serial.println(ret);
  return ret;
}
