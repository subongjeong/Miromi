#pragma once
#include "ofMain.h"
#include "adsSlide.hpp"
#include "mirrorShot.hpp"


enum{
    IDLE = 0,
    TOUCHTOSTART,
    SHOT
//    ,
//    TEMPLATE,
//    PRINT
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    adsSlide slide;
    mirrorShot shot;
    
    ofVideoPlayer touchToStart;
    bool isFullscreen;
    bool isGui;
    
    int MiromiMode;
};
