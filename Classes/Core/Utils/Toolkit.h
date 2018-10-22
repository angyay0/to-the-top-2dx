//
//  Toolkit.h
//  ToTheTop-mobile
//
//  Created by Eduardo Pérez on 05/10/18.
//

#ifndef Toolkit_h
#define Toolkit_h

#include <stdio.h>
#include "Constants.h"

class Toolkit {
private:
    Toolkit(){};
    Toolkit(Toolkit const&){};
    Toolkit& operator = (Toolkit const&){};
    static Toolkit *instance;

    //Methods for level generator
    int getAvailableSpaces(int height,int maxHeight,int level,GAME_DIFFICULTY difficulty);
    int getElementPerSpot(int scape_spaces,bool canBeEnded);
    void threatNoSpacePath(int **levelMap,int height,int width);
    void threatNoWinPath(int **levelMap,int height,int width);
public:
    static Toolkit *getInstance();
    int** getLevelMap(int level,GAME_DIFFICULTY dif,struct PlayerHability hab);
};
#endif /* Toolkit_h */
