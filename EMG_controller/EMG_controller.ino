#include "SoftwareSerial.h"

#define SENSOR_PIN A0

#define THRESHOLD_ON 850
#define THRESHOLD_OFF 500

#define LOOP_INTERVAL 10
#define MIN_CHANGE_TIME 1000

SoftwareSerial XBee(2,3);

//
long lastChange = 0;
void setup()
{
	Serial.begin(9600);
	XBee.begin(9600);

	int active = 0;
	while (1)
	{
		long elapsed = millis() - lastChange;
		
		int sensorValue = analogRead(SENSOR_PIN);

		// print the results to the serial monitor:
		Serial.print("sensor = " );
		Serial.println(sensorValue);
		
		if (sensorValue > THRESHOLD_ON && !active && elapsed > MIN_CHANGE_TIME)
		{
			Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			XBee.write('1');
			active = 1;
			lastChange = millis();
		}
		else if (sensorValue < THRESHOLD_OFF && active && elapsed > MIN_CHANGE_TIME)
		{
			XBee.write('0');
			active = 0;
			lastChange = millis();
		}
		else
		{
			XBee.write('0');
		}
			
		//delay to throttle XBee transmissions and allow ADC to recover
		delay(LOOP_INTERVAL);
	}
}

//
void loop() {}
