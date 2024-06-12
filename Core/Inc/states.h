//
// Created by Malcolm Boyes on 2024-06-09.
//

#ifndef TM23_VCU_FIRMWARE_STATES_H
#define TM23_VCU_FIRMWARE_STATES_H


typedef enum {
    STANDBY_STATE, RUNNING_STATE, BSPD_TRIP_STATE, ERROR_STATE, UNDEFINED_STATE
} STATEVAR;

enum {
    ERR_NONE = 0b00000000,
    ERR_NO_BRAKE_SENSOR = 0b00000001,
    ERR_NO_THROTTLE_SENSOR = 0b00000010,
    ERR_STATE_UNDEFINED = 0b10000000,
};

//FSM Definitions
extern STATEVAR current_State;
extern STATEVAR last_State;
extern uint8_t errorCode;

void standby_State(void);
void running_State(void);
void BSPD_Trip_State(void);
void error_State(void);

#endif //TM23_VCU_FIRMWARE_STATES_H
