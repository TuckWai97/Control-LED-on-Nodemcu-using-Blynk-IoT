/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN            ""

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
// Please put your wifi name in the quotation marks for char ssid
// Please put your wifi password in the char pass's quotation marks
char ssid[] = "";
char pass[] = "";
//static const uint8_t D4=2;


BlynkTimer timer;
// connect pin A0 of nodemcu with 10k potentiometer
#define POT A0
bool eventTrigger = false;
// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  int invtvalue = !value;
  // Update state
  Blynk.virtualWrite(V2, invtvalue);
  
  //Serial.println("V0 value: "+ String(value));
  //digitalWrite(LED_BUILTIN, value);
  digitalWrite(D0,value);
}

BLYNK_WRITE(V3)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V3, value);
  
  //Serial.println("V0 value: "+ String(value));
  //digitalWrite(LED_BUILTIN, value);
  digitalWrite(D4,value);
}


 
// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more than 10 values per second.
  int pot_adc = analogRead(POT);
  
 
  Serial.println("Potentiometer ADC: "+ String(pot_adc));
 
  Blynk.virtualWrite(V1, pot_adc);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  
  if(pot_adc < 100 &&
     eventTrigger == false) {
      eventTrigger = true;
  //Set a flag variable to prevent it from send notifications repeatedly
      Blynk.logEvent("LIGHT", "Light ADC is less than 100");
     }
     else if (pot_adc > 300) {
      eventTrigger = false;
     }
  
}

void setup()
{
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(POT, INPUT); 

  //digitalWrite(LED_BUILTIN, value);
  // Debug console
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
 
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();

  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
