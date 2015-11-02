#ifndef __EMG_ROBOT_H_
#define __EMG_ROBOT_H_

enum MODES {MODE_GROUP, MODE_BASE, MODE_ARM1, MODE_ARM2, MAX_MODE};
enum GROUPS {GROUP_BASE, GROUP_ARM1, GROUP_ARM2, MAX_GROUP};
enum BASE_OPTIONS {BASE_OPT_FORWARD, BASE_OPT_REVERSE, BASE_OPT_RIGHT, BASE_OPT_LEFT, MAX_BASE_OPTION};
enum ARM1_OPTIONS {ARM1_OPT_DOWN, ARM1_OPT_UP, ARM1_OPT_RIGHT, ARM1_OPT_LEFT, MAX_ARM1_OPTION};
enum ARM2_OPTIONS {ARM2_OPT_EXTEND, ARM2_OPT_RETRACT, ARM2_OPT_OPEN, ARM2_OPT_CLOSE, MAX_ARM2_OPTION};

#endif