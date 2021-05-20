#ifndef _ENVIRONMENT_
#define _ENVIRONMENT_

#include "common.h"

struct Environment {
    const char *name;
    const char *animation;
    const char *dateTime;
    const char *cloudState;
    const char *sunintensity;
    const char *azimuth;
    const char *elevation;
    const char *visualRange;
    const char *precipitationType;
    const char *precipitationintensity;
    const char *frictionScaleFactor;
    Environment(
        const char *iname = NULL,
        const char *ianimation = NULL,
        const char *idateTime = NULL,
        const char *icloudState = NULL,
        const char *isunintensity = NULL,
        const char *iazimuth = NULL,
        const char *ielevation = NULL,
        const char *ivisualRange = NULL,
        const char *iprecipitationType = NULL,
        const char *iprecipitationintensity = NULL,
        const char *ifrictionScaleFactor = NULL
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