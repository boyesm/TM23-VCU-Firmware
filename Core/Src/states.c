//
// Created by Malcolm Boyes on 2024-06-09.
//
#include "main.h"
#include "states.h"
#include "utils.h"
#include "checks.h"

STATEVAR current_State = STANDBY_STATE;
STATEVAR last_State = UNDEFINED_STATE;
uint8_t errorCode = ERR_NONE;

//// State Functions
void standby_State(void) {
    if (last_State != STANDBY_STATE) {
        last_State = STANDBY_STATE;
        disable_motor_movement();
    }
    //checking if brakes are pressed, start button is pressed and HV Present at the same time
    // TODO: test HV present feature.

    //if ((bps_Pedal_Position[0] >= 50) && (!HAL_GPIO_ReadPin(Start_Button_GPIO_Port, Start_Button_Pin)) && HAL_GPIO_ReadPin(HV_Present_GPIO_Port, HV_Present_Pin)) {
    if ((bps_Pedal_Position[0] >= 50) && (!HAL_GPIO_ReadPin(Start_Button_GPIO_Port, Start_Button_Pin))) {
        //sound buzzer (and enable green on-board LED) for minimum of 1 second and maximum of 3 seconds using timer
        HAL_GPIO_WritePin(Ready_to_Drive_Sound_GPIO_Port, Ready_to_Drive_Sound_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
        HAL_Delay(2000); //sound buzzer for 2 seconds
        HAL_GPIO_WritePin(Ready_to_Drive_Sound_GPIO_Port, Ready_to_Drive_Sound_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

        sprintf(msg, "Ready to Drive Enabled...\n");
        HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

        // change the current state to RUNNING_STATE
        current_State = RUNNING_STATE;

    } //end if

} //end standby_State()

void running_State(void) {

    // TODO: rename these conditions at the beginning of each state to a function called on_Enter_Running_State, or something similar...
    if (last_State != RUNNING_STATE) {
        last_State = RUNNING_STATE;

        enable_motor_movement();

        sprintf(msg, "Running State...\n");
        HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);
    } //end if


    // check for errors here.
    // TODO: these error checks don't work.
    if (APPS_Out_Of_Range(&appsVal[0], &appsVal[1])) {
        current_State = ERROR_STATE;
        return;
    }

//    if (!Signal_Plausibility_Check()) {
//        current_State = ERROR_STATE;
//        return;
//    }

    if (!APPS_Brake_Pedal_Plausibility_Check(&apps_Pedal_Position[0], &apps_Pedal_Position[1], &bps_Pedal_Position[0])) {
        current_State = BSPD_TRIP_STATE;
        return;
    } //end if

    // if estop is pressed, return to standby mode
    if (!HAL_GPIO_ReadPin(HV_Present_GPIO_Port, HV_Present_Pin)){
        current_State = STANDBY_STATE;
        return;
    }

    // send pedal percentage to DAC here and output to inverters.
    set_value_to_inverter(&appsVal, &bpsVal);

} //end running()

void BSPD_Trip_State(void) {

    if (last_State != BSPD_TRIP_STATE) {

        last_State = BSPD_TRIP_STATE;

        disable_motor_movement();

        sprintf(msg, "BSPD Trip State...\n");
        HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

    } //end if

    // Send CAN message to notify in BSPD trip state

    // Stay in BSPD_Trip_State until accel pedal is less than 5%. brake pedal is don't care.
    if (apps_Pedal_Position[0] < 5) {
        current_State = RUNNING_STATE;
    } //end if

} //end BSPD_Trip_State()

void error_State(void) {

    // Should get here if throttle or brake sensor are out of range

    // Turn Drive Enable OFF

    // todo: why is this happening for each run of this loop?
    HAL_GPIO_WritePin(Drive_Enable_Output_GPIO_Port, Drive_Enable_Output_Pin, GPIO_PIN_RESET);

    if (last_State != ERROR_STATE) {
        last_State = ERROR_STATE;

        sprintf(msg, "Error State...\n");
        HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

        // Display errors over Serial
        // TODO: Also Send CAN message to notify in error state

        if (errorCode == ERR_NONE) {
            sprintf(msg, "   *Error state, but no error code logged...");
            HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);
        }
        if (errorCode & ERR_NO_BRAKE_SENSOR) {
            sprintf(msg, "   *Error state, No brake sensor detected");
            HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);
        }
        if (errorCode & ERR_NO_THROTTLE_SENSOR) {
            sprintf(msg, "   *Error state, No throttle sensor detected");
            HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);
        }
        if (errorCode & ERR_STATE_UNDEFINED) {
            sprintf(msg, "   *State not defined in The State Machine.");
            HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);
        }

    } //end if

    // TODO: test this feature. also check for no movement
    // when ignition button is pressed in error state, return back to standby state
    if (!HAL_GPIO_ReadPin(Start_Button_GPIO_Port, Start_Button_Pin)) {
        current_State = STANDBY_STATE;
    }

} //end errorState()
