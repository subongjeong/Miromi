//
//  adsSlide.cpp
//  Miromi
//
//  Created by Subong Jeong on 2018. 7. 9..
//

#include "adsSlide.hpp"

/*
 클래스 초기화
 */
adsSlide::adsSlide(){
    slideTimeSet = 5;
    slideTime = slideTimeSet;
    currentAdsNum = 0;
    isSliding = false;
    prevTime = ofGetElapsedTimef();
    ofLog() << "adsSlide Init";
}

/*
 셋팅한 경로의 이미지(jpg, png)와 영상(mp4)를 불러와서 vector로 셋팅해 둔다.
 */
void adsSlide::setDir(string str){
    //확장자 지정
    dirAds.allowExt("jpg");
    dirAds.allowExt("png");
    dirAds.allowExt("mp4");
    
    //경로 셋팅 후 정렬
    dirAds.listDir(str);
    dirAds.sort();
    
    //이미지/영상을 나누어 다른 벡터에 넣어둔다.
    for(int i = 0; i < (int)dirAds.size(); i++){
        adsStr listStr;
        
        if(dirAds.getFile(i).getExtension() == "mp4"){
            //영상을 벡터에 넣는다.
            ofVideoPlayer vid;
            vid.load(dirAds.getPath((i)));
            videos.push_back(vid);
            
            //광고리스트에 영상, 영상 벡터의 로컬위치값을 넣는다.
            listStr.kind = VIDEO;
            listStr.localNum = (int)videos.size()-1;
            adsList.push_back(listStr);
        }else if(dirAds.getFile(i).getExtension() == "jpg" || dirAds.getFile(i).getExtension() == "png"){
            //이미지를 벡터에 넣는다.
            ofImage img;
            img.load(dirAds.getPath(i));
            images.push_back(img);
            
            //광고리스트에 이미지, 이미지 벡터의 로컬위치값을 넣는다.
            listStr.kind = IMAGE;
            listStr.localNum = (int)images.size()-1;
            adsList.push_back(listStr);
        }
    }
    
    for(int t=0; t<adsList.size(); t++){
        ofLog(OF_LOG_VERBOSE) << t << " : " << adsList[t].kind << "/" << adsList[t].localNum;
    }
}

//슬라이드 타임 셋팅. 영상이 재생될 때에는 영상 시간에 맞춘다.
void adsSlide::setTime(int sec){
    slideTimeSet = sec;
}

void adsSlide::slideUpdate(){
    //슬라이드 타임 셋팅
    if(ofGetElapsedTimef() - prevTime > slideTime){
        if(currentAdsNum < adsList.size()-1)
            currentAdsNum++;
        else
            currentAdsNum = 0;
        prevTime = ofGetElapsedTimef();
    }
    
    //광고 종류에 따라 업데이트 설정
    //영상의 경우는 재생/정지를 해준다.
    switch (adsList[currentAdsNum].kind) {
        case IMAGE:
            //이미지는 setTime(int sec)에 지정한 시간만큼 보여준다.
            slideTime = slideTimeSet;
            for(int i=0; i<videos.size(); i++)
                videos[i].stop();
            break;
            
        case VIDEO:
            //비디오의 재생시간을 slideTime에 지정한다.
            slideTime = videos[adsList[currentAdsNum].localNum].getDuration() - 0.500;
            videos[adsList[currentAdsNum].localNum].play();
            videos[adsList[currentAdsNum].localNum].update();
            break;
    }
}

void adsSlide::slideDraw(){
    switch (adsList[currentAdsNum].kind) {
        case IMAGE:
            images[adsList[currentAdsNum].localNum].draw(0,0);
            break;
            
        case VIDEO:
            videos[adsList[currentAdsNum].localNum].draw(0,0);
            break;
    }
}
