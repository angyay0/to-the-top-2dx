//
//  DynDLayer.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 10/10/18.
//

#include "DynDLayer.h"

bool DynDLayer::init() {
    return Layer::init();
}

void DynDLayer::setupFor(DDLayerType type) {
    this->type = type;
    
    Size viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    switch (type) {
        case _PauseLayer:
            CCLOG("THIS THING");
            break;
            
        default:
            break;
    }
}

void DynDLayer::updateDyDLayer(float dt) {
    //TODO
    this->update(dt);
}

void DynDLayer::setupInteraction(DyDClickProtocol *handler) {
    this->clickHandler = handler;
}

void DynDLayer::onClick(Ref *pSender) {
    CCLOG("DynD Resolver");
    if (clickHandler) {
        clickHandler->onDyItemClickedCallback(pSender);
    }
}
