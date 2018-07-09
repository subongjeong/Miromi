//
//  mirrorShot.cpp
//  Miromi
//
//  Created by Subong Jeong on 2018. 7. 9..
//

#include "mirrorShot.hpp"

mirrorShot::mirrorShot(){
    shotMode = READY;
    delayTime = 3;
    prevTime = ofGetElapsedTimef();
    
    camera.initGrabber(1920, 1080);
    image_cheese.load("images/cheese.png");
    image_count[0].load("images/5.png");
    image_count[1].load("images/4.png");
    image_count[2].load("images/3.png");
    image_count[3].load("images/2.png");
    image_count[4].load("images/1.png");
}

void mirrorShot::setTime(int sec){
    delayTime = sec;
}

void mirrorShot::sayCheese(){
    if(shotMode == READY){
        shotMode = CHEESE;
        prevTime = ofGetElapsedTimef();
    }
}

void mirrorShot::update(){
    switch(shotMode){
        case READY:
            camera.update();
            break;
            
        case CHEESE:
            camera.update();
            if(ofGetElapsedTimef() - prevTime > delayTime){
                shotMode = COUNT;
                prevTime = ofGetElapsedTimef();
            }
            break;
            
        case COUNT :
            camera.update();
            if(ofGetElapsedTimef() - prevTime > 5){
                shotMode = STILL;
                prevTime = ofGetElapsedTimef();
            }
            break;
            
        case STILL :
            if(ofGetElapsedTimef() - prevTime > delayTime){
                shotMode = READY;
                prevTime = ofGetElapsedTimef();
            }
            break;
    }
}

void mirrorShot::draw(){
    //카메라를 화면에 맞게 돌린다.
    ofEnableAlphaBlending();
    ofSetColor(255,255,255,255);
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth(), 0);
    ofPushMatrix();
    ofRotateZDeg(90);
    camera.draw(0,0,ofGetWindowHeight(),ofGetWindowWidth());
    ofPopMatrix();
    ofPopMatrix();
    
    switch(shotMode){
        case READY:
            break;
            
        case CHEESE:
            image_cheese.draw(0,0);
            break;
            
        case COUNT :
            image_count[(int)ofGetElapsedTimef() - prevTime].draw(0,0);
            break;
            
        case STILL :
            break;
    }
    ofDisableAlphaBlending();
}
