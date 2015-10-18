#include "OgreApp.hpp"

#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "OgreConfigFile.h"
#include "OgreWindowEventUtilities.h"
#include "OgreEntity.h"

#include "SDL.h"

#include "Nugget.hpp"
#include "Dollop.hpp"

#include <iostream>

namespace grt
{

OgreApp& OgreApp::getSingleton() {
    static OgreApp instance;
    return instance;
}
    
OgreApp::OgreApp() {
}

OgreApp::~OgreApp() {
}

void OgreApp::run() {
    mOgreRoot = new Ogre::Root("plugins.cfg");
    
    {
        Ogre::ConfigFile resCfg;
        resCfg.load("resources.cfg");
        Ogre::ConfigFile::SectionIterator sectionIterator = resCfg.getSectionIterator();
        
        while(sectionIterator.hasMoreElements()) {
            Ogre::String sectionName = sectionIterator.peekNextKey();
            Ogre::ConfigFile::SettingsMultiMap* sectionData = sectionIterator.getNext();
            Ogre::ConfigFile::SettingsMultiMap::iterator dataIterator;
            for(dataIterator = sectionData->begin(); dataIterator != sectionData->end(); ++ dataIterator) {
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataIterator->second, dataIterator->first, sectionName);
            }
        }
    }
    
    if(mOgreRoot->restoreConfig() || mOgreRoot->showConfigDialog()) {
        mOgreRoot->initialise(false);

        mSdlWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE);

        SDL_SysWMinfo sdlWindowInfo;
        SDL_VERSION(&sdlWindowInfo.version);
        SDL_GetWindowWMInfo(mSdlWindow, &sdlWindowInfo);
        
        Ogre::NameValuePairList ogreParams;
        #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        ogreParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.win.window));
        #elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        ogreParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.cocoa.window));
        #elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
        ogreParams["parentWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.x11.window));
        #endif
        mOgreWindow = mOgreRoot->createRenderWindow("secret message for uubor haxurs", 1280, 720, false, &ogreParams);
    }
    else {
        return;
    }
    
    SDL_ShowCursor(SDL_FALSE);
    SDL_SetWindowGrab(mSdlWindow, SDL_TRUE);
    
    mSmgr = mOgreRoot->createSceneManager(Ogre::ST_GENERIC);
    
    mCam = mSmgr->createCamera("Camera");
    
    mCam->setPosition(Ogre::Vector3(0, 0, 80));
    mCam->lookAt(Ogre::Vector3(0, 0, -300));
    mCam->setNearClipDistance(5);
    
    Ogre::Viewport* viewport = mOgreWindow->addViewport(mCam);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    
    mCam->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    
    Ogre::SceneNode* headNode = mSmgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* ogreHead = mSmgr->createEntity("Head", "ogrehead.mesh");
    headNode->attachObject(ogreHead);
    headNode->setScale(0.2f, 0.2f, 0.2f);
    
    mSmgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    
    mSmgr->setSkyBox(true, "Test");
    
    Ogre::Light* light = mSmgr->createLight("Light");
    light->setPosition(20,80,50);
    
    Dollop dollop;
    dollop.updateMesh();
    
    bool running = true;
    while(running) {
        
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: {
                    mOgreRoot->queueEndRendering();
                    running = false;
                    break;
                }
                default : {
                    break;
                }
            }
        }
        
        //headNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(1));
        headNode->translate(Ogre::Vector3(0, 0.01, 0));
        
        Ogre::WindowEventUtilities::messagePump();
        
        if(!mOgreRoot->renderOneFrame()) {
            break;
        }
    }
}


}

