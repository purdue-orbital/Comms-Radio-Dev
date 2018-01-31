 /* SENSOR PIN DOCUMENTATION:-
 * 
 * GPS Waveshare Sensor:
 * VCC - 5V
 * GND - GND
 * TX  - 3 (refered to as RX of Arduino)
 * RX  - 4 (refered to as TX of Arduino)
 * 
 * SD Breakout:
 * 5V  - 5V
 * GND - GND
 * CLK - 13
 * DO  - 12
 * DI  - 11
 * CS  - 10
 * 
 * Igniter:
 * input - 5
 * 
 * LED:
 * 
 */
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include <SPI.h>
#include <SD.h>

const int ignitionPIN = 5;
const int gpsRX = 3;
const int gpsTX = 4;
const int chipSelect = 10;

SoftwareSerial serial_connection(gpsRX, gpsTX); //RX=pin 3, TX=pin 4
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data

void setup()
{
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
  pinMode(ignitionPIN, OUTPUT);
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) // see if the card is present and can be initialized:
  {
    Serial.println("Card failed, or not present");
    return;// don't do anything more
  }
  Serial.println("card initialized.");

  File dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) // if the file is available, write to it
  {
    dataFile.println("Satellite Count,Latitude,Longitude,Speed (MPH),Altitude (Feet), Time (ms),");
    dataFile.close();
  }
  else // if the file isn't open, pop up an error:
  {
    Serial.println("error opening data.csv");
    return;// don't do anything more
  }
  serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
}

void loop()
{  
  while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  
  if(gps.location.isUpdated())
  {
    double altitude = gps.altitude.feet();
    File dataFile = SD.open("data.csv", FILE_WRITE);

    // WRITING TO FILE ON SD CARD
    if (dataFile) 
    {
      dataFile.print(gps.satellites.value());
      dataFile.print(", ");
      dataFile.print(gps.location.lat(), 6);
      dataFile.print(", ");
      dataFile.print(gps.location.lng(), 6);
      dataFile.print(", ");
      dataFile.print(gps.speed.mph());
      dataFile.print(", ");
      dataFile.print(gps.altitude.feet());
      dataFile.print(",");
      dataFile.print(millis());
      dataFile.println(",");
      dataFile.close();
    }
    else 
    {
      Serial.println("error opening data.csv");
    }

    //PRINTING TO SERIAL
    Serial.print(gps.satellites.value());
    Serial.print(", ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(", ");
    Serial.print(gps.location.lng(), 6);
    Serial.print(", ");
    Serial.print(gps.speed.mph());
    Serial.print(", ");
    Serial.print(gps.altitude.feet());
    Serial.print(",");
    Serial.print(millis());
    Serial.println(",");

    if(altitude >= 0.1 && millis()>=60000)//ignition after altitue of 10000ft and 20 mins after start time
    {
      //digitalWrite(ignitionPIN,HIGH);
      Serial.println("");
      Serial.println("IGNITION!!!");
      Serial.println("");
    }
    //Serial.print("Altitude: ");
    //Serial.println(altitude);
  }
}
