/*
 * ESP32TimestampManager.cpp
 *
 *  Created on: 10 Feb 2023
 *      Author: Lucas Bonvin
 */

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

	long ESP32TimestampManager::getTimestamp() {
		time_t now = 0;
		time(&now);
		long newTimestamp = now;
		return newTimestamp;
	}

} /* namespace cloudio */
