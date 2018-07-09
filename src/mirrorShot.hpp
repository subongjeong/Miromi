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
    STILL
};

class mirrorShot : public ofBaseApp{
public:
    mirrorShot();
    void update();
    void draw();
    void sayCheese();
    void setTime(int sec);
    
    ofVideoGrabber camera;
    
    ofImage image_cheese;
    ofImage image_count[5];
    
    int shotMode;
    int delayTime;
    int prevTime;
};

#endif /* mirrorShot_hpp */
