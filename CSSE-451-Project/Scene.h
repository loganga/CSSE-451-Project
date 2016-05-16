#ifndef __SCENE
#define __SCENE
#include <vector>
#include "Particle.h"
#include <SFML/System/Vector3.hpp>
#include <glm/detail/type_vec3.hpp>
#include "GL/glcorearb.h"

class Scene
{
public:
	//This vector of particles will have to be a complex tree structure of some sort
	int maxParticles;
	Particle* particles;
	int particleCount;
	GLfloat* positionBufferData;
	GLfloat* colorBufferData;
	glm::vec3 minBound;
	glm::vec3 maxBound;

	Scene() {}

	Scene(glm::vec3 minBound, glm::vec3 maxBound, const int maxParticles)
	{
		this->minBound = minBound;
		this->maxBound = maxBound;
		this->maxParticles = maxParticles;
	}

	void init()
	{
		particles = new Particle[maxParticles];
		positionBufferData = new GLfloat[maxParticles * 4];
		colorBufferData = new GLfloat[maxParticles * 4];
	}

	void generateParticleLayer()
	{
		for (int i = 0; i < maxParticles; i++)
		{
			// generate random floats for x and y, leave z 0.
			float x = std::fmodf((float)rand(), (float)((minBound[0] - maxBound[0] + 1) + minBound[0]));
			float z = std::fmodf((float)rand(), (float)((minBound[2] - maxBound[2] + 1) + minBound[2]));
			particles[i] = Particle(x, 0.0f, z, 0.0f, 0.0f, 1.0f, 1.0f);
			particles[i].size = 0.1f;

			particleCount++;
		}
	}

	void generateRandomParticles(GLuint amount)
	{
		//TODO
	}

	void updateParticles()
	{
		for (int i = 0; i < maxParticles; i++)
		{
			Particle p = particles[i];
			// do physics simulations here!

			// Use this when camera data has been made available in RenderEngine
			//			p.distFromCam = glm::length2(p.pos - cameraPosition);

			positionBufferData[4 * particleCount + 0] = p.pos.x;
			positionBufferData[4 * particleCount + 1] = p.pos.y;
			positionBufferData[4 * particleCount + 2] = p.pos.z;
			positionBufferData[4 * particleCount + 3] = p.size;

			colorBufferData[4 * particleCount + 0] = p.r;
			colorBufferData[4 * particleCount + 1] = p.g;
			colorBufferData[4 * particleCount + 2] = p.b;
			colorBufferData[4 * particleCount + 3] = p.a;
		}
	}

	GLfloat* getVertices()
	{
		
	}

	void getElementBytes()
	{
		
	}

	void getElements()
	{
		
	}
};


#endif
