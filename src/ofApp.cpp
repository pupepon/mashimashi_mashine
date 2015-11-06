#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {
    
    camWidth = 640;
    camHeight = 480;
    ofBackground(200, 200, 200);
    ofSetFrameRate(60);
    sato.loadImage("an.jpg");
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
   // cap.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
  
}

//--------------------------------------------------------------
void ofApp::update() {
    
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    ofEnableAlphaBlending();
    
    ofSetColor(255);
    sato.draw(0,0);
    //最初初期化してないの描画してるかも
    if(img.bAllocated()){img.draw(0,0);}
    //vidGrabber.draw(0, 0);
    
    if (cap[mashiNum][mashiCount].bAllocated()) {
        //cap[mashiNum][mashiCount].draw(0,0);
        mashiCount += 1;
        
        // 過去の映像表示
        for(int i=0; i<SAVEMAX/5; i++){
            for(int j=0; j<5; j++){
                if(cap[i+5*j][mashiCount].bAllocated()){
                    cap[i+5*j][mashiCount].draw(camWidth/5*i, camHeight+camHeight/5*j, camWidth/5, camHeight/5);
                    cap[i+5*j][mashiCount].draw(0,0);
                }
            }
        }

        if (mashiCount >= CAPMAX-1) {
            mashiCount = 0;
            if(mashiNum == 9){
                mashiNum = 0;
            }else{
            mashiNum++;
            }
        }
    }
    for(int i =0; i<COLNUM/5; i++){
        for(int j = 0; j<5; j++){
            ofSetColor(eraseColor[i*5+j]);
            ofRect(camWidth+80*j,0+i*50,50,50);
            ofSetColor(drawColor[i*5+j]);
            ofRect(camWidth+80*j,300+i*50,50,50);
        }
    }
    unsigned char* cp = vidGrabber.getPixels();
    unsigned char* mp;
    mp = (unsigned char*)malloc(camWidth * camHeight * 4);
    
    //mpに現在フレームを透過して代入
    if (img.bAllocated()) {
        for (int y = 0; y < camHeight; y++) {
            for (int x = 0; x < camWidth; x++) {
                ofColor c = img.getColor(x, y);
                ofSetColor(c.r, c.g, c.b);
                mp[(camWidth * y + x) * 4 + 2] = cp[(camWidth * y + x) * 3 + 3];
                mp[(camWidth * y + x) * 4 + 2] = cp[(camWidth * y + x) * 3 + 2];
                mp[(camWidth * y + x) * 4 + 1] = cp[(camWidth * y + x) * 3 + 1];
                mp[(camWidth * y + x) * 4] = cp[(camWidth * y + x) * 3];
                //指定色を透過
                for(int i = 0; i<COLNUM; i++){
                        if(((c.g > c.r && c.g > c.b ) && (c.g-c.r > 30)) ||
                        ((abs(c.r-eraseColor[i].r) < threshold) && (abs(c.g-eraseColor[i].g) < threshold) && (abs(c.b-eraseColor[i].b) < threshold))){
                            mp[(camWidth * y + x) * 4 + 3] = 0;
                            break;
                        }else{
                            mp[(camWidth * y + x) * 4 + 3] = 255;
                    }
                }

                //指定色を描画
                for(int i = 0; i < COLNUM; i++){
                    if((abs(c.r - drawColor[i].r)) < 5 && (abs(c.r - drawColor[i].r)) && (abs(c.r - drawColor[i].r))){
                        mp[(camWidth * y + x) * 4 + 3] = 255;
                    }
                }
            }
        }
    }
    
    //透過した奴をimg(本体)に代入
    img.setFromPixels(mp,camWidth,camHeight,OF_IMAGE_COLOR_ALPHA);
    
    //透過した奴をcap配列(分身)に代入
    cap[capNum][capCount].setFromPixels(mp, camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    capCount++;

    //30フレームごとに次のバッファへ。最大10
    if(capCount >= CAPMAX) {
        if(capNum == SAVEMAX-1){
            capNum = 0;
        }else{
            capNum++;
        }
        capCount = 0;
    }

    free(mp);
    //ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    if(key == 'c'){
        for(int i=0; i<30; i++){
            eraseColor[i] = (0,170+i*10,0);
            drawColor[i] = (0,0,0);
        }
    }
    if(key == 'e'){
        clickFlg = true;
    }
    if(key == 'd'){
        clickFlg = false;
    }
    if(key == ';'){
        threshold++;
    }
    if(key == '-'){
        threshold--;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
    if(clickFlg){
        if(eraseId == COLNUM){eraseId = 0;}
        eraseColor[eraseId] = img.getColor(x , y);
        erasePos[eraseId] = ofPoint(x,y);
        eraseId++;
    }else{
        if(drawId == COLNUM){drawId = 0;}
        drawColor[drawId] = img.getColor(x,y);
        drawPos[drawId] = ofPoint(x,y);
        drawId++;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}