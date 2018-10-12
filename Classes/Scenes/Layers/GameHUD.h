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

USING_NS_CC;

class GameHUD: public cocos2d::Layer {
private:
    Label *scoreLabel;
    Label *livesLabel;
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
