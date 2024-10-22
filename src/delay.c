void wait_msec(int number) {
	unsigned long start_time = get_timer_count();
	unsigned long time_passed = start_time - get_timer_count();
	while(time_passed <= number*1000){
		time_passed = start_time - get_timer_count();
	}

}
void wait_cycles(int time) {
	unsigned long start_time = get_timer_count();
        unsigned long time_passed = start_time - get_timer_count();
        while(time_passed <= time){
                time_passed = start_time - get_timer_count();
        }

}
