#ifndef __RENDERENGINE
#define __RENDERENGINE

#define TEX_TYPE GL_TEXTURE_RECTANGLE

#include "Helpers/glm/glm.hpp"
#include "Helpers/glm/gtc/matrix_transform.hpp"
#include "Helpers/glm/gtc/matrix_inverse.hpp"
#include "Helpers/GLHelper.h""

#include "WorldState.h"
#include "Helpers/glew.h"
#include "Scene.h"

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
	GLuint vertexArray;

	// TODO: take in a scene object as a reference
	void setupBuffers(Scene &s)
	{
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		GLuint idBuffer;
		GLint idSlot = 0;

		//upload element ids only
		glGenBuffers(1, &idBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, idBuffer);
		glBufferData(GL_ARRAY_BUFFER, s.getElementBytes(), &s.getElements()[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(idSlot);
		glVertexAttribPointer(idSlot, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//		//quad for render to texture
		//		static const GLfloat quadVertexData[] = {
		//			-1.0f, -1.0f, 0.0f,
		//			1.0f, -1.0f, 0.0f,
		//			1.0f, 1.0f, 0.0f,
		//			-1.0f, -1.0f, 0.0f,
		//			1.0f, 1.0f, 0.0f,
		//			-1.0f, 1.0f, 0.0f,
		//		};
		//		checkGLError("id buffer");
		//
		//		glGenVertexArrays(1, &quadVertexArray);
		//		glBindVertexArray(quadVertexArray);
		//		GLuint quadVertexBuffer;
		//		glGenBuffers(1, &quadVertexBuffer);
		//		glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
		//		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertexData), quadVertexData, GL_STATIC_DRAW);
		//		glEnableVertexAttribArray(glGetAttribLocation(textureShader, "pos"));
		//		glVertexAttribPointer(glGetAttribLocation(textureShader, "pos"), 3, GL_FLOAT, GL_FALSE, 0, 0);

		checkGLError("quad buffer");
	}

	float initLoader()
	{
		float ver = 0.0f;

#ifdef GLEW

		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %p\n", glewGetErrorString(err));
		}
		fprintf(stdout, "Status: Using GLEW %p\n", glewGetString(GLEW_VERSION));

		if (GLEW_VERSION_1_1) { ver = 1.1f; }
		if (GLEW_VERSION_1_2) { ver = 1.2f; }
		if (GLEW_VERSION_1_3) { ver = 1.3f; }
		if (GLEW_VERSION_1_4) { ver = 1.4f; }
		if (GLEW_VERSION_1_5) { ver = 1.5f; }

		if (GLEW_VERSION_2_0) { ver = 2.0f; }
		if (GLEW_VERSION_2_1) { ver = 2.1f; }

		if (GLEW_VERSION_3_0) { ver = 3.0f; }
		if (GLEW_VERSION_3_1) { ver = 3.1f; }
		if (GLEW_VERSION_3_2) { ver = 3.2f; }
		if (GLEW_VERSION_3_3) { ver = 3.3f; }

		if (GLEW_VERSION_4_0) { ver = 4.0f; }
		if (GLEW_VERSION_4_1) { ver = 4.1f; }
		if (GLEW_VERSION_4_2) { ver = 4.2f; }
		if (GLEW_VERSION_4_3) { ver = 4.3f; }
		if (GLEW_VERSION_4_4) { ver = 4.4f; }
		if (GLEW_VERSION_4_5) { ver = 4.5f; }
#endif

#ifdef GL3W
		if (gl3wInit()) {
			fprintf(stderr, "failed to initialize OpenGL\n");
		}

		if (gl3wIsSupported(1, 1)) { ver = 1.1f; }
		if (gl3wIsSupported(1, 2)) { ver = 1.2f; }
		if (gl3wIsSupported(1, 3)) { ver = 1.3f; }
		if (gl3wIsSupported(1, 4)) { ver = 1.4f; }
		if (gl3wIsSupported(1, 5)) { ver = 1.5f; }

		if (gl3wIsSupported(2, 0)) { ver = 2.0f; }
		if (gl3wIsSupported(2, 1)) { ver = 2.1f; }

		if (gl3wIsSupported(3, 0)) { ver = 3.0f; }
		if (gl3wIsSupported(3, 1)) { ver = 3.1f; }
		if (gl3wIsSupported(3, 2)) { ver = 3.2f; }
		if (gl3wIsSupported(3, 3)) { ver = 3.3f; }

		if (gl3wIsSupported(4, 0)) { ver = 4.0f; }
		if (gl3wIsSupported(4, 1)) { ver = 4.1f; }
		if (gl3wIsSupported(4, 2)) { ver = 4.2f; }
		if (gl3wIsSupported(4, 3)) { ver = 4.3f; }
		if (gl3wIsSupported(4, 4)) { ver = 4.4f; }
		if (gl3wIsSupported(4, 5)) { ver = 4.5f; }
#endif

		return ver;
	}

};

#endif
