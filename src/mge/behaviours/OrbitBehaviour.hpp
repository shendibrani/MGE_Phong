#ifndef OrbitBehaviour_H
#define OrbitBehaviour_H

#include <glm.hpp>

#include <SFML/Window.hpp>

#include "mge/behaviours/AbstractBehaviour.hpp"

class OrbitBehaviour : public AbstractBehaviour
{
    public:
        OrbitBehaviour (GameObject * pTarget, float pDistance, float pSpeed, float pAngleLimit);
        virtual ~OrbitBehaviour();

        virtual void update( float step );

    private:
        GameObject * _target;
        float _distance;
        float _speed;
        float _angleLimit;

        sf::Vector2i _prevMousePos;
};

#endif // OrbitBehaviour_H
