//
// Created by Malcolm Boyes on 2024-06-11.
//

#include "main.h"
#include "utils.h"
#include "states.h"

void enable_motor_movement() {
    HAL_GPIO_WritePin(Drive_Enable_Output_GPIO_Port, Drive_Enable_Output_Pin, GPIO_PIN_SET);
}

void disable_motor_movement() {
    value_to_inverter = 0;
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);
    HAL_GPIO_WritePin(Drive_Enable_Output_GPIO_Port, Drive_Enable_Output_Pin, GPIO_PIN_RESET);
}

void enable_dac_channel_1(){
    DAC1->CR |= 1;
}

// this function takes the values from APPS and BSE and turns into a single signal that is output to DAC to control the motor speeds
void set_value_to_inverter(uint32_t apps_PP[], uint32_t bpsVal[]){
    value_to_inverter = generate_value_for_inverter(apps_PP, bpsVal);
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value_to_inverter);
    return;
}

uint32_t generate_value_for_inverter(uint32_t apps_PP[], uint32_t bpsVal[]) {
    uint32_t inv_val = apps_Pedal_Position[0] * (((1 << 12) - 1) / 100);  // this just multiplies the pedal position percentage by 4095 / 100
    //    uint32_t inv_val = (uint32_t)(adjusted_input_val) * (((1 << 12) - 1) / (APPS_0_MAX - APPS_0_MIN)); // TODO: This is a ghetto function that will actually need to be made proper
    // TODO: need to average values coming from pedal for this. also need to use both pedal values somehow.
    // I have averaged the pedal values
    // TODO: inv_val must be prevented from being a negative value
    // this value has a max of 4095 and lower bound of 0
    // TODO: create the function that maps these inputs to the motor speed. implementing this function will be based on trying different things out.
    // check this value is between bounds of MIN_DAC_VAL and MAX_DAC_VAL
    return inv_val;
}



#define BUFFER_SIZE 7

int apps1_buffer[BUFFER_SIZE] = {0};
int apps2_buffer[BUFFER_SIZE] = {0};
int bps_buffer[BUFFER_SIZE] = {0};

int apps1_index = 0;
int apps2_index = 0;
int bps_index = 0;

int apps1_count = 0;
int apps2_count = 0;
int bps_count = 0;


void add_to_buffer(int buffer[], int *index, int *count, int new_value) {
    buffer[*index] = new_value;
    *index = (*index + 1) % BUFFER_SIZE;
    if (*count < BUFFER_SIZE) {
        (*count)++;
    }
}

int calculate_average(const int buffer[], int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += buffer[i];
    }

    if (count == 0) return 0; // Prevent division by zero
    return sum / count;
}

void monitor_Signals(void) {

    // TODO: configure this to be a DMA function instead of working eating CPU cycles

#ifdef DEBUG

#ifdef TESTING
    sprintf(msg, "Test mode enabled?: YES\n");
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);
#endif

#ifndef TESTING
    sprintf(msg, "Test mode enabled?: NO\n");
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);
#endif

    sprintf(msg, "TS Active: %d\n", !HAL_GPIO_ReadPin(HV_Present_GPIO_Port, HV_Present_Pin));
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

    sprintf(msg, "Current state: %d\n", current_State);
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

    sprintf(msg, "Raw accelerator inputs: %d %d\n", appsVal[0], appsVal[1]);
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

    sprintf(msg, "Processed accelerator inputs: %d %d\n", apps_Pedal_Position[0], apps_Pedal_Position[1]);
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

    sprintf(msg, "Raw brake input: %d\n", bpsVal[0]);
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

    sprintf(msg, "Processed brake input: %d\n", bps_Pedal_Position[0]);
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

    sprintf(msg, "Output to inverter: %d\n\n\n", value_to_inverter);
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

    // also print: whether drive enable GPIO pin is on or off

#endif


} //end monitor_Signals()
