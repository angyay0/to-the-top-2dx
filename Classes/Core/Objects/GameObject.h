//
//  GameObject.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include <stdio.h>

struct GOPosition {
    float xVal = 0;
    float yVal = 0;
};

struct GOAttributes {
    std::string name = "GOGeneric";
    bool isAlive = false;
    bool isPlayable = false;
    bool canInteract = false;
    bool canMove = false;
};

class GameObject {
protected:
    std::string sprite_name;
    struct GOPosition position;
    struct GOAttributes attributes;
public:
    struct GOPosition movement;
    virtual bool initWith(const std::string &sprite,struct GOAttributes attributes);
    struct GOAttributes getAttributes();
    void setInitialPosition(struct GOPosition);
    void setPosition(float x,float y);
    std::string getSpriteKey();
    void move();
};
