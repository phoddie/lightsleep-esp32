import Timer from "timer";

class Sleep {
	close() @ "xs_sleep_reset"
	
	light(done) {
		Timer.set(() => {
			const cause = light();
			done?.(cause);
		});
	}
	
	setWakeUp(ms) @ "xs_sleep_setWakeUp"
	setGPIO(number, level) @ "xs_sleep_setGPIO" 
//	setUART(number, threshold) @ "xs_sleep_setUART" 
}

function light() @ "xs_sleep_light";

export default Sleep;
