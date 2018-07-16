//
//  mirrorShot.hpp
//  Miromi
//
//  Created by Subong Jeong on 2018. 7. 9..
//

#ifndef mirrorShot_hpp
#define mirrorShot_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

#define CUT 2

enum{
    READY = -1,
    CHEESE = 0,
    COUNT,
    STILL,
    MESSAGE,
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
    
//    void setPreviewPosition(int _x, int _y, int _w, int _h);
//    void setFramePositionLeft(int _x, int _y, int _w, int _h);
//    void setFramePositionRight(int _x, int _y, int _w, int _h);

    
    void sayCheese();
    void print();
    bool getProcessDone();
    
    ofVideoGrabber camera;
    
    ofVideoPlayer vid_sayCheese;
    ofVideoPlayer vid_countdown;
    ofVideoPlayer vid_preview;
    ofVideoPlayer vid_message[CUT];
    ofVideoPlayer vid_print;
    //ofImage image_cheese;
    //ofImage image_count[5];
    
    ofDirectory dirFrame;
    vector<ofImage> image_frame;
    
    ofFbo fboCut[CUT];
    ofFbo fboFrame;
    ofPixels pixels;
    
    
    int shotMode;
    
    int cheeseTime;
    int stillTime;
    int printTime;
    int prevTime;
    
    bool isShot;
    bool isDone;
    bool isImageSave;
    
    int shotCount;
    int shotCountMax;
    
    //font
    ofxXmlSettings XML;
    ofTrueTypeFont font_name, font_day;
    string bride, groom, day;
    
    //gui
    ofxPanel gui;
    ofxIntSlider previewPosition_x, previewPosition_y, previewPosition_w, previewPosition_h;
    ofxIntSlider framePositionLeft_x, framePositionLeft_y, framePositionLeft_w, framePositionLeft_h,
    framePositionRight_x, framePositionRight_y, framePositionRight_w, framePositionRight_h;

};

#endif /* mirrorShot_hpp */
