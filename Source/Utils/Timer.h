#pragma once

// Linux ayithe timespec vaadu annaadu

#include <time.h>

namespace kodi {

	namespace utils {

		//// https://stackoverflow.com/questions/1487695/c-cross-platform-high-resolution-timer#5524138
		//typedef std::chrono::high_resolution_clock Clock;

		//class Timer {
		//private:

		//	std::chrono::steady_clock::time_point start;
		//	Clock clock;

		//public:
		//	Timer() {

		//		start = Clock::now();

		//	}

		//	void Reset() {

		//	}

		//	void Elapsed() {

		//	}

		//};

		class Timer {

		private: 
			time_t start;

		public:
			Timer() {
				
				start = clock();

			};

			void Reset() {
				start = clock();
			};

			long ElapsedTime() {

				clock_t difference = clock() - start;
				long msec = difference * 1000 / CLOCKS_PER_SEC;
				//  Note that the time can wrap around.  On a 32-bit system where CLOCKS_PER_SEC equals 1000000 this function will return the same value approximately every 72 minutes.
				return msec;
			};

		};


	}

}
