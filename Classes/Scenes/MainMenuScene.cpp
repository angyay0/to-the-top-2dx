//
//  MainMenuScene.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//
// TODO: Agregar respuestas a clicks

#include "MainMenuScene.h"
#include "HelpScene.h"
#include "GameScene.h"

Scene *MainMenuScene::createScene() {
    Scene *scene = Scene::create();
    Layer *layer = MainMenuScene::create();
    //TODO: Agregar parallax scrolling effect
    //auto backgroundScroll;
    
    scene->addChild(layer);
    
    return scene;
}

bool MainMenuScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float scale = Director::getInstance()->getContentScaleFactor() / 2.0;
    
    //Elementos interactivos
    auto playMenuItem = MenuItemImage::create("play.png","play.png",CC_CALLBACK_1(MainMenuScene::onOptionSelectedCallback,this));
    playMenuItem->setTag( PLAY_TAG );
    auto trophyMenuItem = MenuItemImage::create("trophy.png","trophy.png",CC_CALLBACK_1(MainMenuScene::onOptionSelectedCallback,this));
    trophyMenuItem->setTag( TROPHY_TAG );
    auto helpMenuItem = MenuItemImage::create("help.png","help.png",CC_CALLBACK_1(MainMenuScene::onOptionSelectedCallback,this));
    helpMenuItem->setTag( HELP_TAG );
    
    //Titulo del juego
    auto gameTitle = Label::createWithTTF("To The Top", "fonts/Marker Felt.ttf",48);
    
    //Menu
    auto menu = Menu::create();
    menu->setPosition(Vec2(origin.x + viewPort.width/2, viewPort.height/2 + origin.y));
    
    //Posicionamiento de elementos
    gameTitle->setPosition(origin.x + (viewPort.width/2 ),
                           origin.y + viewPort.height - gameTitle->getContentSize().height);
    
    playMenuItem->setScale(scale);
    playMenuItem->setPosition(origin.x, origin.y - (playMenuItem->getContentSize().height/2));
    trophyMenuItem->setScale(scale);
    trophyMenuItem->setPosition( playMenuItem->getPosition().x + viewPort.width/2 - trophyMenuItem->getContentSize().width - 10, origin.y - (viewPort.height/2) + 10 );
    helpMenuItem->setScale(scale);
    helpMenuItem->setPosition( playMenuItem->getPosition().x - viewPort.width/2 + helpMenuItem->getContentSize().width + 10, origin.y - (viewPort.height/2) + 10  );
    
    //Creacion del menu con los elemtos para mostrar
    menu->addChild(playMenuItem);
    menu->addChild(trophyMenuItem);
    menu->addChild(helpMenuItem);
    
    //Agregar Elementos al layer
    this->addChild(menu,1);
    this->addChild(gameTitle,1);
    
    return true;
}

void MainMenuScene::onOptionSelectedCallback(Ref *pSender) {
    switch (((MenuItem*) pSender)->getTag()) {
        case PLAY_TAG:
            CCLOG("PLAY TAG");
            Director::getInstance()->pushScene(GameScene::createScene());
            break;
        case HELP_TAG:
            CCLOG("HELP TAG");
            Director::getInstance()->pushScene(HelpScene::createScene());
            break;
        case TROPHY_TAG:
            CCLOG("TROPHY TAG");
            break;
    }
}
