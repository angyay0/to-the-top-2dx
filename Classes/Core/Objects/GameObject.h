//
//  GameObject.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#ifndef GameObject_h
#define GameObject_h

#include <stdio.h>
#include "cocos2d.h"

//Tags for GameObjects
#define OBJECT_TAG 0
#define PLAYER_TAG 1
#define SPECIAL_OBJECT_TAG 2
#define BONUS_OBJECT_TAG 3

//Object Category Mask
#define STATIC_OBJECT 0x01
#define PLAYABLE_OBJECT 0x02
#define MOVABLE_OBJECT 0X03
#define INTERACTIVE_OBJECT 0X04

USING_NS_CC;

struct GOPosition {
    float xVal = 0;
    float yVal = 0;
    float zVal = 0;
};

struct GOAttributes {
    std::string name = "Generic Object";
    int points;
    int movementType = -1;
    bool isAlive = false;
    bool isPlayable = false;
    bool isCollidable = false;
    bool canInteract = false;
    bool canMove = false;
    bool canProvidePoints = false;
    bool hasSpecialAttributes = false;
};

struct GOSAttributes { //TBD
    bool hasInmmunity = false;
    int materialType = 0;
    float resistance = 1.0;
    float health = 1.0;
};

class GameObject {
protected:
    bool movementFirstTime;
    Sprite *sprite;
    struct GOPosition position;
    struct GOAttributes attributes;
    struct GOSAttributes specialAttributes;
public:
    struct GOPosition movement;
    virtual void move();
    virtual bool initWith(const std::string &sprite_name,struct GOAttributes attributes);
    virtual bool initWith(const std::string &sprite_name,struct GOAttributes attributes,float pBW,float pBH);
    virtual bool initWith(SpriteFrame *frame,struct GOAttributes attributes,int physicsShape);
    virtual void setExtras(float scale,bool drawAnchor,Size newSize,Vec2 anchor);
    struct GOAttributes getAttributes();
    struct GOSAttributes getSpecialAttributes();
    void setInitialPosition(struct GOPosition);
    void setSpecialAttributes(struct GOSAttributes);
    void setPosition(float x,float y);
    void isFirstTimeMove(bool val);
    Sprite *getSprite();    
};
#endif
