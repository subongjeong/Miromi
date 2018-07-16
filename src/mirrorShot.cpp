//
//  mirrorShot.cpp
//  Miromi
//
//  Created by Subong Jeong on 2018. 7. 9..
//

#include "mirrorShot.hpp"

mirrorShot::mirrorShot(){
    isImageSave = false;
    shotMode = READY;
    cheeseTime = 3;
    stillTime = 3;
    printTime = 21;
    shotCount = 0;
    shotCountMax = CUT;
    prevTime = ofGetElapsedTimef();
    
    //카메라 초기화
    camera.initGrabber(1280, 720);
    
    //xml 초기화
    if(XML.loadFile("miromiSettings.xml") ){
        ofLog() << "miromiSettings loaded";
    }else{
        ofLog() << "miromiSettings load fail";
    }
    
    gui.setup();
    gui.add(previewPosition_x.setup("preview x",0,-1920,1920));
    gui.add(previewPosition_y.setup("preview y",0,-1920,1920));
    gui.add(previewPosition_w.setup("preview w",0,-1920,1920));
    gui.add(previewPosition_h.setup("preview h",0,-1920,1920));
    
    gui.add(framePositionLeft_x.setup("frameL x",0,-1920,1920));
    gui.add(framePositionLeft_y.setup("frameL y",0,-1920,1920));
    gui.add(framePositionLeft_w.setup("frameL w",0,-1920,1920));
    gui.add(framePositionLeft_h.setup("frameL h",0,-1920,1920));
    
    gui.add(framePositionRight_x.setup("frameR x",0,-1920,1920));
    gui.add(framePositionRight_y.setup("frameR y",0,-1920,1920));
    gui.add(framePositionRight_w.setup("frameR w",0,-1920,1920));
    gui.add(framePositionRight_h.setup("frameR h",0,-1920,1920));
    gui.loadFromFile("settings.xml");
    
    ofTrueTypeFont::setGlobalDpi(72);
    font_name.load("font/name.otf", XML.getValue("FONT:NAME:SIZE",14));
    font_day.load("font/day.ttf", XML.getValue("FONT:DAY:SIZE",14));
    bride = XML.getValue("BRIDE","Soohye");
    groom = XML.getValue("GROOM","Subong");
    day = XML.getValue("DAY","July 12, 2014");
    
    //영상 초기화
    vid_sayCheese.load("ui/sayCheese.mp4");
    vid_sayCheese.setLoopState(OF_LOOP_NONE);
    vid_sayCheese.play();
    vid_sayCheese.update();
    
    vid_countdown.load("ui/countdown.mp4");
    vid_countdown.setLoopState(OF_LOOP_NONE);
    vid_countdown.play();
    vid_countdown.update();
    
    vid_preview.load("ui/preview.mp4");
    vid_preview.setLoopState(OF_LOOP_NONE);
    vid_preview.play();
    vid_preview.update();
    
    //컷 수만큼 메세지폴더에서 메세지 영상을 불러온다.
    //컷 미만이면 안된다.
    ofDirectory dir;
    dir.allowExt("mp4");
    dir.listDir("ui/message/");
    dir.sort();
    for(int i=0; i<CUT; i++){
        vid_message[i].load(dir.getPath(i));
        vid_message[i].setLoopState(OF_LOOP_NONE);
        vid_message[i].play();
        vid_message[i].update();
    }
    
    vid_print.load("ui/print.mp4");
    vid_print.setLoopState(OF_LOOP_NORMAL);
    vid_print.play();
    vid_print.update();
    
//    image_cheese.load("images/cheese.png");
//    image_count[0].load("images/5.png");
//    image_count[1].load("images/4.png");
//    image_count[2].load("images/3.png");
//    image_count[3].load("images/2.png");
//    image_count[4].load("images/1.png");
    
    //해상도를 픽스해주어야 하나?
    for(int i=0; i<CUT; i++){
        fboCut[i].allocate(1080,1920);
    }
    fboFrame.allocate(1800,1200);
    pixels.allocate(1800,1200,OF_IMAGE_COLOR);
    
    
    dirFrame.allowExt("jpg");
    dirFrame.allowExt("png");
    
    //경로 셋팅 후 정렬
    dirFrame.listDir("frames/");
    dirFrame.sort();
    
    //프레임 템플릿을 넣어둔다.
    for(int i = 0; i < (int)dirFrame.size(); i++){
        ofImage tmp;
        tmp.load(dirFrame.getPath(i));
        image_frame.push_back(tmp);
    }
}

