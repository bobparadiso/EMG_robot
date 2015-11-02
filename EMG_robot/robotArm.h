#ifndef __ROBOT_ARM_H_
#define __ROBOT_ARM_H_

#define ARM_TURN_MOTOR 1
#define ARM_ELEVATION_MOTOR 2
#define ARM_REACH_MOTOR 3
#define ARM_CLAW_MOTOR 4

#define ARM_CLAW_SPEED 32
#define ARM_TURN_SPEED 32
#define ARM_ELEVATION_DOWN_SPEED 32
#define ARM_ELEVATION_UP_SPEED 140
#define ARM_REACH_SPEED 64

extern Adafruit_DCMotor *armReachMotor;
extern Adafruit_DCMotor *armElevationMotor;
extern Adafruit_DCMotor *armTurnMotor;
extern Adafruit_DCMotor *armClawMotor;

#endif
