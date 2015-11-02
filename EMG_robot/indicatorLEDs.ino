#include <Adafruit_NeoPixel.h>

#define STRIP_LEN 28
#define BAND_LEN 10
#define BASE_STRIP_PIN 5
#define ARM1_STRIP_PIN 6
#define ARM2_STRIP_PIN 7

Adafruit_NeoPixel baseStrip = Adafruit_NeoPixel(STRIP_LEN, BASE_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel arm1Strip = Adafruit_NeoPixel(STRIP_LEN, ARM1_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel arm2Strip = Adafruit_NeoPixel(STRIP_LEN, ARM2_STRIP_PIN, NEO_GRB + NEO_KHZ800);

#define BRIGHTNESS 64
//#define BRIGHTNESS 8
       
uint32_t white = Adafruit_NeoPixel::Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS);
uint32_t red = Adafruit_NeoPixel::Color(BRIGHTNESS, 0, 0);
uint32_t green = Adafruit_NeoPixel::Color(0, BRIGHTNESS, 0);
uint32_t blue = Adafruit_NeoPixel::Color(0, 0, BRIGHTNESS);
uint32_t magenta = Adafruit_NeoPixel::Color(BRIGHTNESS, 0, BRIGHTNESS);
uint32_t cyan = Adafruit_NeoPixel::Color(0, BRIGHTNESS, BRIGHTNESS);
uint32_t yellow = Adafruit_NeoPixel::Color(BRIGHTNESS, BRIGHTNESS, 0);

#include "EMG_robot.h"

const int8_t baseLEDs[] = {24, 10, 3, 17};
const int8_t arm1LEDs[] = {24, 10, 3, 17}; 
const int8_t arm2LEDs[] = {24, 10, 3, 17}; 

const uint32_t selectionColors[] = {green, red, cyan, magenta};

//
void setupLEDs()
{
	//start all LEDs off
	baseStrip.begin();
	baseStrip.show();
	
	arm1Strip.begin();
	arm1Strip.show();
	
	arm2Strip.begin();
	arm2Strip.show();
}

//
int lastMode = -1;
int lastSelection = -1;
void updateLEDs()
{
	//tracef("updateLEDs; mode:%d selection:%d\r\n", mode, selection);
	
	if (mode == lastMode && selection == lastSelection)
		return; //nothing to do

	//clear
	for (uint8_t i = 0; i < STRIP_LEN; i++)
	{
		baseStrip.setPixelColor(i, 0, 0, 0);
		arm1Strip.setPixelColor(i, 0, 0, 0);
		arm2Strip.setPixelColor(i, 0, 0, 0);
	}

	switch (mode)
	{
	case MODE_GROUP:
		switch (selection)
		{
		case GROUP_BASE:
			for (uint8_t i = 0; i < STRIP_LEN; i++)
				baseStrip.setPixelColor(i, white);
			break;
		case GROUP_ARM1:
			for (uint8_t i = 0; i < STRIP_LEN; i++)
				arm1Strip.setPixelColor(i, white);
			break;
		case GROUP_ARM2:
			for (uint8_t i = 0; i < STRIP_LEN; i++)
				arm2Strip.setPixelColor(i, white);
			break;
		}
		break;
		
	case MODE_BASE:
		if (selection != MAX_BASE_OPTION)
		{
			for (uint8_t i = 0; i < BAND_LEN; i++)
				baseStrip.setPixelColor((baseLEDs[selection] + i) % STRIP_LEN, selectionColors[selection]);
		}
		else
		{
			for (uint8_t i = 0; i < STRIP_LEN; i++)
				baseStrip.setPixelColor(i, yellow);
		}
		break;
		
	case MODE_ARM1:
		if (selection != MAX_ARM1_OPTION)
		{
			for (uint8_t i = 0; i < BAND_LEN; i++)
				arm1Strip.setPixelColor((arm1LEDs[selection] + i) % STRIP_LEN, selectionColors[selection]);
		}
		else
		{
			for (uint8_t i = 0; i < STRIP_LEN; i++)
				arm1Strip.setPixelColor(i, yellow);
		}
		break;
		
	case MODE_ARM2:
		if (selection != MAX_ARM2_OPTION)
		{
			for (uint8_t i = 0; i < BAND_LEN; i++)
				arm2Strip.setPixelColor((arm2LEDs[selection] + i) % STRIP_LEN, selectionColors[selection]);
		}
		else
		{
			for (uint8_t i = 0; i < STRIP_LEN; i++)
				arm2Strip.setPixelColor(i, yellow);
		}
		break;
	}

	baseStrip.show();
	arm1Strip.show();
	arm2Strip.show();
	
	lastMode = mode;
	lastSelection = selection;
}
