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
    this->sprite->setAnchorPoint(Vec2(0.5,0.5));
    
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
    if (attributes.canMove & !movementFirstTime) {
        switch(attributes.movementType){
            case 2://Rotation from Cero to 45 or -45 on same axis 1.22 is Cero
                float rotation = (movement.xVal-1.22)*10.20;
                if (rotation < 0){
                    if (rotation < -45) {
                        rotation = -45;
                    }
                } else {
                    if (rotation > 45) {
                        rotation = 45;
                    }
                }
                this->sprite->setRotation(rotation);
                break;
        }
    }
}

Sprite *GameObject::getSprite() {
    return this->sprite;
}

void GameObject::isFirstTimeMove(bool val) {
    this->movementFirstTime = val;
}
