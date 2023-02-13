/*
 * BasicTimestampManager.h
 *
 *  Created on: 10 Feb 2023
 *      Author: Lucas Bonvin
 */

#ifndef COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_BASICTIMESTAMPMANAGER_H_
#define COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_BASICTIMESTAMPMANAGER_H_

#include "ITimestampManager.h"

namespace cloudio {

	class BasicTimestampManager: public ITimestampManager {
	public:
		virtual ~BasicTimestampManager();

		static BasicTimestampManager& getInstance();

		// from ITimestampManager interface
		void init();
		int64_t getTimestamp();

	private:
		BasicTimestampManager();
	};

} /* namespace cloudio */

#endif /* COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_BASICTIMESTAMPMANAGER_H_ */
