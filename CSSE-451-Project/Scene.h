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
	sf::Vector3<GLfloat> minBound;
	sf::Vector3<GLfloat> maxBound;

	Scene() {}

	Scene(sf::Vector3<float> minBound, sf::Vector3<float> maxBound, const int maxParticles)
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

	void getElementBytes()
	{
		
	}

	void getElements()
	{
		
	}
};


#endif
