//
//  GameObject.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "GameObject.h"

bool GameObject::initWith(const std::string &sprite, struct GOAttributes attributes) {
    this->attributes = attributes;
    this->sprite_name = sprite;
    
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

std::string GameObject::getSpriteKey() {
    return this->sprite_name;
}
