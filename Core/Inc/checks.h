//
// Created by Malcolm Boyes on 2024-06-09.
//

#ifndef TM23_VCU_FIRMWARE_CHECKS_H
#define TM23_VCU_FIRMWARE_CHECKS_H

#include "main.h"

// TODO: verify that these functions work with the new method of passing parameters to them instead of accessing global variables!
bool Signal_Plausibility_Check(uint32_t *apps_Pedal_Position0, uint32_t *apps_Pedal_Position1);
bool Brake_Pedal_Plausibility_Check(uint32_t *bps_Pedal_Position0);
bool APPS_Brake_Pedal_Plausibility_Check(uint32_t *apps_Pedal_Position0, uint32_t *apps_Pedal_Position1, uint32_t *bps_Pedal_Position0);
bool APPS_Out_Of_Range(uint32_t *appsVal0, uint32_t *appsVal1);
bool APPS_Are_Not_Connected(uint32_t *appsVal0, uint32_t *appsVal1);

#endif //TM23_VCU_FIRMWARE_CHECKS_H
