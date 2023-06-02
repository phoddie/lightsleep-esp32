# ESP32 Light Sleep for Moddable SDK
Updated June 2, 2023

Sleep is a JavaScript class to use the ESP32 light sleep feature.

It currently implements wake on timer and GPIO.

There is disabled support for wake on UART, but it there is some work to do make it useful.

Notes:

- See the code in main.js for an example of using the class.
- The Sleep class should only be instantiated once. This is currently not enforced.
- When using xsbug, debugger output is flushed before going to sleep
- To reset all sleep triggers, close the Sleep instance and create a new instance
- When light sleep is requested, it begins after the current turn completes. This means that `sleep.light()` returns immediately and the device goes to sleep shortly thereafter.
- The power consumption of an ESP32 with no active radio drops from 46 mA to 12 mA while in light sleep (these numbers were observed on a development board that isn't optimized for low-energy so they are useful as proof that it is working, but not a representaiton of what you will see)


### Wi-Fi

The documentation and examples indicate that before going to sleep (light or deep) the application should disconnect from Wi-Fi and recommend on wake.

There is a notificaiton for wake on Wi-Fi. It isn't documented so some exploration is needed. Also, it is not supported on the original ESP32, but is for S2, S3, and C3.

There are power saving modes of the Wi-Fi chip that are independent of sleep using `esp_wifi_set_ps`.

### BLE

There is no BLE wake. There is a constant for it, but no chip implements it.

 
