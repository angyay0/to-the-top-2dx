//
//  Player.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "Player.h"
#include "cocos2d.h"

void Player::setScore(long score) {
    this->score = score;
}

void Player::setLives(int lives) {
    this->lives = lives;
}

void Player::setDistance(long distance) {
    this->distance = distance;
}

void Player::setDefaults() {
    this->score = 0;
    this->lives = 3;
    this->distance = 0;
    
    this->sprite->setTag(PLAYER_TAG);
}

long Player::getScore() {
    return score;
}

int Player::getLives() {
    return lives;
}

long Player::getDistance() {
    return distance;
}

void Player::moveXAxis(float min, float max, float dt) {
    float scviewport = Director::getInstance()->getContentScaleFactor()/2;
    float sizeConstant = (this->getSprite()->getContentSize().width * scviewport)/2;
    float diff = this->movement.xVal * dt;
    float newX = this->getSprite()->getPosition().x + diff;
    max -= sizeConstant;
    min += sizeConstant;
    
    newX = MIN(MAX(newX,min), max);
    
    this->setPosition(newX, this->getSprite()->getPosition().y);
}

void Player::moveYAxis(float min, float max, float dt) {
    float scviewport = Director::getInstance()->getContentScaleFactor()/2;
    float sizeConstant = (this->getSprite()->getContentSize().height * scviewport)/2;
    float diff = this->movement.yVal * dt;
    float newY = this->getSprite()->getPosition().y + diff;
    max -= sizeConstant;
    min += sizeConstant;
    
    newY = MIN(MAX(newY,min), max);
    
    this->setPosition(this->getSprite()->getPosition().x, newY);
}