//TODO : 관리자 기능을 위해 분리해서 config로 빼놓을 예정
void mirrorShot::setTime(int sec){
    cheeseTime = sec;
    stillTime = sec;
    printTime = sec;
}

//TODO : 관리자 기능을 위해 config로 빼놓을 예정
void mirrorShot::setShotCount(int cnt){
    shotCountMax = cnt;
}

//
//void mirrorShot::setPreviewPosition(int _x, int _y, int _w, int _h){
//    previewPosition_x = _x;
//    previewPosition_y = _y;
//    previewPosition_w = _w;
//    previewPosition_h = _h;
//}
//
//void mirrorShot::setFramePositionLeft(int _x, int _y, int _w, int _h){
//    framePositionLeft_x = _x;
//    framePositionLeft_y = _y;
//    framePositionLeft_w = _w;
//    framePositionLeft_h = _h;
//}
//
//void mirrorShot::setFramePositionRight(int _x, int _y, int _w, int _h){
//    framePositionRight_x = _x;
//    framePositionRight_y = _y;
//    framePositionRight_w = _w;
//    framePositionRight_h = _h;
//}

void mirrorShot::sayCheese(){
    if(shotMode == READY){
        shotMode = CHEESE;
        prevTime = ofGetElapsedTimef();
    }
}

void mirrorShot::print(){
    if(shotMode == FRAME){
        shotMode = PRINT;
    }
}

bool mirrorShot::getProcessDone(){
    return isDone;
}

