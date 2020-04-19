/*************************************************** 
  ARDUINOSAN 1.0
  For sensing bean temp and environmental temp and sending it to Artisan

  Slapped together by Austin Johnson (austinj@gmail.com)

  Code mostly adapted from:

  1. Lukeinator42 - https://github.com/lukeinator42/coffee-roaster
  2. This Adafruit library - https://github.com/adafruit/DHT-sensor-library
  3. And this Adafruit library -->
  
  This is a library for the Adafruit PT100/P1000 RTD Sensor w/MAX31865

  Designed specifically to work with the Adafruit RTD Sensor
  ----> https://www.adafruit.com/products/3328

  This sensor uses SPI to communicate, 4 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/


#include <Adafruit_MAX31865.h>
#include <ModbusRtu.h>



// data array for modbus network sharing
uint16_t au16data[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1 };
/**
 *  Modbus object declaration
 *  u8id : node id = 0 for master, = 1..247 for slave
 *  u8serno : serial port (use 0 for Serial)
 *  u8txenpin : 0 for RS-232 and USB-FTDI 
 *               or any pin number > 1 for RS-485
 */
Modbus slave; // this is slave @1 and RS-232 or USB-FTDI



// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

int ssr = 5;  


void setup() {
  thermo.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  pinMode(ssr, OUTPUT);
  slave = Modbus(1,0,0);
  slave.begin( 19200 ); // 19200 baud, 8-bits, even, 1-bit stop
  delay(5);
}

void loop() {
  
   au16data[2] = ((uint16_t) thermo.temperature(RNOMINAL, RREF));
   
   slave.poll( au16data, 16 );

   for(int i=1; i<=99; i++) {
    if(i<=au16data[4])
      digitalWrite(ssr, HIGH);
    else
      digitalWrite(ssr, LOW);
    
    delay(5);
   }
   
}
