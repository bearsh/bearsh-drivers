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

#ifndef BEARSH_INTERRUPTINOUT_H_
#define BEARSH_INTERRUPTINOUT_H_

#include "mbed-drivers/platform.h"

#if DEVICE_INTERRUPTIN

#include "core-util/FunctionPointer.h"
#include "mbed-drivers/InterruptIn.h"

namespace bearsh {

class InterruptInOut: public InterruptIn {
public:
	InterruptInOut(PinName pin) : InterruptIn(pin) {}
	virtual ~InterruptInOut() {}

	InterruptInOut(PinName pin, PinDirection direction, PinMode mode, int value) : InterruptIn(pin) {
		if (direction != PIN_INPUT)
			gpio_dir(&gpio, PIN_INPUT);
		if (mode != PullDefault)
			gpio_mode(&gpio, mode);
		if (pin != NC)
			gpio_write(&gpio, value);
	}

	void write(int value) {
		gpio_write(&gpio, value);
	}

	void output() {
		disable_irq();
		gpio_dir(&gpio, PIN_OUTPUT);
	}

	void input() {
		gpio_dir(&gpio, PIN_INPUT);
	}

	int is_connected() {
		return gpio_is_connected(&gpio);
	}

    void rise_irq_enable(bool enable) {
    	gpio_irq_set(&gpio_irq, IRQ_RISE, enable ? 1 : 0);
    }

    void fall_irq_enable(bool enable) {
    	gpio_irq_set(&gpio_irq, IRQ_FALL, enable ? 1 : 0);
    }

#ifdef MBED_OPERATORS
	InterruptInOut& operator= (int value) {
		write(value);
		return *this;
	}

	InterruptInOut& operator= (InterruptInOut& rhs) {
		write(rhs.read());
		return *this;
	}
#endif
};

}

#endif

#endif /* BEARSH_INTERRUPTINOUT_H_ */
