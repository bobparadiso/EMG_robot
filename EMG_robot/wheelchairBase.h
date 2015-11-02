#ifndef __WHEELCHAIR_BASE_H_
#define __WHEELCHAIR_BASE_H_

#define DATA_PIN_REG PIND
#define DATA_DDR_REG DDRD
#define DATA_PORT_REG PORTD
#define DATA_PIN 2
#define BIT_WIDTH 26 //uS
#define DELAY_CMD 8 //ms

#define NUM_PACKETS 6
#define LEN_PACKET (3+8+1)
#define LEN_CMD (LEN_PACKET*NUM_PACKETS)

#define CMD_INIT   "11001001010111010110101111."

#define DRIVE_SPEED 4

extern char driveCmdBuf[LEN_CMD];

#endif
