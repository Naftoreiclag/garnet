#include "GarnetApp.hpp"

#include <stdint.h>
#include <iostream>

#include "OgreEntity.h"

#include "SDL.h"



namespace grt
{
    
GarnetApp& GarnetApp::getSingleton() {
    static GarnetApp instance;
    return instance;
}

GarnetApp::GarnetApp() {
}

GarnetApp::~GarnetApp() {
}

void GarnetApp::initialize(Ogre::Root* ogreRoot, Ogre::RenderWindow* ogreWindow) {
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    mCamPitch = Ogre::Degree(0);
    mCamYaw = Ogre::Degree(0);
    mCamRoll = Ogre::Degree(0);
    
    mOgreRoot = ogreRoot;
    
    mSmgr = mOgreRoot->createSceneManager(Ogre::ST_GENERIC);
    mRootNode = mSmgr->getRootSceneNode();
    
    mCam = mSmgr->createCamera("Camera");
    mCam->setNearClipDistance(5);
    
    mCamLocNode = mRootNode->createChildSceneNode("CameraNode");
    mCamYawNode = mCamLocNode->createChildSceneNode();
    mCamPitchNode = mCamYawNode->createChildSceneNode();
    mCamRollNode = mCamPitchNode->createChildSceneNode();
    mCamRollNode->attachObject(mCam);
    /*
    mCam->setPosition(Ogre::Vector3(0, 0, 80));
    mCam->lookAt(Ogre::Vector3(0, 0, -300));
    */
    
    mCam->setAspectRatio(Ogre::Real(1280) / Ogre::Real(720));
    
    Ogre::Viewport* viewport = ogreWindow->addViewport(mCam);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    
    Ogre::SceneNode* headNode = mSmgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* ogreHead = mSmgr->createEntity("Head", "ogrehead.mesh");
    headNode->attachObject(ogreHead);
    headNode->setPosition(0, 0, -80);
    headNode->setScale(0.2f, 0.2f, 0.2f);
    
    mSmgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    
    mSmgr->setSkyBox(true, "Test");
    
    Ogre::Light* light = mSmgr->createLight("Light");
    light->setPosition(20,80,50);
}

void GarnetApp::onClose() {
}
void GarnetApp::onTick(float tps) {
    
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    
    Ogre::Vector3 moveVec;
    float spd = tps * 5;
    bool moved = false;
    if(keyStates[SDL_GetScancodeFromKey(SDLK_w)]) {
        moveVec.z = -spd;
        moved = true;
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_a)]) {
        moveVec.x = -spd;
        moved = true;
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_s)]) {
        moveVec.z = spd;
        moved = true;
    }
    if(keyStates[SDL_GetScancodeFromKey(SDLK_d)]) {
        moveVec.x = spd;
        moved = true;
    }
    
    if(moved) {
        mCamLocNode->translate(mCamYawNode->getOrientation() * mCamPitchNode->getOrientation() * moveVec);
    }
}


void GarnetApp::onKeyPress(const SDL_KeyboardEvent& event) {
    switch(event.keysym.sym) {
        case SDLK_w: {
            break;
        }
        case SDLK_a: {
            break;
        }
        case SDLK_s: {
            break;
        }
        case SDLK_d: {
            break;
        }
        default: {
            break;
        }
    }
}
void GarnetApp::onKeyRelease(const SDL_KeyboardEvent& event) {
    std::cout << "Key released" << std::endl;
}
void GarnetApp::onMouseMove(const SDL_MouseMotionEvent& event) {
    std::cout << "Mouse move " << event.xrel << "\t" << event.yrel << std::endl;
    
    float dx = -event.xrel;
    float dy = -event.yrel;
    Ogre::Radian dYaw = Ogre::Radian(dx / 200);
    Ogre::Radian dPitch = Ogre::Radian(dy / 200);
    
    mCamPitch += dPitch;
    mCamYaw += dYaw;
    
    if(mCamPitch > Ogre::Degree(90)) {
        mCamPitch = Ogre::Degree(90);
    }
    else if(mCamPitch < Ogre::Degree(-90)) {
        mCamPitch = Ogre::Degree(-90);
    }
    
    mCamYawNode->resetOrientation();
    mCamYawNode->yaw(mCamYaw);
    mCamPitchNode->resetOrientation();
    mCamPitchNode->pitch(mCamPitch);
    
}
void GarnetApp::onMousePress(const SDL_MouseButtonEvent& event) {
}
void GarnetApp::onMouseRelease(const SDL_MouseButtonEvent& event) {
    
}
}

