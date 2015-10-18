#ifndef GRT_GARNETAPP_HPP
#define GRT_GARNETAPP_HPP

#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"

#include "SDL_events.h"

namespace grt
{

class GarnetApp
{
public:
    static GarnetApp& getSingleton();
public:
    Ogre::Root* mOgreRoot;
    Ogre::Camera* mCam;
    Ogre::SceneManager* mSmgr;
    
    void initialize(Ogre::Root* ogreRoot, Ogre::RenderWindow* ogreWindow);
    
    // User wants to close application
    void onClose();
    
    // Ticks
    void onTick();
    
    // Key handling
    void onKeyPress(const SDL_KeyboardEvent& event);
    void onKeyRelease(const SDL_KeyboardEvent& event);
    
    // Mouse handling
    void onMouseMove(const SDL_MouseMotionEvent& event);
    void onMousePress(const SDL_MouseButtonEvent& event);
    void onMouseRelease(const SDL_MouseButtonEvent& event);
    
    GarnetApp();
    ~GarnetApp();
};

}

#endif // GRT_GARNETAPP_HPP
