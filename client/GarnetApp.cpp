#include "GarnetApp.hpp"

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
    mOgreRoot = ogreRoot;
    
    mSmgr = mOgreRoot->createSceneManager(Ogre::ST_GENERIC);
    
    mCam = mSmgr->createCamera("Camera");
    
    mCam->setPosition(Ogre::Vector3(0, 0, 80));
    mCam->lookAt(Ogre::Vector3(0, 0, -300));
    mCam->setNearClipDistance(5);
    
    mCam->setAspectRatio(Ogre::Real(1280) / Ogre::Real(720));
    
    Ogre::Viewport* viewport = ogreWindow->addViewport(mCam);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    
    Ogre::SceneNode* headNode = mSmgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* ogreHead = mSmgr->createEntity("Head", "ogrehead.mesh");
    headNode->attachObject(ogreHead);
    headNode->setScale(0.2f, 0.2f, 0.2f);
    
    mSmgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    
    mSmgr->setSkyBox(true, "Test");
    
    Ogre::Light* light = mSmgr->createLight("Light");
    light->setPosition(20,80,50);
}

void GarnetApp::onClose() {
}
void GarnetApp::onTick() {
}


void GarnetApp::onKeyPress(const SDL_KeyboardEvent& event) {
    
}
void GarnetApp::onKeyRelease(const SDL_KeyboardEvent& event) {
    std::cout << "Key released" << std::endl;
}
}

