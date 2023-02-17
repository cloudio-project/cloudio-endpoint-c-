/*
 * ESP32TimestampManager.cpp
 *
 *  Created on: 10 Feb 2023
 *      Author: Lucas Bonvin
 */

#ifdef ESP_PLATFORM
#include "ESP32TimestampManager.h"
#include "time.h"
#include "esp_sntp.h"
#include <iostream>

using namespace std;

namespace cloudio {

    ESP32TimestampManager::ESP32TimestampManager() {
        this->init();
    }

    ESP32TimestampManager::~ESP32TimestampManager() {
    }

    ESP32TimestampManager& ESP32TimestampManager::getInstance() {
        static ESP32TimestampManager timestampManager;
        return timestampManager;
    }

    void ESP32TimestampManager::init() {

        sntp_setoperatingmode(SNTP_OPMODE_POLL);
        sntp_setservername(0, "pool.ntp.org");
        sntp_init();

        // wait for time to be set
        int retry = 0;
        const int retry_count = 10;
        while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET
                && ++retry < retry_count) {
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            cout << "Waiting for system time to be set... (" << retry << "/"
                    << retry_count << ")" << endl;
        }

        if (retry >= retry_count) {
            esp_restart();
            cout << "Couldn't not get sntp time, will reboot" << endl;
        }
    }

    int64_t ESP32TimestampManager::getTimestamp() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        int64_t newTimestamp =  tv.tv_sec;
        // int64_t newTimestamp = (tv.tv_sec * 1000LL + (tv.tv_usec/1000)); // this is timestamp in ms
        // cjson doesn't support 64 bits so for now we stay in second resolution...
        return newTimestamp;
    }

} /* namespace cloudio */
#endif //ESP_PLATFORM
