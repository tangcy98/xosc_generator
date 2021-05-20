#ifndef _COMMON_
#define _COMMON_
#include <cstddef>
#include <vector>
#include <utility>

struct Parameter {
    const char *name;
    const char *parameterType;
    const char *value;
};

enum SETRES {
	SET_ERROR = 0,
	SET_OK,
	SET_NOPREREQUISITE,
};


#endif