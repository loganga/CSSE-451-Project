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
#include "ShaderManager.h"

#define MAX_PARTICLES 1000

class RenderEngine
{
public:
	// OVERALL TODO: Add shader loading and uniform uploads. Write shaders.
	// Refactor a bunch of the Particle data to be in the Scene class.
	// Updates for particles should be called through the WorldState and
	// delegated to the scene.
	const static GLfloat vertexBufferData[];

	RenderEngine()
	{
		initialized = false;
	}

	void init(WorldState &state)
	{
		initialized = true;

		float ver = initLoader();
		if (ver < 1.0f)
		{
			printf("OpenGL is not supported.\n");
		}
		printf("OpenGL version %.1f is supported.\n", ver);

		state.scene->generateParticleLayer();
		state.scene->updateParticles();

		glEnable(GL_DEPTH_TEST);

		setupBuffers();
		buildRenderBuffers();
	}

	void display(WorldState &state)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		checkGLError("clear");

		state.scene->updateParticles();
		updateBuffers(state);

		glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
		glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
		glVertexAttribDivisor(2, 1); // color : one per quad -> 1

		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, state.scene->particleCount);
	}

	void setupShader()
	{
		char const * vertPath = "Shaders/sph.vert";
		char const * fragPath = "Shaders/sph.frag";

		shaderProg = ShaderManager::shaderFromFile(&vertPath, &fragPath, 1, 1);

		checkGLError("shader");
	}

	~RenderEngine()
	{
		if (initialized)
		{
			glDeleteBuffers(1, &vertexBuffer);
			glDeleteBuffers(1, &positionBuffer);
			glDeleteBuffers(1, &colorBuffer);
		}
	}

private:
	WorldState state;
	bool initialized;

	GLuint vertexArray;
	GLuint vertexBuffer;
	// common vertex data quad, positions are what differ
	GLint vertexSlot;

	GLuint positionBuffer;
	GLint positionSlot;

	GLuint colorBuffer;
	GLint colorSlot;

	GLuint shaderProg;


	void setupBuffers()
	{
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, vertexBufferData, GL_STATIC_DRAW);
//		vertexSlot = glGetAttribLocation(shaderProg, "pos");
		checkGLError("setup");

		glGenBuffers(1, &positionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
		positionSlot = glGetAttribLocation(shaderProg, "pos");
		glEnableVertexAttribArray(positionSlot);
		glVertexAttribPointer(positionSlot, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		checkGLError("setup");

		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
		colorBuffer = glGetAttribLocation(shaderProg, "colorIn");
		glEnableVertexAttribArray(colorSlot);
		glVertexAttribPointer(positionSlot, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		checkGLError("setup");
	}

	void updateBuffers(WorldState &s)
	{
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, state.scene->particleCount * sizeof(GLfloat) * 4, s.scene->positionBufferData);

		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, state.scene->particleCount * sizeof(GLubyte) * 4, s.scene->colorBufferData);
	}

	void buildRenderBuffers()
	{
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0, // attribute. No particular reason for 0, but must match the layout in the shader.
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
			);

		// 2nd attribute buffer : positions of particles' centers
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glVertexAttribPointer(
			1, // attribute. No particular reason for 1, but must match the layout in the shader.
			4, // size : x + y + z + size => 4
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
			);

		// 3rd attribute buffer : particles' colors
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glVertexAttribPointer(
			2, // attribute. No particular reason for 1, but must match the layout in the shader.
			4, // size : r + g + b + a => 4
			GL_UNSIGNED_BYTE, // type
			GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0, // stride
			(void*)0 // array buffer offset
			);
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
