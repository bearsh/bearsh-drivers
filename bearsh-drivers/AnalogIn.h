/*
 * Copyright (c) 2016, Martin Gysel, me@bearsh.org
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BEARSH_ANALOGIN_H_
#define BEARSH_EANALOGIN_H_

#include "mbed-drivers/platform.h"

#if DEVICE_ANALOGIN

#include "core-util/FunctionPointer.h"
#include "mbed-drivers/AnalogIn.h"
#include "ext-hal-nrf51/analogin.h"

namespace bearsh {

class AnalogIn: public mbed::AnalogIn {

public:
	AnalogIn(PinName pin);
	void config(uint8_t res, uint8_t inpsel, uint8_t refsel, uint8_t extrefsel) {
		analogin_config(&_adc, res, inpsel, refsel, extrefsel);
	}
	void enable() {
		analogin_enable(&_adc);
	}
	void disable() {
		analogin_disable(&_adc);
	}
	void start() {
		analogin_start(&_adc);
	}
	bool busy() {
		return (bool)analogin_busy(&_adc);
	}
	uint16_t read_result_u16() {
		return analogin_read_result_u16(&_adc);
	}

	void interrupt(void (*fptr)(void));

	template<typename T>
	void interrupt(T* tptr, void (T::*mptr)(void)) {
		if (mptr) {
			irq.attach(tptr, mptr);
			analogin_irq_set(&_adc, (uint32_t)this, 1);
		} else {
			analogin_irq_set(&_adc, 0, 0);
		}
	}

	static void irq_handler(uint32_t id);

protected:
	mbed::util::FunctionPointer irq;
};

} // namespace bearsh

#endif

#endif /* BEARSH_ANALOGIN_H_ */
