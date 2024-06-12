//
// Created by Malcolm Boyes on 2024-06-12.
//

#ifndef TM23_VCU_FIRMWARE_SIGNALS_H
#define TM23_VCU_FIRMWARE_SIGNALS_H

#include "main.h"

void BPSMapEncoderValueToPositionPercentage(uint32_t *bpsVal, uint32_t bps_PP[]);
void APPSMapEncoderValueToPositionPercentage(uint32_t *appsVal0, uint32_t *appsVal1, uint32_t apps_PP[]);


#endif //TM23_VCU_FIRMWARE_SIGNALS_H