void mirrorShot::update(){
    vid_sayCheese.update();
    vid_countdown.update();
    vid_preview.update();
    for(int i; i<CUT ; i++)
        vid_message[i].update();
    vid_print.update();
    
    switch(shotMode){
        case READY:
//            camera.update();
            shotCount = 0;
            isImageSave = false;
            
            if(vid_sayCheese.isPlaying()){
                vid_sayCheese.stop();
            }
            
            if(vid_countdown.isPlaying()){
                vid_countdown.stop();
            }
            
            if(vid_preview.isPlaying()){
                vid_preview.stop();
            }
            
            for(int i=0; i<CUT; i++){
                if(vid_message[i].isPlaying()){
                    vid_message[i].stop();
                }
            }
            
            if(vid_print.isPlaying()){
                vid_print.stop();
            }
            
            isDone = false;
            break;
            
        case CHEESE:
//            camera.update();
            
            vid_sayCheese.play();
            
            if(vid_countdown.getCurrentFrame() > 2){
                vid_countdown.setPaused(false);
                vid_countdown.setFrame(2);
            }else{
                vid_countdown.setPaused(true);
            }
            
            if(vid_preview.getCurrentFrame() > 2){
                vid_preview.setPaused(false);
                vid_preview.setFrame(2);
            }else{
                vid_preview.setPaused(true);
            }
            
            for(int i=0; i<CUT; i++){
                if(vid_message[i].getCurrentFrame()  > 2){
                    vid_message[i].setPaused(false);
                    vid_message[i].setFrame(2);
                }else{
                    vid_message[i].setPaused(true);
                }
            }
            
            if(vid_print.getCurrentFrame() > 2){
                vid_print.setPaused(false);
                vid_print.setFrame(2);
            }else{
                vid_print.setPaused(true);
            }
            
            isDone = false;
            if(vid_sayCheese.getCurrentFrame() >= vid_sayCheese.getTotalNumFrames()-5){
                shotMode = COUNT;
            }
//            if(ofGetElapsedTimef() - prevTime > cheeseTime){
//                shotMode = COUNT;
//                prevTime = ofGetElapsedTimef();
//            }
            break;
            
        case COUNT :
            camera.update();
            vid_countdown.play();
           
            if(vid_sayCheese.getCurrentFrame() > 2){
                vid_sayCheese.setPaused(false);
                vid_sayCheese.setFrame(2);
            }else{
                vid_sayCheese.setPaused(true);
            }
            
            if(vid_preview.getCurrentFrame() > 2){
                vid_preview.setPaused(false);
                vid_preview.setFrame(2);
            }else{
                vid_preview.setPaused(true);
            }
            
            for(int i=0; i<CUT; i++){
                if(vid_message[i].getCurrentFrame()  > 2){
                    vid_message[i].setPaused(false);
                    vid_message[i].setFrame(2);
                }else{
                    vid_message[i].setPaused(true);
                }
            }
            
            if(vid_print.getCurrentFrame() > 2){
                vid_print.setPaused(false);
                vid_print.setFrame(2);
            }else{
                vid_print.setPaused(true);
            }
            
            if(vid_countdown.getCurrentFrame() >= vid_countdown.getTotalNumFrames()-5){
                shotMode = STILL;
                prevTime = ofGetElapsedTimef();
                //화면을 fboCut에 저장한다.
                isShot = true;
            }
            
//            if(ofGetElapsedTimef() - prevTime > 5){
//                shotMode = STILL;
//                prevTime = ofGetElapsedTimef();
//
//                //화면을 fboCut에 저장한다.
//                isShot = true;
//            }
            break;
            
        case STILL :
            if(isShot){
                isShot = false;
            }
            vid_preview.play();

            if(vid_sayCheese.getCurrentFrame() > 2){
                vid_sayCheese.setPaused(false);
                vid_sayCheese.setFrame(2);
            }else{
                vid_sayCheese.setPaused(true);
            }
            
            if(vid_countdown.getCurrentFrame() > 2){
                vid_countdown.setPaused(false);
                vid_countdown.setFrame(2);
            }else{
                vid_countdown.setPaused(true);
            }
            
            if(vid_preview.getCurrentFrame() >= vid_preview.getTotalNumFrames()-5){
                shotMode = MESSAGE;
                prevTime = ofGetElapsedTimef();
            }
        
//            if(ofGetElapsedTimef() - prevTime > stillTime){
//                if(shotCount < shotCountMax){
//                    shotMode = CHEESE;
//                    prevTime = ofGetElapsedTimef();
//                }else{
//                    shotMode = FRAME;
//                }
//            }
        
            break;
            
        case MESSAGE:
            vid_message[shotCount].update();
            vid_message[shotCount].setPaused(false);
            vid_message[shotCount].play();
        
            if(vid_message[shotCount].getCurrentFrame() >= vid_message[shotCount].getTotalNumFrames()-5){
                if(++shotCount < shotCountMax){
                    shotMode = CHEESE;
                    prevTime = ofGetElapsedTimef();
                }else{
                    shotMode = FRAME;
                }
            }
            
            break;
            
        case FRAME :
            //프레임 선택화면
            prevTime = ofGetElapsedTimef();
            break;
            
        case PRINT :
            vid_print.update();
            vid_print.setPaused(false);
            vid_print.play();
            //출력 넣어야 함
            if(!isImageSave){
                fboFrame.readToPixels(pixels);
                string fileName;
                fileName = ofToString(ofGetMonth()) +"-"+ ofToString(ofGetDay()) +"-"+ ofToString(ofGetHours()) +"-"+ ofToString(ofGetMinutes()) +"-"+ ofToString(ofGetSeconds())+".jpg";
                ofSaveImage(pixels, fileName ,OF_IMAGE_QUALITY_BEST);
                
                //프린터 부분 예. 옵션이 중요하다.
                string print ="lp -o media=Custom.156x105mm /Users/subongjeong/Developer/Openframeworks/of_v0.10.0_osx_release/apps/myApps/Miromi/bin/data/";
                
                print += fileName;
                ofSystem(print);
                //system ("lp /Users/subongjeong/Developer/Openframeworks/of_v0.10.0_osx_release/apps/myApps/Miromi/bin/");
                isImageSave = true;
            }
            
            //다시 처음으로
            if(ofGetElapsedTimef() - prevTime > printTime){
                isDone = true;
                isImageSave = false;
                shotMode = READY;
                shotCount = 0;
            }
            break;
    }
 //   cout << "shotmode : " << shotMode << "cmt : " << shotCount<< endl;
}

