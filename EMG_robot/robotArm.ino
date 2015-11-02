#include "robotArm.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *armReachMotor = AFMS.getMotor(ARM_REACH_MOTOR);
Adafruit_DCMotor *armElevationMotor = AFMS.getMotor(ARM_ELEVATION_MOTOR);
Adafruit_DCMotor *armTurnMotor = AFMS.getMotor(ARM_TURN_MOTOR);
Adafruit_DCMotor *armClawMotor = AFMS.getMotor(ARM_CLAW_MOTOR);

//
void setupArm()
{
	AFMS.begin();

	armReachMotor->run(RELEASE);
	armReachMotor->setSpeed(ARM_REACH_SPEED);
	armElevationMotor->run(RELEASE);
	armTurnMotor->run(RELEASE);
	armTurnMotor->setSpeed(ARM_TURN_SPEED);
	armClawMotor->run(RELEASE);
	armClawMotor->setSpeed(ARM_CLAW_SPEED);
}
 
//
void armOff()
{
	armReachMotor->run(RELEASE);
	armElevationMotor->run(RELEASE);
	armTurnMotor->run(RELEASE);
	armClawMotor->run(RELEASE);
}
