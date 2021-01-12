#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <bsec.h>

#include "main.hpp"
#include "secret.hpp"
#include "SensorReceiver.h"

/* in minutes */
#define REPORT_INTERVAL (5)
#define MAX_RETRIES (3)
constexpr char TABLE[] = "viva_test";

Bsec bme;
unsigned long lastReport = 0;

float tempOut;
byte humOut;

float tempIn;
float humIn;
float presIn;

float iaq;
float resistance;
float co2;
float voc;
uint8_t acc;

void blink()
{
  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(50); // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);
}

void initVars()
{
  tempOut = NAN;
  humOut = 0xFF;

  tempIn = NAN;
  humIn = NAN;
  presIn = NAN;

  iaq = NAN;
  resistance = NAN;
  voc = NAN;
  co2 = NAN;
}

void read433(byte *data)
{
  // is data a ThermoHygro-device?
  if ((data[3] & 0x1f) == 0x1e)
  {
    // Yes!

    byte channel, randomId;
    int temp;
    byte humidity;

    // Decode the data
    SensorReceiver::decodeThermoHygro(data, channel, randomId, temp, humidity);

    tempOut = (temp / 10) + ((temp % 10) / 10.);
    humOut = humidity;
  }
}

void enable433()
{
  SensorReceiver::init(digitalPinToInterrupt(14), read433);
}

void disable433()
{
  detachInterrupt(digitalPinToInterrupt(14));
}

void readBme()
{
  if (bme.run())
  {
    tempIn = bme.temperature;
    humIn = bme.humidity;
    presIn = bme.pressure;

    iaq = bme.staticIaq;
    resistance = bme.gasResistance;
    voc = bme.breathVocEquivalent;
    co2 = bme.co2Equivalent;
    acc = bme.staticIaqAccuracy;

    Serial.println(acc);
    Serial.println(iaq);
    Serial.println(humOut);

    const unsigned long ms = millis();

    if (acc == 0)
    {
      lastReport = ms;
    }
    else if (ms - lastReport >= REPORT_INTERVAL * 60 * 1000)
    {
      report();
    }
  }
  else
  {
    checkBmeStatus();
  }
}

void setup()
{
  initVars();
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200);
  Wire.begin();

  bme.begin(BME680_I2C_ADDR_SECONDARY, Wire);
  checkBmeStatus();

  bsec_virtual_sensor_t sensorList[10] = {
      BSEC_OUTPUT_RAW_TEMPERATURE,
      BSEC_OUTPUT_RAW_PRESSURE,
      BSEC_OUTPUT_RAW_HUMIDITY,
      BSEC_OUTPUT_RAW_GAS,
      BSEC_OUTPUT_IAQ,
      BSEC_OUTPUT_STATIC_IAQ,
      BSEC_OUTPUT_CO2_EQUIVALENT,
      BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
  };

  bme.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
  checkBmeStatus();

  enable433();
}

void loop()
{
  readBme();
}

void report()
{
  disable433();

  IPAddress ip(192, 168, 168, 4);
  IPAddress gw(192, 168, 168, 1);
  IPAddress subnet(255, 255, 255, 224);

  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gw, subnet);
  WiFi.begin(MYSSID, MYPASS);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  String data(TABLE);

  if (!isnan(tempIn))
  {
    data += " tIn=";
    data += tempIn;
    data += ",pIn=";
    data += presIn;

    data += ",humIn=";
    data += humIn;

    data += ",iaq=";
    data += iaq;
    data += ",res=";
    data += resistance;
    data += ",co2=";
    data += co2;
    data += ",voc=";
    data += voc;
    data += ",acc=";
    data += acc;
  }

  if (!isnan(tempOut))
  {
    if (data.length() > 6)
    {
      data += ",";
    }
    else
    {
      data += " ";
    }

    data += "tOut=";
    data += tempOut;
    data += ",humOut=";
    data += humOut;
  }

  Serial.println(data);

  if (data.length() > 6)
  {
    for (int i = 0; i < MAX_RETRIES; i++)
    {
      HTTPClient http; //Declare object of class HTTPClient
      String url = "http://37.205.8.10:50517/write?db=mydb&u=esp&p=";
      url += DB_PASS;
      http.begin(url);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      int httpCode = http.POST(data);    //Send the request
      String payload = http.getString(); //Get the response payload
      http.end();                        //Close connection

      Serial.println(httpCode); //Print HTTP return code
      Serial.println(payload);  //Print request response payload

      if (httpCode == HTTP_CODE_NO_CONTENT)
      {
        blink();
        lastReport = millis();
        break;
      }
      else
      {
        Serial.println("Unable to send data, retrying in 5s...");
        delay(5000);
      }
    }
  }

  initVars();
  WiFi.disconnect();
  Serial.print("Disconnecting");
  do
  {
    delay(500);
    Serial.print(".");
  } while (WiFi.status() == WL_CONNECTED);

  enable433();
}

void checkBmeStatus()
{
  String output;
  if (bme.status != BSEC_OK)
  {
    if (bme.status < BSEC_OK)
    {
      output = "BSEC error code : " + String(bme.status);
      Serial.println(output);
      for (;;)
        blink(); /* Halt in case of failure */
    }
    else
    {
      output = "BSEC warning code : " + String(bme.status);
      Serial.println(output);
    }
  }

  if (bme.bme680Status != BME680_OK)
  {
    if (bme.bme680Status < BME680_OK)
    {
      output = "BME680 error code : " + String(bme.bme680Status);
      Serial.println(output);
      for (;;)
        blink(); /* Halt in case of failure */
    }
    else
    {
      output = "BME680 warning code : " + String(bme.bme680Status);
      Serial.println(output);
    }
  }
}
