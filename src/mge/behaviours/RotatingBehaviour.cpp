#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"

RotatingBehaviour::RotatingBehaviour():AbstractBehaviour()
{
	//ctor
}

RotatingBehaviour::~RotatingBehaviour()
{
	//dtor
}

void RotatingBehaviour::update( float step )
{
	_owner->rotate( step * glm::radians(45.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ); // rotates 45� per second
}
