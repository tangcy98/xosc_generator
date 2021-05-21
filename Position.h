#ifndef _POSITION_
#define _POSITION_

enum POSITIONTYPE {
    WORLD,
    LANE,
};

struct WorldPosition {
    std::string x;
    std::string y;
    std::string z;
    std::string h;
};

struct LanePosition {
    std::string roadId;
    std::string laneId;
    std::string offset;
    std::string s;
};

struct Position {
    POSITIONTYPE  positiontype;
    WorldPosition worldPosition;
    LanePosition  lanePosition;
};

#endif