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

#include "bearsh-drivers/AnalogIn.h"

#if DEVICE_ANALOGIN

namespace bearsh {

AnalogIn::AnalogIn(PinName pin): mbed::AnalogIn(pin)
{
	analogin_irq_set_handler(&_adc, &AnalogIn::irq_handler);
	analogin_irq_init();
}

void AnalogIn::interrupt(void (*fptr)(void)) {
	if (fptr) {
		irq.attach(fptr);
		analogin_irq_set(&_adc, (uint32_t)this, 1);
	} else {
		analogin_irq_set(&_adc, 0, 0);
	}
}

void AnalogIn::irq_handler(uint32_t id) {
	AnalogIn *handler = (AnalogIn*)id;
	handler->irq.call();
}

}

#endif
