import Timer from "timer"
import Sleep from "sleep"

trace("awake for 2 seconds\n");

const sleep = new Sleep;
sleep.setWakeUp(5_000);		// after 5 seconds
sleep.setGPIO(0, 1);		// when GPIO 0 goes high

Timer.set(() => {
	trace("sleeping for 5 seconds or until GPIO 0 high\n");
	sleep.light(cause => {
		trace(`awake, again, because of "${cause}"\n`);
	});
}, 2000);
