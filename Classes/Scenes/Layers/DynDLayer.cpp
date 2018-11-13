//
//  DynDLayer.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 10/10/18.
//

#include "DynDLayer.h"
#include "Constants.h"

bool DynDLayer::init() {
    return LayerColor::initWithColor(Color4B(0,0,0,255));
}

void DynDLayer::setupFor(DDLayerType type,std::string data[]) {
    this->type = type;
    
    switch (type) {
        case _PauseLayer:
            CCLOG("Pause");
            this->configurePause();
            break;
        case _GameOverLayer:
            CCLOG("Game Over");
            this->configureGOver();
            break;
        case _WinLayer:
            CCLOG("Winner");
           // this->configureWinner();
            break;
        default:
            CCLOG("General");
            break;
    }
}

void DynDLayer::configurePause(){
    Size viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float scale = Director::getInstance()->getContentScaleFactor()/2.f;
    
    auto playMenuItem = MenuItemImage::create("play.png","play.png",CC_CALLBACK_1(DynDLayer::onClick, this));
    playMenuItem->setTag(PLAY_TAG);
    playMenuItem->setScale(scale);
    
    auto homeMenuItem = MenuItemImage::create("home.png","home.png",CC_CALLBACK_1(DynDLayer::onClick, this));
    homeMenuItem->setTag(HOME_TAG);
    homeMenuItem->setScale(scale);
    
    auto someMenuItem = MenuItemImage::create("help.png","help.png",CC_CALLBACK_1(DynDLayer::onClick, this));
    someMenuItem->setTag(HELP_TAG);
    someMenuItem->setScale(scale);
    
    auto pauseTitle = Label::createWithTTF("PAUSED", "fonts/Marker Felt.ttf", 36);
    
    auto menu = Menu::create();
    menu->setPosition(Vec2(origin.x + viewPort.width/2.f,origin.y + viewPort.height/2.f));
    
    pauseTitle->setPosition(origin.x + viewPort.width/2.f,origin.y + viewPort.height - pauseTitle->getContentSize().height);
    
    playMenuItem->setPosition(origin.x, origin.y - (playMenuItem->getContentSize().height/2));
    
    homeMenuItem->setPosition( playMenuItem->getPosition().x + viewPort.width/2 - homeMenuItem->getContentSize().width - 10, origin.y - (viewPort.height/2) + 10 );
    
    someMenuItem->setPosition( playMenuItem->getPosition().x - viewPort.width/2 + someMenuItem->getContentSize().width + 10, origin.y - (viewPort.height/2) + 10  );
    
    menu->addChild(playMenuItem);
    menu->addChild(homeMenuItem);
    menu->addChild(someMenuItem);
    
    this->addChild(menu, 1);
    this->addChild(pauseTitle, 1);
    this->setTag(DYNLAYER_TAG);
    this->setScale(0.65f);
}

void DynDLayer::configureGOver(){
    Size viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float scale = Director::getInstance()->getContentScaleFactor()/2.f;
    
    auto playMenuItem = MenuItemImage::create("play.png","play.png",CC_CALLBACK_1(DynDLayer::onClick, this));
    playMenuItem->setTag(PLAY_TAG);
    playMenuItem->setScale(scale);
    
    auto homeMenuItem = MenuItemImage::create("home.png","home.png",CC_CALLBACK_1(DynDLayer::onClick, this));
    homeMenuItem->setTag(HOME_TAG);
    homeMenuItem->setScale(scale);
    
    auto someMenuItem = MenuItemImage::create("help.png","help.png",CC_CALLBACK_1(DynDLayer::onClick, this));
    someMenuItem->setTag(HELP_TAG);
    someMenuItem->setScale(scale);
    
    auto pauseTitle = Label::createWithTTF("You Lose", "fonts/Marker Felt.ttf", 36);
    
    auto menu = Menu::create();
    menu->setPosition(Vec2(origin.x + viewPort.width/2.f,origin.y + viewPort.height/2.f));
    
    pauseTitle->setPosition(origin.x + viewPort.width/2.f,origin.y + viewPort.height - pauseTitle->getContentSize().height);
    
    playMenuItem->setPosition(origin.x, origin.y - (playMenuItem->getContentSize().height/2));
    
    homeMenuItem->setPosition( playMenuItem->getPosition().x + viewPort.width/2 - homeMenuItem->getContentSize().width - 10, origin.y - (viewPort.height/2) + 10 );
    
    someMenuItem->setPosition( playMenuItem->getPosition().x - viewPort.width/2 + someMenuItem->getContentSize().width + 10, origin.y - (viewPort.height/2) + 10  );
    
    menu->addChild(playMenuItem);
    menu->addChild(homeMenuItem);
    menu->addChild(someMenuItem);
    
    this->addChild(menu, 1);
    this->addChild(pauseTitle, 1);
    this->setTag(DYNLAYER_TAG);
    this->setScale(0.65f);
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
