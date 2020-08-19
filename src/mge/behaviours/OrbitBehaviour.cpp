#include <glm.hpp>

#include "mge/behaviours/OrbitBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Input.hpp"

#include <SFML/Window.hpp>

#include <cmath>
#include <iostream>

OrbitBehaviour::OrbitBehaviour(GameObject * pTarget, float pDistance, float pSpeed, float pAngleLimit) : AbstractBehaviour(), _target(pTarget), _distance(pDistance), _speed(pSpeed), _angleLimit(pAngleLimit)
{
    _prevMousePos = sf::Mouse::getPosition();
}

OrbitBehaviour::~OrbitBehaviour()
{

}

void OrbitBehaviour::update(float step)
{
    /*
    glm::vec3 dir_TargetToCam;
    glm::vec3 dir_NextTargetToCam;

    sf::Vector2i currentMousePos = sf::Mouse::getPosition();
    glm::vec2 mouseVector = glm::vec2(currentMousePos.x, currentMousePos.y) - glm::vec2(_prevMousePos.x, _prevMousePos.y) * 0.01f * _speed * step;
    sf::Mouse::setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2));
    _prevMousePos = sf::Mouse::getPosition();

    if(glm::length(_owner->getLocalPosition() - _target->getLocalPosition()) == 0) {
        dir_TargetToCam = glm::vec3(1,0,0);
    } else {
        dir_TargetToCam = glm::normalize(_owner->getLocalPosition() - _target->getLocalPosition());
    }
    */

    _distance += Input::GetMouseWheelDelta() / 10;

    //Get Mouse Position
    sf::Vector2i currentMousePos = sf::Mouse::getPosition();

    //Get Mouse Delta
    glm::vec2 mouseVector = glm::vec2(currentMousePos.x, currentMousePos.y) - glm::vec2(_prevMousePos.x, _prevMousePos.y);

    //Set Mouse to center so we can fully see the rotation mode
    int screenHeight = sf::VideoMode::getDesktopMode().height;
    int screenWidth = sf::VideoMode::getDesktopMode().width;
    sf::Mouse::setPosition(sf::Vector2i(screenWidth / 2, screenHeight / 2));

    //Set prevMousePos
    _prevMousePos = sf::Mouse::getPosition();

    //Get X Value of Mouse delta and scale it a little
    float mouseXMovement = mouseVector.x / 100 * _speed * step;



    //Set up forward vector
    glm::vec3 forward;

    //Check if target and owner are on the same position
    if(glm::length(_owner->getLocalPosition() - _target->getLocalPosition()) == 0)
    {
        //Get the unit vector from target to camera
        forward = glm::vec3(1,0,0);
    }
    else
    {
        //Get the unit vector from target to camera
        forward = glm::normalize(_owner->getLocalPosition() - _target->getLocalPosition());
    }

    forward *= _distance;


    //Construct Rotation Matrix with Mouse X
    glm::mat3 rotationMatrixY = glm::mat3(glm::vec3(cos(mouseXMovement), 0, -sin(mouseXMovement)),
                                          glm::vec3(0, 1, 0),
                                          glm::vec3(sin(mouseXMovement ), 0, cos(mouseXMovement)));

    //multiply our target->cam vector by the rotation matrix, plus add target position so the desired position is from the target
    _owner->setLocalPosition((rotationMatrixY * forward) + _target->getLocalPosition());









    //Normalize forward vector again for Up Down
    forward = glm::normalize(_owner->getLocalPosition() - _target->getLocalPosition());

    //Calculate right
    glm::vec3 targetRight = glm::cross (glm::vec3(0,1,0), forward); //TODO What if worldUp == forward??

    //Set up down rotation axis
    glm::vec3 n = glm::normalize(targetRight);

    //calculate angle
    float a = mouseVector.y / 100 * _speed * step;;

    //Construct Rotation Matrix
    glm::mat3 rotationMatrixUpDown = glm::mat3(glm::vec3(n.x*n.x*(1-cos(a))+cos(a),     n.x*n.y*(1-cos(a))-n.z*sin(a),   n.x*n.z*(1-cos(a))+n.y*sin(a)),
                                               glm::vec3(n.y*n.x*(1-cos(a))+n.z*sin(a), n.y*n.y*(1-cos(a))+cos(a),       n.y*n.z*(1-cos(a))-n.x*sin(a)),
                                               glm::vec3(n.z*n.x*(1-cos(a))-n.y*sin(a), n.z*n.y*(1-cos(a))+n.x*sin(a), n.z*n.z*(1-cos(a))+cos(a)));


    //Apply the new position
    forward = forward * _distance;
    glm::vec3 tempForward = forward * rotationMatrixUpDown;
    float nextAngle = glm::degrees(glm::angle(glm::normalize(glm::vec3(tempForward.x, 0, tempForward.z)), glm::normalize(tempForward)));

    //std::cout << nextAngle << std::endl;

    if(nextAngle < _angleLimit)
    {
        _owner->setLocalPosition(tempForward + _target->getLocalPosition());
    }







    //Normalize forward vector again for LookAt
    forward = glm::normalize(_owner->getLocalPosition() - _target->getLocalPosition());

    glm::vec3 right = glm::normalize(glm::cross (glm::vec3(0,1,0), forward)); //TODO What if worldUp == forward??
    glm::vec3 up = glm::normalize(glm::cross (forward, right));

    //Do the Lookat
    _owner->setTransform(
     glm::mat4 (glm::vec4(right, 0),
                glm::vec4(up,0),
                glm::vec4(forward,0),
                glm::vec4(_owner->getLocalPosition(),1))
    );
}
