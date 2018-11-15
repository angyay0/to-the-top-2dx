//
//  GameHUD.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "cocos2d.h"
#include "Player.h"
#include "Constants.h"
#include "ReactiveProtocols.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class GameHUD: public cocos2d::Layer {
private:
    Label *scoreLabel;
    Label *livesLabel;
    LoadingBar *lifeBar;
    GameHUDClickProtocol *clickHandler;
protected:
    Player *player;
public:
    virtual bool init();
    void setupPlayer(Player *player);
    bool setupView();
    void setupInteractions(GameHUDClickProtocol *handler);
    void updateValues(float dt);
    
    void onClick(Ref *pSender);
    
    CREATE_FUNC(GameHUD);
};
