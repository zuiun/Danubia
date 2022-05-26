#include <chrono>
#include "time_manager.hpp"

using namespace std::chrono;

/*
 * Initialises time manager
 *
 * frame_rate = New frame rate
 */
TimeManager::TimeManager (int frame_rate) {
	this->frame_counter = 0;
	this->frame_rate = frame_rate;
	this->base_wait = 1000 / frame_rate;
	this->minimum_wait = base_wait * 0.5;
	this->delta_time = 0;
	this->time = system_clock::now ();
}

TimeManager::~TimeManager () {
	// do nothing
}

/*
 * Gets new frame information
 * This tells the game how long to wait for the next frame and whether to skip rendering
 * 
 * Pre: None
 * Post: None
 * Return: New frame information 
 */
TimeManager::FrameInformation* TimeManager::get_frame_information () {
	FrameInformation* result = new FrameInformation ();

	delta_time = duration_cast<milliseconds> (system_clock::now () - time).count ();

	// Less than one second has passed; continue updating
	if (delta_time < 1000) {
		// Not enough frames in this second; continue updating
		if (frame_counter < frame_rate) {
			result->wait_time = (1000 - delta_time) / (frame_rate - frame_counter);
			result->is_skip_frame = result->wait_time < minimum_wait;
		// Too many frames in this second; skip frame and use base update
		} else {
			result->wait_time = base_wait;
			result->is_skip_frame = true;
		}
	// One or more seconds have passed; force update and reset counters
	} else {
		this->frame_counter = 0;
		this->delta_time = 0;
		this->time = system_clock::now ();
		result->wait_time = base_wait;
		result->is_skip_frame = false;
	}

	frame_counter++;
	return result;
}
