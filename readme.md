# ESP32 Light Sleep for Moddable SDK
Updated June 2, 2023

Sleep is a JavaScript class to use the ESP32 light sleep feature.

It currently implements wake on timer and GPIO.

It should be straightforward to extend to support wake on Wi-Fi and BLE. There is disabled support for wake on UART, but it there is some work to do make it useful.

Notes:

- See the code in main.js for an example of using the class.
- The Sleep class should only be instantiated once. This is currently not enforced.
- When using xsbug, debugger output is flushed before going to sleep
- To reset all sleep triggers, close the Sleep instance and create a new instance
- When light sleep is requested, it begins after the current turn completes. This means that `sleep.light()` returns immediately and the device goes to sleep shortly thereafter.
- The power consumption of an ESP32 with no active radio drops from 46 mA to 12 mA while in light sleep
