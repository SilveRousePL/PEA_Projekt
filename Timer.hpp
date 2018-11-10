/*
 * Timer.hpp
 *
 *  Created on: 28 mar 2018
 *      Author: darek
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_
#include <chrono>
#include <cstdint>

class Timer {
	std::chrono::high_resolution_clock::time_point begin_time;
	std::chrono::high_resolution_clock::time_point end_time;
public:
	Timer() {
		resetTimer();
	}
	virtual ~Timer() {
	}

	void startTimer() {
		begin_time = std::chrono::high_resolution_clock::now();
	}
	void stopTimer() {
		end_time = std::chrono::high_resolution_clock::now();
	}
	uint64_t getTimeNs() {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(
				end_time - begin_time).count();
	}
	uint64_t getTimeUs() {
		return std::chrono::duration_cast<std::chrono::microseconds>(
				end_time - begin_time).count();
	}
	long double getTimeMs() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(
				end_time - begin_time).count();
	}
	long double getTimeS() {
		return std::chrono::duration_cast<std::chrono::seconds>(
				end_time - begin_time).count();
	}
	void resetTimer() {
		auto now = std::chrono::high_resolution_clock::now();
		begin_time = now;
		end_time = now;
	}
};

#endif /* TIMER_HPP_ */
