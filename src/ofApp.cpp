#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    slide.setDir("ads/");
    ofBackground(ofColor::white);
    
    //대기 모드로 시작
    MiromiMode = IDLE;
}

//--------------------------------------------------------------
void ofApp::update(){
    switch(MiromiMode){
        case IDLE:
            break;
            
        case SHOT:
            break;
            
        case PREVIEW:
            break;
            
        case TEMPLATE:
            break;
            
        case PRINT:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    switch(MiromiMode){
        case IDLE:
//            for(int i = 0; i < (int)dir.size(); i++){
//                images[i].draw((ofGetWindowWidth()/2)-((images[i].getWidth()*ofGetWindowHeight())/images[i].getHeight())/2, 0, (images[i].getWidth()*ofGetWindowHeight())/images[i].getHeight(), ofGetWindowHeight());
//            }
            break;
            
        case SHOT:
            break;
            
        case PREVIEW:
            break;
            
        case TEMPLATE:
            break;
            
        case PRINT:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
            break;
            
        case SHOT:
            break;
            
        case PREVIEW:
            break;
            
        case TEMPLATE:
            break;
            
        case PRINT:
            break;
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
