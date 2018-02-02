#pragma once
#include "kilolib.h"

// #define ROTATIONPERTICK 0.05
// #define DISTANCEPERTICK 0.5
// #define RADPERINT 0.02472
#define BEACON_NUM 3
#define K_CONST 1
#define MIN(a, b) ((a < b) ? a : b)

class mykilobot : public kilobot
{
	unsigned char dist;
	float theta;
	message_t out_message;
	long int motion_timer = 0;
	char phase = 0; // phase change occurs when see new light source
	long int phase_start[BEACON_NUM]; // array to record start time of each phase
	int phase_interval[BEACON_NUM];
	char motion_flag = 0; // 0 means stop, nonzero means move at that phase

	//main loop
	void loop()
	{
		set_color(RGB(1,1,1));

		if (id == 0){
			switch (phase)
			{
				case 0:
				{
					set_color(RGB(1,0,0));
					break;
				}
				case 1:
				{
					set_color(RGB(0,1,0));
					break;
				}
				case 2:
				{
					set_color(RGB(0,0,1));
					break;
				}
			}

			if ((angle_to_light_1 >= -0.03 && angle_to_light_1 < 0.07)
			|| (angle_to_light_2 >= -0.03 && angle_to_light_2 < 0.07)
			|| (angle_to_light_3 >= -0.03 && angle_to_light_3 < 0.07)) {
				// phase_start[0] records the starting time of the current phase
				int past_phase = motion_timer - phase_start[0];
				if (past_phase > 2) { // only update after some threshold time lapse
					for (int i = BEACON_NUM - 1; i > 0; i--) {
						phase_start[i] = phase_start[i-1];
					}
					phase_start[0] = motion_timer;
					// phase_interval[BEACON_NUM-1] corresponds to the oldest phase in record
					for (int i = BEACON_NUM - 1; i > 0; i--) {
						phase_interval[i] = phase_interval[i-1];
					}
					phase_interval[0] = past_phase;
					phase = (phase + 1) % BEACON_NUM;
				}
			}

			float period = 0.0;
			motion_flag = 1;
			for (int i = 0; i < BEACON_NUM; i++) {
				if (phase_interval[i] < phase_interval[BEACON_NUM - 1]) { // cannot include = here
					motion_flag = 0;
					break;
				}
				period += phase_interval[i];
			}

			if (motion_flag) {
				// float percent_interval = phase_interval[BEACON_NUM - 1] / period;
				float average = period / BEACON_NUM;
				// float above_ave = percent_interval - 1.0 / BEACON_NUM;
				float above_ave = -(phase_interval[BEACON_NUM - 1] - average); // could be below ave
				int thrust_time = MIN((int) (above_ave * K_CONST), phase_interval[BEACON_NUM-1]);
				if ((motion_timer < phase_start[0] + (phase_interval[BEACON_NUM-1] - thrust_time) / 2) ||
				(motion_timer > phase_start[0] + (phase_interval[BEACON_NUM-1] + thrust_time) / 2)) {
					motion_flag = 0;
				}
			}
			spinup_motors();
			if (motion_flag) {
				set_motors(50,50);
			} else {
				set_motors(50, 0);
			}
			motion_timer++;
		}
	}

	//executed once at start
	void setup()
	{
	}

	//executed on successfull message send
	void message_tx_success()
	{
	}

	//sends message at fixed rate
	message_t *message_tx()
	{
	}

	//receives message
	void message_rx(message_t *message, distance_measurement_t *distance_measurement,float t)
	{
	}

};
