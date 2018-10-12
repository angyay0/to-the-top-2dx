//
//  GameObject.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;

bool GameObject::initWith(const std::string &sprite_name, struct GOAttributes attributes) {
    this->attributes = attributes;
    
    auto polinfo = AutoPolygon::generatePolygon(sprite_name);
    this->sprite = Sprite::create(polinfo);
    
    movement.xVal = 0.0f;
    movement.yVal = 0.0f;
    movement.zVal = 0.0f;
    
    return true;
}

struct GOAttributes GameObject::getAttributes() {
    return this->attributes;
}

struct GOSAttributes GameObject::getSpecialAttributes() {
    return this->specialAttributes;
}

void GameObject::setInitialPosition(struct GOPosition position) {
    this->setPosition(position.xVal, position.yVal);
}

void GameObject::setSpecialAttributes(struct GOSAttributes attributes) {
    this->specialAttributes = attributes;
}

void GameObject::setPosition(float x, float y) {
    this->position.xVal = x;
    this->position.yVal = y;
    
    this->sprite->setPosition(this->position.xVal,this->position.yVal);
}

void GameObject::move() {
    if (attributes.canMove) {
        switch(attributes.movementType){
            case 2://Rotation from Cero to 45 or -45 on same axis
                float rotation = movement.xVal*1.20;
                this->sprite->setRotation(rotation);
                break;
        }
    }
}

Sprite *GameObject::getSprite() {
    return this->sprite;
}
