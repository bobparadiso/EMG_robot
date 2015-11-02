// Digital pin #2 is the same as Pin D2 see
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping

// Using the Adafruit Motor Shield v2:
// http://www.adafruit.com/products/1438

#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include "EMG_robot.h"
#include "robotArm.h"
#include "wheelchairBase.h"

#define RX_TIMEOUT 250

#define SELECTION_SCAN_UPDATE_INTERVAL 1250

MODES mode = MODE_GROUP;
int selection = 0;

//TODO: watchdog?
//TODO: other safeties

// buffer sizes
#define maxTraceF 128

char trcBuf[maxTraceF];

// debug output
void tracef(const char *fmt, ... )
{
  va_list args;
  va_start (args, fmt );
  vsnprintf(trcBuf, maxTraceF, fmt, args);
  va_end (args);
  trace(trcBuf);
}

// debug output
void trace(const char *str)
{
  Serial.print(str);
}

//
uint8_t activated = 0; //is a motor/action in progress
void setup()
{
	//USB
	Serial.begin(9600);
	Serial.println("USB ready");
	
	//XBee
	//Serial1.begin(9600);
	//Serial1.println("XBee ready");

	setupArm();
	setupLEDs();
	setupWheelchairBase();

	//process commands
	uint32_t lastRx;
	while (1)
	{
		if (Serial.available())
		{    
			char rxData = Serial.read();
			lastRx = millis();

			switch (rxData)
			{
			case '0': break; //nothing to do
			
			case '1':
				if (!activated)
				{
					processSwitchActivation();
				}
				else
				{
					allOff();
					activated = 0;
				}
				break;
				
			default: allOff(); break;
			}
		}

		updateWheelchairBase();
		if (!activated)
			updateSelectionScan();
		updateLEDs();

		//cut everything
		if (millis() - lastRx > RX_TIMEOUT)
		{
			allOff();
			resetSelection();
		}
	}

	while (1) {}
}

//
void loop() {}

//
void allOff()
{
	driveOff();
	armOff();
}

//
void resetSelection()
{
	mode = MODE_GROUP;
	selection = 0;
}

//
void processSwitchActivation()
{
	switch (mode)
	{
	case MODE_GROUP:
		switch (selection)
		{
		case GROUP_BASE: mode = MODE_BASE; selection = 0; break;
		case GROUP_ARM1: mode = MODE_ARM1; selection = 0; break;
		case GROUP_ARM2: mode = MODE_ARM2; selection = 0; break;
		}
		break;
		
	case MODE_BASE:
		switch (selection)
		{
        case BASE_OPT_FORWARD: buildDriveCmd(driveCmdBuf, DRIVE_SPEED, 100, 0); activated = 1; break;
        case BASE_OPT_REVERSE: buildDriveCmd(driveCmdBuf, DRIVE_SPEED, -100, 0); activated = 1; break;
        case BASE_OPT_LEFT: buildDriveCmd(driveCmdBuf, DRIVE_SPEED, 0, -100); activated = 1; break;
        case BASE_OPT_RIGHT: buildDriveCmd(driveCmdBuf, DRIVE_SPEED, 0, 100); activated = 1; break;
        case MAX_BASE_OPTION: mode = MODE_GROUP; selection = 0; break;
		}
		break;
		
	case MODE_ARM1:
		switch (selection)
		{
        case ARM1_OPT_DOWN: armElevationMotor->setSpeed(ARM_ELEVATION_DOWN_SPEED); armElevationMotor->run(FORWARD); activated = 1; break;
        case ARM1_OPT_UP: armElevationMotor->setSpeed(ARM_ELEVATION_UP_SPEED); armElevationMotor->run(BACKWARD); activated = 1; break;
        case ARM1_OPT_LEFT: armTurnMotor->run(BACKWARD); activated = 1; break;
        case ARM1_OPT_RIGHT: armTurnMotor->run(FORWARD); activated = 1; break;
        case MAX_ARM1_OPTION: mode = MODE_GROUP; selection = 1; break;
        }
		break;
		
	case MODE_ARM2:
		switch (selection)
		{
        case ARM2_OPT_RETRACT: armReachMotor->run(FORWARD); activated = 1; break;
        case ARM2_OPT_EXTEND: armReachMotor->run(BACKWARD); activated = 1; break;
        case ARM2_OPT_CLOSE: armClawMotor->run(FORWARD); activated = 1; break;
        case ARM2_OPT_OPEN: armClawMotor->run(BACKWARD); activated = 1; break;
        case MAX_ARM2_OPTION: mode = MODE_GROUP; selection = 2; break;
        }
		break;
	}
}

//
void updateSelectionScan()
{
	static uint32_t lastUpdate = 0;
	if (millis() - lastUpdate < SELECTION_SCAN_UPDATE_INTERVAL)
		return;
			
	char max;
	switch (mode)
	{
	case MODE_GROUP: max = MAX_GROUP; break;
	case MODE_BASE: max = MAX_BASE_OPTION; break;
	case MODE_ARM1: max = MAX_ARM1_OPTION; break;
	case MODE_ARM2: max = MAX_ARM2_OPTION; break;
	}

	if (mode != MODE_GROUP)
		max++; //exit option

	selection = (selection + 1)	% max;
	lastUpdate = millis();
}
