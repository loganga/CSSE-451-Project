#ifndef __WORLDSTATE
#define __WORLDSTATE

#define NUM_TRACKED_FRAMES 10
#include "Scene.h"
#include <glm/detail/type_vec3.hpp>

class WorldState {
public:
	Scene* scene;

	WorldState()
	{
		running = false;
	}

	void init(int resX, int resY)
	{
		running = true;
		scene = new Scene(glm::vec3(-10.0f), glm::vec3(10.0f), 1000);
	}

	void timeStep(float currentTime)
	{
		
	}

	void printFPS()
	{
		float sum = 0.0f;
		float avg = 0.0f;
		float fps = 0.0f;

		for (size_t i = 0; i < NUM_TRACKED_FRAMES; i++)
			sum += frameTimes[i];

		avg = sum / NUM_TRACKED_FRAMES;
		fps = 1.0f / avg;
		printf("fps %f\n", fps);
	}

	bool isRunning() { return running; }

private:
	bool running;
	int resX, resY;
	float frameTimes[NUM_TRACKED_FRAMES];
	
};

#endif