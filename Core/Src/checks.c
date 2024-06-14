//
// Created by Malcolm Boyes on 2024-06-09.
//

#include "main.h"
#include "checks.h"


// return false when error
// TODO: rename to: Signals_Are_Plausible() or something like that.
bool Signal_Plausibility_Check(uint32_t *apps_Pedal_Position0, uint32_t *apps_Pedal_Position1) {
    // if the difference between signals is greater than 10% for more than 100ms, return false, otherwise return true
    static int start_time = 0;
    static int current_time = 0;

    if (abs(*apps_Pedal_Position0 - *apps_Pedal_Position1) > 10) {

        if (start_time == 0) { start_time = HAL_GetTick(); }

        current_time = HAL_GetTick();

        int time_diff = current_time - start_time;

        if (time_diff > LOOP_TIME_INTERVAL) {
            return false;
        }

    } else {
        start_time = 0;
    }

    return true;
}

// TODO: this isn't implemented properly yet. read the manual.
bool Brake_Pedal_Plausibility_Check(uint32_t *bps_Pedal_Position0) {

    // this function must:


}

// return true when the check passes
bool APPS_Brake_Pedal_Plausibility_Check(uint32_t *apps_Pedal_Position0, uint32_t *apps_Pedal_Position1, uint32_t *bps_Pedal_Position0) {
    // TODO: Add very small timer to this? to prevent car from entering this mode on small sensor mis-reading.
    return !((*apps_Pedal_Position0 > 25) && (*bps_Pedal_Position0 > BPS_PERCENT_THRESHOLD));
}


// return true when error
bool APPS_Out_Of_Range(uint32_t *appsVal0, uint32_t *appsVal1) {
    if (*appsVal0 < 0 || *appsVal0 > 4095 || *appsVal1 < 0 || *appsVal1 > 4095)
        return true;
    return false;
}

bool APPS_Are_Not_Connected(uint32_t *appsVal0, uint32_t *appsVal1){
    if (*appsVal0 <  APPS_DISCONNECTED || *appsVal1 < APPS_DISCONNECTED) { return true; }
    else { return false; }
}