#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_SILENT);
    ofSetFullscreen(isFullscreen);
    ofBackground(ofColor::black);
    
    touchToStart.load("ui/touchToStart.mp4");
    touchToStart.setLoopState(OF_LOOP_NORMAL);
    
    //ads setting
    slide.setDir("ads/");
    
    //대기 모드로 시작
    MiromiMode = IDLE;
    
    isGui = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    switch(MiromiMode){
        case IDLE:
            slide.update();
            break;
            
        case TOUCHTOSTART :
            touchToStart.play();
            touchToStart.update();
            break;
            
        case SHOT:
            shot.update();
            if(shot.getProcessDone()){
                MiromiMode = IDLE;
            }
            break;
//
//        case TEMPLATE:
//            break;
//
//        case PRINT:
//            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    switch(MiromiMode){
        case IDLE:
            slide.draw();
            break;
            
        case TOUCHTOSTART :
            ofSetColor(255, 255, 255, 255);
            touchToStart.draw(0, 0, 1080, 1920);
            break;
            
        case SHOT:
            shot.draw();
            break;
//
//        case TEMPLATE:
//            break;
//
//        case PRINT:
//            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case ' ':
            isFullscreen = !isFullscreen;
            ofSetFullscreen(isFullscreen);
            break;
            
        case 'i':
            isGui = !isGui;
            break;
//
//        case 'c':
//            ofSaveScreen("photos/"+ofToString(ofGetMonth()) +"-"+ ofToString(ofGetDay()) +"-"+ ofToString(ofGetHours()) +"-"+ ofToString(ofGetMinutes()) +"-"+ ofToString(ofGetSeconds())+".png");
//            break;
            
        case 'p':
            //프린트 출력하는 명령어
            //system (  "lpr sb.pdf");
            //system (  "lp /Users/subongjeong/Developer/Openframeworks/of_v0.10.0_osx_release/apps/myApps/Miromi/bin/data/photos/7-9-19-57-27.png"  );
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    switch(MiromiMode){
        case IDLE:
            MiromiMode = TOUCHTOSTART;
            break;
            
        case TOUCHTOSTART :
            MiromiMode = SHOT;
            shot.sayCheese();
            break;
            
        case SHOT:
            //임시
            shot.print();
            break;
            
//        case TEMPLATE:
//            break;
//
//        case PRINT:
//            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
