#pragma once

#include <SDL/SDL.h>

namespace skrengine
{

	class FPSLimiter {
	public:
		FPSLimiter();
		~FPSLimiter();

		void init(float maxFPS);

		void setMaxFPS(float maxFPS);

		void begin();

		// Returns FPS
		float end();

	private:
		void calculateFPS();

		float _maxFPS;
		float _fps;
		float _frameTime;
		unsigned int _startTicks;
	};


}

