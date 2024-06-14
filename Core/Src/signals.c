//
// Created by Malcolm Boyes on 2024-06-12.
//

#include "main.h"
#include "signals.h"

void APPSMapEncoderValueToPositionPercentage(uint32_t *appsVal0, uint32_t *appsVal1, uint32_t apps_PP[]) {

    if (*appsVal0 < (APPS_0_MIN + APPS_FLOOR_THRESHOLD)){
        apps_PP[0] = 0;
    } else {
        apps_PP[0] = ((*appsVal0) - APPS_0_MIN) * (100.00 / (APPS_0_MAX - APPS_0_MIN));
    }

    if (apps_PP[0] < 0) {
        apps_PP[0] = 0;
    } //end if
    if (apps_PP[0] > 100) {
        apps_PP[0] = 100;
    } //end if

    if (*appsVal1 < (APPS_1_MIN + APPS_FLOOR_THRESHOLD)){
        apps_PP[1] = 0;
    } else {
        apps_PP[1] = ((*appsVal1) - APPS_1_MIN) * (100.00 / (APPS_1_MAX - APPS_1_MIN));
    }

    if (apps_PP[1] < 0) {
        apps_PP[1] = 0;
    } //end if
    if (apps_PP[1] > 100) {
        apps_PP[1] = 100;
    } //end if

//    add_to_buffer(apps2_buffer, &apps2_count, &apps2_index, apps_PP[0]);
//    apps_PP[0] = calculate_average(apps2_buffer, apps2_count);

    // the code to process the second apps sensor has been disabled. the code below is not correct and must be changed before use.
//    apps_PP[0] = 0.05405405 * (*appsVal0) - 35.13513513;
//
//    if (apps_PP[0] < 0) {
//        apps_PP[0] = 0;
//    } //end if
//    if (apps_PP[0] > 100) {
//        apps_PP[0] = 100;
//    } //end if
//
//    add_to_buffer(apps1_buffer, &apps1_count, &apps1_index, apps_PP[1]);
//    apps_PP[1] = calculate_average(apps1_buffer, apps1_count);

    // do some error checking here

    // if apps_PP[0] or [1] are less than a certain value, set them to 0!



} //end APPS_Mapping()

void BPSMapEncoderValueToPositionPercentage(uint32_t *bpsVal, uint32_t bps_PP[]){
    if (*bpsVal < (BPS_MIN + BPS_MINIMUM_THRESHOLD)){
        bps_PP[0] = 0;
    } else {
        bps_PP[0] = ((*bpsVal) - BPS_MIN) * (100.00 / (BPS_MAX - BPS_MIN));
    }

    if (bps_PP[0] < 0) {
        bps_PP[0] = 0;
    } //end if
    if (bps_PP[0] > 100) {
        bps_PP[0] = 100;
    } //end if
}
