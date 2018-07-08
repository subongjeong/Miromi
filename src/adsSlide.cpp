//
//  adsSlide.cpp
//  Miromi
//
//  Created by Subong Jeong on 2018. 7. 9..
//

#include "adsSlide.hpp"
/*
 셋팅한 경로의 이미지(jpg, png)와 영상(mp4)를 불러와서 vector로 셋팅해 둔다.
 */

void adsSlide::setDir(string str){
    totalAdsNum = 0;
    currentAdsNum = 0;
    
    //확장자 지정
    dirAdsImages.allowExt("jpg");
    dirAdsImages.allowExt("png");
    
    //경로 셋팅 후 정렬
    dirAdsImages.listDir(str);
    dirAdsImages.sort();
    
    //이미지 크기 할당
    if( dirAdsImages.size() ){
        images.assign(dirAdsImages.size(), ofImage());
    }
    
    //이미지 불러오기
    for(int i = 0; i < (int)dirAdsImages.size(); i++){
        images[i].load(dirAdsImages.getPath(i));
        totalAdsNum++;
        ofLog(OF_LOG_VERBOSE) << "ads images path chk" << dirAdsImages.getPath(i);
    }
    
    //영상을 위한 셋팅
    dirAdsVideos.allowExt("mp4");
    dirAdsVideos.listDir(str);
    dirAdsVideos.sort();
    
    //영상 불러오기
    for(int i = 0; i < (int)dirAdsVideos.size(); i++){
        //videos[i].load(dir.getPath(i));
        totalAdsNum++;
        ofLog(OF_LOG_VERBOSE) << "ads videos path chk" << dirAdsVideos.getPath(i);
    }
    
    ofLog() << "total Ads Number : " << totalAdsNum;
}
