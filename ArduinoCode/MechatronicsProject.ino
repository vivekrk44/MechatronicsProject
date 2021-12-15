#include <SparkFun_SCD30_Arduino_Library.h>
#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial BTSerial(10, 11); // RX | TX
SCD30 airSensor;

uint8_t buff[50];

float co2, temp;

float co2_thr = 20000;
float temp_thr = 32;

void setup()
{
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  BTSerial.begin(9600);  // HC-05 default speed in AT command more
  Serial.println("Starting");
  Wire.begin();
  pinMode(2, INPUT_PULLUP);

  if (airSensor.begin() == false)
  {
    Serial.println("Air sensor not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }
  
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  // if (BTSerial.available())
  if (airSensor.dataAvailable())
  {
    Serial.print("co2(ppm):");
    co2 = airSensor.getCO2();
    Serial.print(co2);

    Serial.print(" temp(C):");
    temp = airSensor.getTemperature();
    Serial.print(temp, 1);

    Serial.print(" humidity(%):");
    Serial.print(airSensor.getHumidity(), 1);

    Serial.println();

    if(co2 > co2_thr)
    {
      BTSerial.print("CO2");
      Serial.print("CO2 High\n");
    }
    if(temp > temp_thr)
    {
      BTSerial.print("Temp");
      Serial.print("Temp High\n");
  
    }
    if(co2 < co2_thr && temp < temp_thr)
    {
      BTSerial.print("All Good");
      Serial.println("All Good");
    }
    BTSerial.println("");
  }
  if (false)
  {
    String start = BTSerial.readStringUntil('\n');
    Serial.println(start);
    if(start == "G")
    {
      String velStr = BTSerial.readStringUntil('\n');
      String omgStr = BTSerial.readStringUntil('\n');
      int vel = (int)velStr.toInt();
      int the = (int)omgStr.toInt();
      Serial.print("Got Velocity: ");
      Serial.print(vel, DEC);
      Serial.print(" Got Theta: ");
      Serial.println(the, DEC);
      
    }
  }

  if(!digitalRead(2))
  {
    BTSerial.print("Button");
    Serial.println("Button was pressed");
    delay(1000);
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());
}
