#include <iostream>
#include <glm.hpp>
#include "mge/core/Light.hpp"
#include <vector>
#include <string>

const int Light::_maxLights = 10;
std::vector<Light*> Light::_lights;
float Light::_ambientCoefficient = 0.0005f;

Light::Light(std::string pName, glm::vec3 pPosition, glm::vec3 pDirection, glm::vec3 pIntensities, float pAttenuation, float pConeAngle, bool pIsDirectional)
    : GameObject(pName, pPosition), _direction(pDirection), _intensities(pIntensities), _attenuation(pAttenuation), _coneAngle(pConeAngle), _isDirectional(pIsDirectional)
{
    addLight(this);
}

Light::~Light() { }

void Light::addLight(Light* pLight)
{
    if(_lights.size() < _maxLights) {
        _lights.push_back(pLight);
    } else {
        std::cout << "The maximum number of lights have been reached!" << std::endl;
    }
}
