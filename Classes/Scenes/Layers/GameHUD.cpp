//
//  GameHUD.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "GameHUD.h"
#include <sstream>

bool GameHUD::init() {
    if (!Layer::init()) {
        return false;
    }
    
    return this->setupView();
}

bool GameHUD::setupView() {
    Size viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    float topPadding = 15;
    Menu *menu = Menu::create();
    
    MenuItemImage *pauseMenuItem = MenuItemImage::create("CloseNormal.png",
                                                         "CloseSelected.png",
                                                         CC_CALLBACK_1(GameHUD::onClick, this));
    pauseMenuItem->setScale(1.1);
    pauseMenuItem->setTag(PAUSE_TAG);
    pauseMenuItem->setPosition(origin.x, origin.y - 5);
    
    this->scoreLabel = Label::createWithTTF("000000000", "fonts/Marker Felt.ttf", 20);
    Label *label1 = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 20);
    this->scoreLabel->setPosition(origin.x + viewPort.width - this->scoreLabel->getContentSize().width/2 - 5, origin.y + viewPort.height - topPadding);
    label1->setPosition(this->scoreLabel->getPosition().x - scoreLabel->getContentSize().width + topPadding, this->scoreLabel->getPosition().y);
    
    this->livesLabel = Label::createWithTTF("4", "fonts/Marker Felt.ttf", 20);
    Label *label2 = Label::createWithTTF("Lives:", "fonts/Marker Felt.ttf", 20);
    label2->setPosition(label2->getContentSize().width - topPadding, origin.y + viewPort.height - topPadding);
    this->livesLabel->setPosition(label2->getPosition().x + label2->getContentSize().width - 5, label2->getPosition().y);
    
    //Life Indicator
    Sprite *heart = Sprite::create("health_icon.png");
    heart->setPosition(Vec2(origin.x+heart->getContentSize().width,label2->getPosition().y-20));
    
    this->lifeBar = LoadingBar::create("slider_health.png");
    this->lifeBar->setCapInsets(Rect(0,0,0,0));
    this->lifeBar->setScale9Enabled(true);
    this->lifeBar->setContentSize(Size(100,10));
    this->lifeBar->setPosition(Vec2(80,label2->getPosition().y-20));
    this->lifeBar->setPercent(100);
    
    
    menu->setPosition(origin.x + viewPort.width/2, origin.y - pauseMenuItem->getContentSize().height   + viewPort.height - topPadding);
    
    //Add To Menu
    menu->addChild(pauseMenuItem);
    
    //Add to View
    this->addChild(menu);
    this->addChild(label1);
    this->addChild(label2);
    this->addChild(this->scoreLabel);
    this->addChild(this->livesLabel);
    this->addChild(this->lifeBar);
    this->addChild(heart);
    
    //Configure Tag
    this->setTag(HUD_TAG);
    
    
    return true;
}

void GameHUD::onClick(Ref *pSender) {
    CCLOG("GHud Resolver");
    if (clickHandler) {
        clickHandler->onHUDItemClickedCallback(pSender);
    }
}

void GameHUD::setupInteractions(GameHUDClickProtocol *handler) {
    this->clickHandler = handler;
}

void GameHUD::setupPlayer(Player *player) {
    this->player = player;
    this->updateValues(0.f);
}

void GameHUD::updateValues(float dt) {
    std::stringstream streamer;
    streamer << this->player->getScore();
    this->scoreLabel->setString(streamer.str());
    streamer.str("");
    
    int lives = this->player->getLives();
    streamer << lives;
    this->livesLabel->setString(streamer.str());
    streamer.flush();
    
    GOSAttributes special = player->getSpecialAttributes();
    
    float perc = player->getCurrentHealth()*100.f/(special.health*special.resistance);
    this->lifeBar->setPercent(perc);
    
    this->update(dt);
}
