#include "GarnetApp.hpp"

namespace grt
{
    
GarnetApp& GarnetApp::getSingleton() {
    static GarnetApp instance;
    return instance;
}

GarnetApp::GarnetApp()
{
}

GarnetApp::~GarnetApp()
{
}


}

