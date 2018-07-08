//
//  adsSlide.hpp
//  Miromi
//
//  Created by Subong Jeong on 2018. 7. 9..
//

#ifndef adsSlide_hpp
#define adsSlide_hpp

#include "ofMain.h"

class adsSlide : public ofBaseApp{
public:
    ofDirectory dirAdsImages, dirAdsVideos;
    vector<ofImage> images;
    vector<ofVideoPlayer> videos;
    
    int slideTime;
    int totalAdsNum;
    int currentAdsNum;
    
    adsSlide();
    void setDir(string str); //경로 셋팅
    void setTime(int sec);
    
    void slideUpdate();
    void slideDraw();
};

#endif /* adsSlide_hpp */