void mirrorShot::draw(){
    ofEnableAlphaBlending();
    switch(shotMode){
        case READY:
//            ofSetColor(255,255,255,255);
//            ofPushMatrix();
//            ofTranslate(1080, 0);
//            ofPushMatrix();
//            ofRotateZDeg(90);
//            camera.draw(0,0,1920,1080);
//            ofPopMatrix();
//            ofPopMatrix();
            break;
            
        case CHEESE:
//            ofSetColor(255,255,255,255);
//            ofPushMatrix();
//            ofTranslate(1080, 0);
//            ofPushMatrix();
//            ofRotateZDeg(90);
//            camera.draw(0,0,1920,1080);
//            ofPopMatrix();
//            ofPopMatrix();
//            ofSetColor(255,255,255,255);
//            image_cheese.draw(0,0);
            vid_sayCheese.draw(0,0,1080,1920);
            break;
            
        case COUNT :
//            ofSetColor(255,255,255,255);
//            ofPushMatrix();
//            ofTranslate(1080, 0);
//            ofPushMatrix();
//            ofRotateZDeg(90);
//            camera.draw(0,0,1920,1080);
//            ofPopMatrix();
//            ofPopMatrix();
//            ofSetColor(255,255,255,255);
//            image_count[(int)ofGetElapsedTimef() - prevTime].draw(0,0);
            vid_countdown.draw(0,0,1080,1920);
            break;
            
        case STILL :
            vid_preview.draw(0, 0, 1080, 1920);
            ofSetColor(255,255,255,255);
            ofPushMatrix();
            ofTranslate(previewPosition_x, previewPosition_y); //영상 사이즈에 맞췄음. 나중에 gui로 빼야하나
            ofPushMatrix();
            ofRotateZDeg(90);
            camera.draw(0,0,previewPosition_w,previewPosition_h);
            ofPopMatrix();
            ofPopMatrix();
            
            if(isShot){
                fboCut[shotCount].begin();
                ofClear(0,0,0,0);
                ofSetColor(255,255,255,255);
                ofPushMatrix();
                ofTranslate(1080, 0);
                ofPushMatrix();
                ofRotateZDeg(90);
                camera.draw(0,0,1920,1080);
                ofPopMatrix();
                ofPopMatrix();
                fboCut[shotCount].end();
            }
            break;
            
        case MESSAGE:
            vid_message[shotCount].draw(0, 0, 1080, 1920);
            break;
            
        case FRAME :
            fboFrame.begin();
            ofClear(0,0,0,0);
            ofSetColor(255,255,255,255);
            fboCut[1].draw(framePositionLeft_x,framePositionLeft_y,framePositionLeft_w,framePositionLeft_h);
            fboCut[0].draw(framePositionRight_x,framePositionRight_y,framePositionRight_w,framePositionRight_h);
            image_frame[0].draw(0, 0, 1800, 4*1800/6);
            fboFrame.end();
            fboFrame.draw(0, 0, 1080, 4*1080/6);
            break;
            
        case PRINT :
            vid_print.draw(0, 0, 1080, 1920);
            break;
    }
    
    font_name.drawString(bride, 100, 100);
    font_name.drawString(groom, 100, 150);
    font_day.drawString(day, 100, 200);
}
