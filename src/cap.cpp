//
//  cap.cpp
//  test
//
//  Created by student on 2015/11/16.
//
//

#include "cap.h"

void ca::setup(){
    camWidth = 640;
    camHeight = 480;
    ofBackground(200, 200, 200);
    ofSetFrameRate(60);
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(camWidth, camHeight);
    ofSetVerticalSync(true);
    capFlg = false;
    capCount = 0;
    mashiNum = 0;
    mashiCount = 0;
    eraseId = 0;
    drawId = 0;
    clickFlg = true;
    threshold = 30;
    for(int i=0; i<COLNUM; i++){
        eraseColor[i] = ofColor(0,100+i*5,0);
        drawColor[i] = ofColor(0,0,0);
        erasePos[i] = ofPoint(0,0);
        erasePos[i] = ofPoint(0,0);
    }
    capNum = 0;
}
void ca::chromaKey(unsigned char* mp){
    img.setFromPixels(mp, camWidth, camHeight, OF_IMAGE_COLOR);
    
}
void ca::eraseCol(ofColor c){
    
}
void ca::update(){
    img.draw(0,0);
}
