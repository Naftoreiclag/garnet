#include "OgreApp.hpp"

#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"
#include "OgreConfigFile.h"
#include "OgreWindowEventUtilities.h"
#include "OgreEntity.h"

#include "SDL.h"
#include "SDL_syswm.h"

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
    m_ogreRoot = new Ogre::Root("plugins.cfg");
    
    // Load resource config
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
    
    if(m_ogreRoot->restoreConfig() || m_ogreRoot->showConfigDialog()) {
        m_ogreRoot->initialise(false);

        SDL_Window* mSDLWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE);

        SDL_SysWMinfo sdlWindowInfo;
        SDL_VERSION(&sdlWindowInfo.version);
        SDL_GetWindowWMInfo(mSDLWindow, &sdlWindowInfo);
        
        Ogre::NameValuePairList ogreParams;
        #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        ogreParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.win.window));
        #elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        ogreParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.cocoa.window));
        #elif OGRE_PLATFORM == OGRE_PLATFORM_LINUX
        ogreParams["parentWindowHandle"] = Ogre::StringConverter::toString(size_t(sdlWindowInfo.info.x11.window));
        #endif
        m_window = m_ogreRoot->createRenderWindow("secret message for uubor haxurs", 1280, 720, false, &ogreParams);
    }
    else {
        return;
    }
    
    m_smgr = m_ogreRoot->createSceneManager(Ogre::ST_GENERIC);
    
    m_cam = m_smgr->createCamera("Camera");
    
    m_cam->setPosition(Ogre::Vector3(0, 0, 80));
    m_cam->lookAt(Ogre::Vector3(0, 0, -300));
    m_cam->setNearClipDistance(5);
    
    Ogre::Viewport* viewport = m_window->addViewport(m_cam);
    viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    
    m_cam->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
    
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    
    Ogre::SceneNode* headNode = m_smgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* ogreHead = m_smgr->createEntity("Head", "ogrehead.mesh");
    headNode->attachObject(ogreHead);
    headNode->setScale(0.2f, 0.2f, 0.2f);
    
    m_smgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    
    m_smgr->setSkyBox(true, "Test");
    
    Ogre::Light* light = m_smgr->createLight("Light");
    light->setPosition(20,80,50);
    
    Dollop dollop;
    dollop.updateMesh();
    
    while(true) {
        
        //headNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(1));
        headNode->translate(Ogre::Vector3(0, 0.01, 0));
        
        Ogre::WindowEventUtilities::messagePump();
        
        if(m_window->isClosed()) {
            break;
        }
        
        if(!m_ogreRoot->renderOneFrame()) {
            break;
        }
    }
}


}

