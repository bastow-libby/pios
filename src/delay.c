void milisec_delay() {
	unsigned long start_time = get_timer_count();
	unsigned long time_passed = start_time - get_timer_count();

	while(time_passed <= 1000){
		time_passed = start_time - get_timer_count();
	}
}
