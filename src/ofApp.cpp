#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFullscreen(true);
    ofBackground(ofColor::black);
    
    //ads setting
    slide.setDir("ads/");
    
    //대기 모드로 시작
    MiromiMode = IDLE;
}

//--------------------------------------------------------------
void ofApp::update(){
    switch(MiromiMode){
        case IDLE:
            slide.update();
            break;
            
        case SHOT:
            shot.update();
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
            slide.draw();
            break;
            
        case SHOT:
            shot.draw();
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
            MiromiMode++;
            shot.sayCheese();
            break;
            
        case SHOT:
            shot.sayCheese();
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
