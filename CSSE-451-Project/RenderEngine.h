#ifndef  __RENDERENGINE
#define __RENDERENGINE

#define TEX_TYPE GL_TEXTURE_RECTANGLE

#include "Helpers/glm/glm.hpp"
#include "Helpers/glm/gtc/matrix_transform.hpp"
#include "Helpers/glm/gtc/matrix_inverse.hpp"

#include "WorldState.h"

class RenderEngine
{
public:
	RenderEngine()
	{
		initialized = false;
	}

	void render(WorldState sate);

	void init(WorldState &state)
	{
		initialized = true;

		float ver = initLoader();
		if (ver < 1.0f)
		{
			printf("OpenGL is not supported.\n");
		}
		printf("OpenGL version %.1f is supported.\n", ver);

		glEnable(GL_DEPTH_TEST);

	}

	void display(WorldState state)
	{
		
	}

	void setupShader()
	{
		
	}

	// TODO: take in a scene object as a reference
	void setupBuffers()
	{
		
	}

	// TODO: take in a scene object as a reference
	void buildRenderBuffers()
	{
		
	}

	~RenderEngine()
	{
		if (initialized)
		{
//			glDeleteBuffers(1, &positionBuffer);
		}
	}

private:
	WorldState state;
	bool initialized;

	float initLoader()
	{
		float ver = initLoader();
		glewExperimental = GL_TRUE;

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	}
};

#endif
