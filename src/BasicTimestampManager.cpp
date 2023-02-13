/*
 * BasicTimestampManager.cpp
 *
 *  Created on: 10 Feb 2023
 *      Author: Lucas Bonvin
 */

#include "BasicTimestampManager.h"
#include "time.h"

namespace cloudio {

	BasicTimestampManager::BasicTimestampManager() {

	}

	BasicTimestampManager::~BasicTimestampManager() {
	}

	BasicTimestampManager& BasicTimestampManager::getInstance() {
		static BasicTimestampManager timestampManager;
		return timestampManager;
	}

	void BasicTimestampManager::init() {
	}

	int64_t BasicTimestampManager::getTimestamp() {
		return time(nullptr);
	}

} /* namespace cloudio */
