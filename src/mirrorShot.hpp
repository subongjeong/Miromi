//
//  mirrorShot.hpp
//  Miromi
//
//  Created by Subong Jeong on 2018. 7. 9..
//

#ifndef mirrorShot_hpp
#define mirrorShot_hpp

#include "ofMain.h"

enum{
    READY = -1,
    CHEESE = 0,
    COUNT,
    STILL,
    FRAME,
    PRINT
};

class mirrorShot : public ofBaseApp{
public:
    mirrorShot();
    void update();
    void draw();
    void setTime(int sec);
    void setShotCount(int cnt);
    
    void sayCheese();
    void print();
    bool getProcessDone();
    
    ofVideoGrabber camera;
    
    ofImage image_cheese;
    ofImage image_count[5];
    
    ofFbo fboCut[2];
    ofFbo fboFrame;
    ofPixels pixels;
    
    
    int shotMode;
    
    int cheeseTime;
    int stillTime;
    int printTime;
    int prevTime;
    
    bool isShot;
    bool isDone;
    
    int shotCount;
    int shotCountMax;
};

#endif /* mirrorShot_hpp */
