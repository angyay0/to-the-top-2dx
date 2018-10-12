//
//  HelpScene.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "HelpScene.h"

Scene *HelpScene::createScene(){
    Scene *scene = Scene::create();
    Layer *layer = HelpScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool HelpScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size viewPort = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float scale = Director::getInstance()->getContentScaleFactor() / 2.0;
    
    //Instancia de elementos
    //Menu
    auto menu = Menu::create();
    menu->setPosition(Vec2(viewPort.width/2 + origin.x, viewPort.height/2 + origin.y));
    //Boton Back
    auto backMenuItem = MenuItemImage::create("back.png","back.png",
                                              CC_CALLBACK_1(HelpScene::onOptionSelectedCallback, this));
    backMenuItem->setTag( BACK_TAG );
    //Boton para ir a landing
    auto webMenuItem = MenuItemImage::create("web.png","web.png",
                                             CC_CALLBACK_1(HelpScene::onOptionSelectedCallback, this));
    webMenuItem->setTag( PLAY_TAG );
    
    //Titulo del layer
    auto layerTitle = Label::createWithTTF("HELP", "fonts/Marker Felt.ttf",42);
    
    //Descricion del la ayuda
    auto helpLabel = Label::createWithTTF("Controls:\n\nMovement: Accelerometer up/down/right/left\n", "fonts/Marker Felt.ttf", 20);
    helpLabel->enableShadow();
    
    //Posiciones de los elementos
    layerTitle->setPosition(origin.x + (viewPort.width / 2 ),
                            origin.y + viewPort.height - layerTitle->getContentSize().height);
    
    helpLabel->setPosition(viewPort.width/2 + origin.x, viewPort.height/2 + origin.y);
    
    backMenuItem->setScale(scale);
    backMenuItem->setPosition(origin.x - (viewPort.width/2) + backMenuItem->getContentSize().width,
                              origin.y + viewPort.height/2 - (backMenuItem->getContentSize().height * scale) - 10 );
    
    webMenuItem->setScale(scale);
    webMenuItem->setPosition(origin.x,origin.y - viewPort.height/2 + webMenuItem->getContentSize().height/2);
    
    
    menu->addChild(backMenuItem);
    menu->addChild(webMenuItem);
    
    this->addChild(layerTitle,1);
    this->addChild(helpLabel,1);
    this->addChild(menu,1);
    return true;
}

void HelpScene::onOptionSelectedCallback(Ref *pSender){
    switch (((MenuItem*) pSender)->getTag()) {
        case BACK_TAG:
            CCLOG("BACK TAG");
            Director::getInstance()->popScene();
            break;
        case PLAY_TAG:
            CCLOG("WEB TAG");
            Application::getInstance()->openURL("http://aimos-studio.com.mx/angelperez/space");
            break;
    }
}
