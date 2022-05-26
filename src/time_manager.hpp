#ifndef TIME_MANAGER_HPP
#define TIME_MANAGER_HPP

#include <chrono>

class TimeManager {
public:
	struct FrameInformation {
		bool is_skip_frame;
		int wait_time;
	};

	TimeManager (int frame_rate = 30);
	~TimeManager ();
	FrameInformation* get_frame_information ();
private:
	int frame_counter;
	int frame_rate;
	int base_wait;
	int minimum_wait;
	int delta_time;
	std::chrono::system_clock::time_point time;
};

#endif
