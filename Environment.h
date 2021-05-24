#ifndef _ENVIRONMENT_
#define _ENVIRONMENT_

#include "common.h"

struct Environment {
    std::string name;
    std::string animation;
    std::string dateTime;
    std::string cloudState;
    std::string sunintensity;
    std::string azimuth;
    std::string elevation;
    std::string visualRange;
    std::string precipitationType;
    std::string precipitationintensity;
    std::string frictionScaleFactor;
    Environment(
        std::string iname = "",
        std::string ianimation = "",
        std::string idateTime = "",
        std::string icloudState = "",
        std::string isunintensity = "",
        std::string iazimuth = "",
        std::string ielevation = "",
        std::string ivisualRange = "",
        std::string iprecipitationType = "",
        std::string iprecipitationintensity = "",
        std::string ifrictionScaleFactor = ""
    ) {
        name = iname;
        animation = ianimation;
        dateTime = idateTime;
        cloudState = icloudState;
        sunintensity = isunintensity;
        azimuth = iazimuth;
        elevation = ielevation;
        visualRange = ivisualRange;
        precipitationType = iprecipitationType;
        precipitationintensity = iprecipitationintensity;
        frictionScaleFactor = ifrictionScaleFactor;
    };
};


#endif