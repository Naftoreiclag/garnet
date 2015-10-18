#ifndef GRT_GARNETAPP_HPP
#define GRT_GARNETAPP_HPP

namespace grt
{

class GarnetApp
{
public:
    static GarnetApp& getSingleton();
    GarnetApp();
    ~GarnetApp();

};

}

#endif // GRT_GARNETAPP_HPP
