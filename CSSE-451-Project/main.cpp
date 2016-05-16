#define CRT_SECURE_NO_WARNINGS
#define RESOLUTION_X 800
#define RESOLUTION_Y 600
#define TARGET_FPS 60
#define PRINT_FPS_INTERVAL 10.0f

#define GL3W
#ifdef GLEW
#define GLEW_STATIC
//#include "Helpers/glew.h"
#endif
#ifdef GL3W
#include "GL/gl3w.h"
#endif


#include <stdio.h>
#include <stdlib.h>
#include <SFML/Window.hpp>

#include "WorldState.h"
#include "RenderEngine.h"

class Dingus
{
public:
	void worldLoop()
	{
		getWindowContext();

		float lastFrame = clock.restart().asSeconds();
		float lastPrint = lastFrame;
		float targetFrameTime = 1.0f / (float)TARGET_FPS;
		RenderEngine engine;
		WorldState state;

		state.init(RESOLUTION_X, RESOLUTION_Y);		
		engine.init(state);

		//main loop
		while (state.isRunning())
		{
			window->setActive();
			float currentTime = clock.getElapsedTime().asSeconds();
			float sinceLastFrame = currentTime - lastFrame;
			float sleepTime = targetFrameTime - sinceLastFrame;
			if (sleepTime > 0)
				sf::sleep(sf::seconds(sleepTime));

			currentTime = clock.getElapsedTime().asSeconds();
			lastFrame = currentTime;
			float sinceLastPrint = currentTime - lastPrint;

			state.timeStep(currentTime);

			if (sinceLastPrint > PRINT_FPS_INTERVAL)
			{
				lastPrint = currentTime;
				state.printFPS();
			}

			engine.display(state);
			window->display();
		}
	}

private:
	sf::Window* window;
	sf::Clock clock;
	

	

	void updateTime()
	{
		
	}

	void getWindowContext()
	{
		// ONLY HAS WINDOWS SUPPORT
		sf::err().rdbuf(NULL);
		sf::VideoMode mode(RESOLUTION_X, RESOLUTION_Y, 32);
		sf::ContextSettings settings(32, 0, 0, 3, 3, sf::ContextSettings::Core);
		window = new sf::Window(mode, "Fluid Simulation", sf::Style::Default, settings);
	}
};

int main() {
	Dingus d = Dingus();
	d.worldLoop();
}