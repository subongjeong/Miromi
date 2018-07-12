//
//  mirrorShot.cpp
//  Miromi
//
//  Created by Subong Jeong on 2018. 7. 9..
//

#include "mirrorShot.hpp"

mirrorShot::mirrorShot(){
    shotMode = READY;
    cheeseTime = 3;
    stillTime = 3;
    printTime = 5;
    shotCount = 0;
    shotCountMax = 2;
    prevTime = ofGetElapsedTimef();
    
    camera.initGrabber(1280, 720);
    image_cheese.load("images/cheese.png");
    image_count[0].load("images/5.png");
    image_count[1].load("images/4.png");
    image_count[2].load("images/3.png");
    image_count[3].load("images/2.png");
    image_count[4].load("images/1.png");
    
    //해상도를 픽스해주어야 하나?
    fboCut[0].allocate(1080,1920);
    fboCut[1].allocate(1080,1920);
    fboFrame.allocate(1080,1920);
    pixels.allocate(1080,1920,OF_IMAGE_COLOR);
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
    switch(shotMode){
        case READY:
            camera.update();
            shotCount = 0;
            isDone = false;
            break;
            
        case CHEESE:
            camera.update();
            isDone = false;
            if(ofGetElapsedTimef() - prevTime > cheeseTime){
                shotMode = COUNT;
                prevTime = ofGetElapsedTimef();
            }
            break;
            
        case COUNT :
            camera.update();
            if(ofGetElapsedTimef() - prevTime > 5){
                shotMode = STILL;
                prevTime = ofGetElapsedTimef();
                
                //화면을 fboCut에 저장한다.
                isShot = true;
            }
            break;
            
        case STILL :
            if(isShot){
                isShot = false;
            }
        
            if(ofGetElapsedTimef() - prevTime > stillTime){
                if(shotCount < shotCountMax){
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
            //출력 넣어야 함
            
            //다시 처음으로
            if(ofGetElapsedTimef() - prevTime > printTime){
                fboFrame.readToPixels(pixels);
                ofSaveImage(pixels, "good.jpg",OF_IMAGE_QUALITY_BEST);
                isDone = true;
                shotMode = READY;
                shotCount = 0;
            }
            break;
    }
//    cout << "shotmode : " << shotMode << endl;
}

void mirrorShot::draw(){
    ofEnableAlphaBlending();
    switch(shotMode){
        case READY:
            ofSetColor(255,255,255,255);
            ofPushMatrix();
            ofTranslate(1080, 0);
            ofPushMatrix();
            ofRotateZDeg(90);
            camera.draw(0,0,1920,1080);
            ofPopMatrix();
            ofPopMatrix();
            break;
            
        case CHEESE:
            ofSetColor(255,255,255,255);
            ofPushMatrix();
            ofTranslate(1080, 0);
            ofPushMatrix();
            ofRotateZDeg(90);
            camera.draw(0,0,1920,1080);
            ofPopMatrix();
            ofPopMatrix();
            ofSetColor(255,255,255,255);
            image_cheese.draw(0,0);
            break;
            
        case COUNT :
            ofSetColor(255,255,255,255);
            ofPushMatrix();
            ofTranslate(1080, 0);
            ofPushMatrix();
            ofRotateZDeg(90);
            camera.draw(0,0,1920,1080);
            ofPopMatrix();
            ofPopMatrix();
            ofSetColor(255,255,255,255);
            image_count[(int)ofGetElapsedTimef() - prevTime].draw(0,0);
            break;
            
        case STILL :
            if(isShot){
                fboCut[shotCount].begin();
                ofClear(0,0,0,0);
            }
            ofSetColor(255,255,255,255);
            ofPushMatrix();
            ofTranslate(1080, 0);
            ofPushMatrix();
            ofRotateZDeg(90);
            camera.draw(0,0,1920,1080);
            ofPopMatrix();
            ofPopMatrix();
            if(isShot){
                fboCut[shotCount++].end();
            }
            break;
            
        case FRAME :
            fboFrame.begin();
            ofClear(0,0,0,0);
            fboCut[0].draw(0,0,1080/2,1920/2);
            fboCut[1].draw(1080/2,0,1080/2,1920/2);
            fboFrame.end();
            fboFrame.draw(0,0);
            break;
            
        case PRINT :
            ofDrawBitmapString("print", 100, 100);
            break;
    }
    ofDisableAlphaBlending();
}
