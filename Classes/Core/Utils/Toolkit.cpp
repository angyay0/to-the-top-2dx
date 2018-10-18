//
//  Toolkit.cpp
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "Toolkit.h"

Toolkit *Toolkit::instance = NULL;

Toolkit *Toolkit::getInstance(){
    if (!instance){
        instance = new Toolkit;
    }    
    return instance;
}

int** Toolkit::getLevelMap(float level,GAME_DIFFICULTY dif,struct PlayerHability hab) {
    int** levelMap = 0;
    int height = LEVEL_BASE_HEIGHT;
    levelMap = new int*[height];
    //TODO
    for(int c=0;c<height;c++) {
        levelMap[c] = new int[LEVEL_BASE_WIDTH];
        for(int w=0;w<LEVEL_BASE_WIDTH;w++) {
            levelMap[c][w] = BLOCK_ITEM_MASK;
        }
    }
    
    return levelMap;
}
