#ifndef __SCENE
#define __SCENE
#include <vector>
#include "Particle.h"
#include <SFML/System/Vector3.hpp>

class Scene
{
public:
	//This vector of particles will have to be a complex tree structure of some sort
	int maxParticles;
//	Particle particles[maxParticles];
//	std::vector<Particle> particles;
	std::vector<GLfloat> particleVerts; // 3 per particle
//	std::vector<GLfloat> particleMass; // 1 per particle
	glm::vec3 minBound;
	glm::vec3 maxBound;

	Scene() {}

	Scene(glm::vec3 minBound, glm::vec3 maxBound, const int maxParticles)
	{
		this->minBound = minBound;
		this->maxBound = maxBound;
		this->maxParticles = maxParticles;
	}

	void generateParticleLayer(GLuint amount)
	{
		//TODO
	}

	void generateRandomParticles(GLuint amount)
	{
		//TODO
	}

	GLfloat* getVertices()
	{
		return &particleVerts[0];
	}

	void getElementBytes()
	{
		
	}

	void getElements()
	{
		
	}
};


#endif
