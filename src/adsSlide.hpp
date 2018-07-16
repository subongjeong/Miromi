//
//  adsSlide.hpp
//  Miromi
//
//  Created by Subong Jeong on 2018. 7. 9..
//

#ifndef adsSlide_hpp
#define adsSlide_hpp

#include "ofMain.h"

enum{
    IMAGE = 0,
    VIDEO
};

struct adsStr{
    int kind = IMAGE;
    int localNum;
};

class adsSlide : public ofBaseApp{
private:
    int slideTimeSet;
public:
    ofDirectory dirAds;
    vector<ofImage> images;
    vector<ofVideoPlayer> videos;
    vector<adsStr> adsList; //이미지와 영상의 리스트를 관리한다.
    ofImage companyFrame;
        
    int alpha;
    int slideTime;
    int prevTime;
    int currentAdsNum;
    bool isSliding; //현재 움직이고 있는지 여부    
    
    adsSlide();
    void setDir(string str); //경로 셋팅
    void setTime(int sec);
    
    void update();
    void draw();
};

#endif /* adsSlide_hpp */
