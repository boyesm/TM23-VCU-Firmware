//
// Created by Malcolm Boyes on 2024-06-11.
//

#ifndef TM23_VCU_FIRMWARE_UTILS_H
#define TM23_VCU_FIRMWARE_UTILS_H

void disable_motor_movement();
void enable_motor_movement();
void enable_dac_channel_1();
void set_value_to_inverter(uint32_t apps_PP[], uint32_t bpsVal[]);
uint32_t generate_value_for_inverter(uint32_t apps_PP[], uint32_t bpsVal[]);
void add_to_buffer(int buffer[], int *index, int *count, int new_value);
int calculate_average(const int buffer[], int count);
void monitor_Signals(void);

#endif //TM23_VCU_FIRMWARE_UTILS_H
