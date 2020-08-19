#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/FPS.hpp"

#include "mge/core/Camera.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/OrbitBehaviour.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame ()
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

    //MESHES
    Mesh* sphereMesh = Mesh::load (config::MGE_MODEL_PATH+"sphere_smooth.obj");
    Mesh* objMesh = Mesh::load (config::MGE_MODEL_PATH+"suzanna_smooth.obj");
    Mesh* planeMesh = Mesh::load (config::MGE_MODEL_PATH+"plane.obj");

    //MATERIALS
    AbstractMaterial* litTextureMaterial = new LitTextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"bricks.jpg"), 10, glm::vec3(1,1,1));

    //SCENE SETUP
/*
    GameObject* obj = new GameObject ("GameObject", glm::vec3(0,2,0));
    obj->setMesh (objMesh);
    obj->setMaterial(litTextureMaterial);
    obj->setBehaviour (new RotatingBehaviour());
    _world->add(obj);
*/

    GameObject* plane = new GameObject ("Plane", glm::vec3(0,0,0));
    plane->scale(glm::vec3(20,20,20));
    plane->rotate(glm::radians(90.0f), glm::vec3(1,0,0));
    plane->setMesh(planeMesh);
    plane->setMaterial(litTextureMaterial);
    _world->add(plane);


    Light* light1 = new Light("Light", glm::vec3(0, 5, 4), glm::vec3(0, -1, 0), glm::vec3(1, 1, 1), 1, 360, false); //point light
    light1->setMesh(sphereMesh);
    light1->setMaterial(new ColorMaterial(glm::vec3(1, 1, 1)));
    light1->setBehaviour(new KeysBehaviour());
    _world->add(light1);

/*
    Light* light2 = new Light("Light", glm::vec3(0, 5, 8), glm::vec3(0, -1, -1), glm::vec3(1, 1, 0), 1, 60, false); //spot light
    light2->setMesh(sphereMesh);
    light2->setMaterial(new ColorMaterial(glm::vec3(1, 1, 1)));
    _world->add(light2);
/*

/*
    Light* light3 = new Light("Light", glm::vec3(0, 9, 0), glm::vec3(0, -1, -1), glm::vec3(0.4, 0.4, 0.4), 1, 360, true); //directional light
    light3->setMesh(sphereMesh);
    light3->setMaterial(new ColorMaterial(glm::vec3(1, 1, 1)));
    _world->add(light3);
*/


    Camera* camera = new Camera ("camera", glm::vec3(0,3,3));
    camera->setBehaviour(new OrbitBehaviour (plane, 30, 4, 75));
    //camera->setBehaviour(new LookAt(obj));
    _world->add(camera);
    _world->setMainCamera(camera);
}

void MGEDemo::_render() {
    AbstractGame::_render();
    _updateHud();
    //_world->renderDebugInfo();
}

void MGEDemo::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string(FPS::getFPS())+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}


MGEDemo::~MGEDemo()
{
	//dtor
}
