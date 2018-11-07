//
//  Toolkit.cpp
//  ToTheTop
//
//  Created by Eduardo Pérez on 05/10/18.
//

#include "Toolkit.h"
#include <math.h>

Toolkit *Toolkit::instance = NULL;

Toolkit *Toolkit::getInstance(){
    if (!instance){
        instance = new Toolkit;
    }    
    return instance;
}

int Toolkit::getAvailableSpaces(int height, int maxHeight, int level, GAME_DIFFICULTY difficulty) {
    int spaces = 2 - ((int) (1 * (level%10+(level/difficulty)))); //1~10, 1, 2, 3 y 5
    spaces -= (height<(maxHeight-1))?2:0;
    spaces = (spaces<0)?1:spaces;

    return height<maxHeight-1?spaces:0;
}

int Toolkit::getElementPerSpot(int scape_spaces, bool canBeEnded) {
    int length = 1; //this depends on which kind o blocks are availables
    int count = 0;
    length += canBeEnded?1:0;
    length += (scape_spaces>0)?scape_spaces:0;

    int *availableItems = new int[length+1];
    availableItems[count] = BLOCK_ITEM_MASK; count++;
    if(canBeEnded){availableItems[count] = STGCL_ITEM_MASK;count++;}
    for(int i=0;i<scape_spaces;i++){availableItems[count]=SPACE_ITEM_MASK;count++;}
    availableItems[count] = BLOCK_ITEM_MASK;

    int item = arc4random() % (length+1);
    return availableItems[item];
}

int** Toolkit::threatNoSpacePath(int **levelMap, int height, int width) {
    bool hasSpaceSpots = false;
    int space1,space2;
    
    for(int i=0;i<height-1;i++) {
        hasSpaceSpots = false;
        
        for(int j=0;j<width;j++){
            if (levelMap[i][j]==SPACE_ITEM_MASK){ //At least one
                hasSpaceSpots = true;
                break;
            }
        }
        
        if (!hasSpaceSpots) {
            do {
                space1 = arc4random() % width;
                space2 = arc4random() % width;
            }while(space2 == space1);
            
            levelMap[i][space1] = SPACE_ITEM_MASK;
            levelMap[i][space2] = SPACE_ITEM_MASK;
        }
    }
    
    return levelMap;
}

int** Toolkit::threatNoWinPath(int **levelMap, int height, int width) {
    bool hasWinSpace = false;
    for(int i=0;i<width;i++) {
        int bit = levelMap[height-1][i];
        if (bit == STGCL_ITEM_MASK) {
            hasWinSpace = true;
            break;
        }
    }
    
    if (!hasWinSpace) {
        int item = arc4random() % width;
        levelMap[height-1][item] = STGCL_ITEM_MASK;
    }
    
    return levelMap;
}

int** Toolkit::getLevelMap(int level,GAME_DIFFICULTY dif,struct PlayerHability hab) {
    int** levelMap = 0;
    int scapeSpots = 0;
    bool endSpot = false;

    //Calculate Height for the level
    int height = this->levelLength(LEVEL_BASE_HEIGHT, dif);
    this->actualMapHeight = height;

    //Instantiate basic objects
    levelMap = new int*[height];

    //Level Core Generation
    for(int h=0;h<height;h++) {
        levelMap[h] = new int[LEVEL_BASE_WIDTH];
        scapeSpots = this->getAvailableSpaces(h,height,level,dif);
        endSpot = (h==height-1);

        for(int w=0;w<LEVEL_BASE_WIDTH;w++) {
            int item = this->getElementPerSpot(scapeSpots,endSpot);
            if (item==SPACE_ITEM_MASK) scapeSpots = (scapeSpots<1)?scapeSpots:scapeSpots--;
            if (endSpot) endSpot = !(item==STGCL_ITEM_MASK);

            levelMap[h][w] = item;
            //printf("%d ",item);
        }
        //printf("\n");
    }
    
    this->threatNoSpacePath(levelMap,height,LEVEL_BASE_WIDTH);
    this->threatNoWinPath(levelMap,height,LEVEL_BASE_WIDTH);
    
    return levelMap;
}

int Toolkit::countSpacesInMap(int** levelMap) {
    int height = sizeof(levelMap);
    int count = 0;
    
    for(int i=0;i<height;i++) {
        for(int j=0;j<LEVEL_BASE_WIDTH;j++) {
            int byteMap = levelMap[i][j];
            if (byteMap != SPACE_ITEM_MASK ) {
                count++;
            }
        }
    }
    
    return count;
}

int Toolkit::levelLength(int base_height,GAME_DIFFICULTY dif) {
    int adjust = ceil(base_height*dif/10);
    int sizing = ((int)dif>(int)GAME_DIFFICULTY::_NORMAL)?floor(adjust%2):0;
    
    return  (base_height + adjust - sizing);
}

int Toolkit::getActualMapHeight() { return this->actualMapHeight; }


