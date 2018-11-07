//
//  GameObject.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "cocos2d.h"
#include "GameObject.h"
#include "Constants.h"

USING_NS_CC;

bool GameObject::initWith(SpriteFrame *frame,struct GOAttributes attributes) {
    this->attributes = attributes;
    
    sprite = Sprite::createWithSpriteFrame(frame);
    PhysicsBody *body = PhysicsBody::createEdgeBox(sprite->getContentSize());
    body->setDynamic(false);
    sprite->addComponent(body);
    
    movement.xVal = 0.0f;
    movement.yVal = 0.0f;
    movement.zVal = 0.0f;
    
    return true;
}

bool GameObject::initWith(const std::string &sprite_name,struct GOAttributes attributes) {
    this->attributes = attributes;
    
    auto polinfo = AutoPolygon::generatePolygon(sprite_name);
    sprite = Sprite::create(polinfo);
    auto physicsBody = PhysicsBody::createEdgeBox(sprite->getContentSize());
    physicsBody->setDynamic(false);
    sprite->addComponent(physicsBody);
    movement.xVal = 0.0f;
    movement.yVal = 0.0f;
    movement.zVal = 0.0f;
    
    return true;
}

bool GameObject::initWith(const std::string &sprite_name,struct GOAttributes attributes,float pBW,float pBH) {
    this->attributes = attributes;
    
    auto polinfo = AutoPolygon::generatePolygon(sprite_name);
    sprite = Sprite::create(polinfo);
    PhysicsBody *body;
    
    if (pBW<0) {
        body = PhysicsBody::createEdgeBox(Size(sprite->getContentSize().width,pBH));
        body->setPositionOffset(Vec2(0,pBH));
    } else {
        body = PhysicsBody::createEdgeBox(Size(pBW,pBH));
    }
    
    body->setDynamic(false);
    sprite->addComponent(body);
    movement.xVal = 0.0f;
    movement.yVal = 0.0f;
    movement.zVal = 0.0f;
    
    return true;
}

bool GameObject::initWith(SpriteFrame *frame,struct GOAttributes attributes,float pBW,float pBH) {
    this->attributes = attributes;
    
    sprite = Sprite::createWithSpriteFrame(frame);
    PhysicsBody *body;
    
    if (pBW<0) {
        body = PhysicsBody::createEdgeBox(Size(sprite->getContentSize().width,pBH));
        body->setPositionOffset(Vec2(0,sprite->getContentSize().height/2-pBH));
    } else {
        body = PhysicsBody::createEdgeBox(Size(pBW,pBH));
    }
    
    body->setDynamic(false);
    sprite->addComponent(body);
    movement.xVal = 0.0f;
    movement.yVal = 0.0f;
    movement.zVal = 0.0f;
    
    return true;
}

bool GameObject::initWith(SpriteFrame *frame,struct GOAttributes attributes,int physicsShape) {
    this->attributes = attributes;
    
    sprite = Sprite::createWithSpriteFrame(frame);
    PhysicsBody *body;
    
    switch(physicsShape){
        case 1://box
            body = PhysicsBody::createEdgeBox(sprite->getContentSize());
            break;
        case 2://Circle
            body = PhysicsBody::createCircle(sprite->getContentSize().width/2);
            break;
        case 3://Triangles->TODO
            body = PhysicsBody::createEdgeBox(sprite->getContentSize());
            break;
            
    }
    
    body->setDynamic(false);
    sprite->addComponent(body);
    sprite->setAnchorPoint(Vec2(0.5,0.5));
    movement.xVal = 0.0f;
    movement.yVal = 0.0f;
    movement.zVal = 0.0f;
    
    return true;
}

void GameObject::setExtras(float scale, bool drawAnchor, Size newSize, Vec2 anchor){
    sprite->setScale(scale);
    
    if (newSize.width > 0 && newSize.height > 0) {
        sprite->setContentSize(newSize);
        sprite->setAnchorPoint(anchor);
    }
    
    if (drawAnchor) {
        DrawNode *point = DrawNode::create();
        point->drawDot(Point(newSize.width*sprite->getAnchorPoint().x,newSize.height*sprite->getAnchorPoint().y),2, Color4F(1.0,0.0,0.0,1.0));
        sprite->addChild(point);
    }
}

struct GOAttributes GameObject::getAttributes() {
    return this->attributes;
}

struct GOSAttributes GameObject::getSpecialAttributes() {
    return this->specialAttributes;
}

struct GOPosition GameObject::getPosition() {
    return this->position;
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

Sprite* GameObject::getSprite() {
    return this->sprite;
}

void GameObject::isFirstTimeMove(bool val) {
    this->movementFirstTime = val;
}

GOAttributes GameObject::getBlockBaseAttributes() {
    GOAttributes attributes;
    attributes.points = 10;
    attributes.isCollidable = true;
    attributes.canProvidePoints = true;    
    return attributes;
}

