#include "xsmc.h"

#include "xsHost.h"
#include "mc.defines.h"
#include "mc.xs.h" // for xsID_ values

#include "esp_sleep.h"

void xs_sleep_reset(xsMachine *the)
{
	esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
}

void xs_sleep_light(xsMachine *the)
{
#ifdef mxDebug
	uart_wait_tx_done(0, 200);		// flush pending xsbug output
#endif

	esp_err_t err = esp_light_sleep_start();
	if (ESP_OK == err) {
		char *cause;
		switch (esp_sleep_get_wakeup_cause()) {
			case ESP_SLEEP_WAKEUP_UNDEFINED: cause = "undefined"; break;
			case ESP_SLEEP_WAKEUP_EXT0: cause = "ext0"; break;
			case ESP_SLEEP_WAKEUP_EXT1: cause = "ext1"; break;
			case ESP_SLEEP_WAKEUP_TIMER: cause = "timer"; break;
			case ESP_SLEEP_WAKEUP_TOUCHPAD: cause = "touchpad"; break;
			case ESP_SLEEP_WAKEUP_ULP: cause = "ulp"; break;
			case ESP_SLEEP_WAKEUP_GPIO: cause = "gpio"; break;
			case ESP_SLEEP_WAKEUP_UART: cause = "uart"; break;
			case ESP_SLEEP_WAKEUP_WIFI: cause = "wifi"; break;
			case ESP_SLEEP_WAKEUP_COCPU: cause = "cocpu"; break;
			case ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG: cause = "cocpu_trap"; break;
			case ESP_SLEEP_WAKEUP_BT: cause = "bt"; break;
			default: cause = "unknown"; break; 
		}
		xsmcSetString(xsResult, cause);
	}
}

void xs_sleep_setWakeUp(xsMachine *the)
{
	esp_sleep_enable_timer_wakeup((xsmcToNumber(xsArg(0))) * 1000);		// ms to us
}

void xs_sleep_setGPIO(xsMachine *the)
{
	int pin = xsmcToInteger(xsArg(0));
	char *reason = xsmcToString(xsArg(1));
	gpio_int_type_t intType;

	if (!esp_sleep_is_valid_wakeup_gpio(pin))
		xsUnknownError("pin cannot wake");

	if (xsmcArgc) {
		if (xsmcToBoolean(xsArg(0)))
			gpio_wakeup_enable(pin, GPIO_INTR_HIGH_LEVEL);
		else
			gpio_wakeup_enable(pin, GPIO_INTR_LOW_LEVEL);

		esp_sleep_enable_gpio_wakeup();
	} 
	else
		gpio_wakeup_disable(pin);
}

#if 0
void xs_sleep_setUART(xsMachine *the)
{
	int uart = xsmcToInteger(xsArg(0));
	esp_err_t err;
	if (xsmcArgc > 1) {
		err = uart_set_wakeup_threshold(uart, xsmcToInteger(xsArg(1)));
		if (err)
			xsUnknownError("set threshold failed");
	}
	err = esp_sleep_enable_uart_wakeup(uart);
	if (err)
		xsUnknownError("enable uart wakeup failed");
}
#endif
