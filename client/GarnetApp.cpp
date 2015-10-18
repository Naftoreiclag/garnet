#include "GarnetApp.hpp"

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

void GarnetApp::initialize(Ogre::Root* ogreRoot) {
    mOgreRoot = ogreRoot;
}

void GarnetApp::onClose() {
}
void GarnetApp::onTick() {
}

}

