#ifndef _POSITION_
#define _POSITION_

enum POSITIONTYPE {
    WORLD,
    LANE,
};

struct WorldPosition {
    const char *x;
    const char *y;
    const char *z;
    const char *h;
};

struct LanePosition {
    const char *roadId;
    const char *laneId;
    const char *offset;
    const char *s;
};

struct Position {
    POSITIONTYPE  positiontype;
    WorldPosition worldPosition;
    LanePosition  lanePosition;
};

#endif