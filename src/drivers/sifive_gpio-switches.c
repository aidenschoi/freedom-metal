/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <metal/machine/platform.h>

#ifdef METAL_SIFIVE_GPIO_SWITCHES

#include <metal/drivers/riscv_cpu.h>
#include <metal/drivers/sifive_gpio-switches.h>
#include <metal/machine.h>
#include <string.h>

int metal_switch_has_label(struct metal_switch *flip, char *label) {
    if (strcmp(__metal_driver_sifive_gpio_switch_label(flip), label) == 0) {
        return 1;
    }
    return 0;
}

struct metal_interrupt *
metal_switch_interrupt_controller(struct metal_switch *flip) {
    return __metal_driver_sifive_gpio_switch_interrupt_controller(flip);
}

int metal_switch_get_interrupt_id(struct metal_switch *flip) {
    int irq, max_irq;
    struct metal_interrupt *irc;

    irq = __metal_driver_sifive_gpio_switch_interrupt_line(flip);
    irc = __metal_driver_sifive_gpio_switch_interrupt_controller(flip);
    if (irc != NULL) {
        max_irq = _metal_interrupt_command_request(irc, METAL_MAX_INTERRUPT_GET,
                                                   NULL);

        if (irq < max_irq) {
            return _metal_interrupt_command_request(
                irc, METAL_INDEX_INTERRUPT_GET, (void *)&irq);
        }
    }
    return METAL_INTERRUPT_ID_LCMX;
}

#endif

typedef int no_empty_translation_units;
