#ifndef __PARTICLE
#define __PARTICLE

class Particle {
public:
	glm::vec3 pos, vel;
	GLfloat r, g, b, a;

	Particle() {}

	Particle(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void setPos(GLfloat x, GLfloat y, GLfloat z)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}

};

#endif