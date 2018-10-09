//
//  GameObject.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

struct GOPosition {
    float xVal = 0;
    float yVal = 0;
};

struct GOAttributes {
    std::string name = "Generic Object";
    int points;
    bool isAlive = false;
    bool isPlayable = false;
    bool isCollidable = false;
    bool canInteract = false;
    bool canMove = false;
    bool canProvidePoints = false;
};

class GameObject {
protected:
    Sprite *sprite;
    struct GOPosition position;
    struct GOAttributes attributes;
public:
    struct GOPosition movement;
    virtual void move();
    virtual bool initWith(const std::string &sprite_name,struct GOAttributes attributes);
    struct GOAttributes getAttributes();
    void setInitialPosition(struct GOPosition);
    void setPosition(float x,float y);
    Sprite *getSprite();    
};
