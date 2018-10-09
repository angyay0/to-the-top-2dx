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
    
    return true;
}

struct GOAttributes GameObject::getAttributes() {
    return this->attributes;
}

void GameObject::setInitialPosition(struct GOPosition position) {
    this->position = position;
}

void GameObject::setPosition(float x, float y) {
    this->position.xVal = x;
    this->position.yVal = y;
}

void GameObject::move() {
    
    if (attributes.canMove) {
        //TODO: Movement Algorithm
    }
}

Sprite *GameObject::getSprite() {
    return this->sprite;
}
