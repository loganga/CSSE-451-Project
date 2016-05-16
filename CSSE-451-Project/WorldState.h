#ifndef __WORLDSTATE
#define __WORLDSTATE

#define NUM_TRACKED_FRAMES 10
#include "Scene.h"
#include <glm/detail/type_vec3.hpp>

class WorldState {
private:
	float currentTime;
	bool running;
	int resX, resY;
	float frameTimes[NUM_TRACKED_FRAMES];

	glm::vec3 cameraPos;
	glm::vec3 cameraLook;
	glm::vec3 cameraUp;

//	glm::vec4 lightPos;
	glm::vec3 lightIntensity;

public:
	Scene scene;

	WorldState()
	{
		running = false;
	}

	void init(int resX, int resY)
	{
		for (size_t i = 0; i<NUM_TRACKED_FRAMES; i++)
			frameTimes[i] = 0.0f;

		running = true;
		scene = Scene(glm::vec3(-10.0f), glm::vec3(10.0f), 1000);
		scene.init();

		glm::vec3 center = glm::vec3(0.0f);
		glm::vec3 max = scene.maxBound;
		glm::vec3 min = scene.minBound;
		glm::vec3 dim = max - min;
		printf("model loaded: bounds");
		printf("[%.2f %.2f %.2f]..", min[0], min[1], min[2]);
		printf("[%.2f %.2f %.2f] ", max[0], max[1], max[2]);
		printf("= dim [%.2f %.2f %.2f]\n", dim[0], dim[1], dim[2]);
		float camDistance = max(dim[0], dim[1]);
		cameraPos = glm::vec3(0, max[1], camDistance * 2);
		cameraLook = glm::vec3(0, 0, 0);
		cameraUp = glm::vec3(0, 1, 0);

//		lightPos = glm::vec4((max - center)*1.3f, 1);
//		lightIntensity = glm::vec3(1, 1, 1);
	}

	void timeStep(float t)
	{
		float elapsed = t - this->currentTime;
		this->updateFrameTime(elapsed);

		this->currentTime = t;
	}

	void updateFrameTime(float timeAsSeconds)
	{
		for (size_t i = 1; i<NUM_TRACKED_FRAMES; i++)
			frameTimes[i] = frameTimes[i - 1];
		frameTimes[0] = timeAsSeconds;
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
	
};

#endif