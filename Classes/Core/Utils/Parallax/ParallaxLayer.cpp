//
//  ParallaxLayer.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "ParallaxLayer.h"
#include "cocos2d.h"

USING_NS_CC;

class PointObject: public Ref{
public:
    inline void setRation(Point ratio) {_ratio = ratio;}
    inline void setOffset(Point offset) {_offset = offset;}
    inline void setChild(Node *var) {_child = var;}
    inline Point getOffset() const {return _offset;}
    inline Node* getChild() const {return _child;}
private:
    Point _ratio;
    Point _offset;
    Node* _child;
};

ParallaxLayer* ParallaxLayer::create()
{
    // Create an instance of InfiniteParallaxNode
    ParallaxLayer *node = new ParallaxLayer();
    if(node) {
        // Add it to autorelease pool
        node->autorelease();
    } else {
        // Otherwise delete
        delete node;
        node = 0;
    }
    return node;
}

void ParallaxLayer::updateLayer(){
    int safeOffset = -10;
    // Get visible size
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 1. For each child of an parallax node
    for(int i = 0; i < _children.size(); i++){
        auto node = _children.at(i);
        // 2. We check whether it is out of the left side of the visible area
        if(convertToWorldSpace(node->getPosition()).x + node->getContentSize().width < safeOffset){
            // 3. Find PointObject that corresponds to current node
            for(int i = 0; i < _parallaxArray->num; i++) {
                auto po = (PointObject*)_parallaxArray->arr[i];
                // If yes increase its current offset on the value of visible width
                if(po->getChild() == node)
                    po->setOffset(po->getOffset() +
                                  Point((visibleSize.width*1.6) + node->getContentSize().width,0));
            }
        }
    }
}

void ParallaxLayer::setupMovementFactor(float bg_min_spd,float bg_max_spd,float min_factor_spd,float max_factor_spd,float factor,float distance,int orientation) {
    this->bg_min_spd = bg_min_spd;
    this->bg_max_spd = bg_max_spd;
    this->min_factor_spd = min_factor_spd;
    this->max_factor_spd = max_factor_spd;
    this->pfactor = factor;
    this->pdistance = distance;
    this->orientation = orientation;
    
    point = cocos2d::Point(bg_min_spd,bg_max_spd);
}

cocos2d::Point ParallaxLayer::getPointSpeed(){
    return point;
}

void ParallaxLayer::move(float dt) {
    
}

void ParallaxLayer::setupBehavior(bool remove, bool stop) {
    this->removeAfterRoll = true;
    this->stopAtEndRoll = true;
}
