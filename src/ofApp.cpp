#include "ofApp.h"

int frame;
bool capflg;
int capX = 0;
int capY = 0;
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
    mashiFlg = false;
    mashiText = "image_";
    clickColor.r = 0;
    clickColor.g = 200;
    clickColor.b = 0;
    capNum = 0;
   // cap.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
  
}

//--------------------------------------------------------------
void ofApp::update() {
    
    vidGrabber.update();
    
    if (frame >= CAPMAX * 3) {
        
        frame = 0;
        mashiNum = rand() % 10;
//        capX = rand()%camWidth;
//        capY = rand()%camHeight;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    ofEnableAlphaBlending();
    
    ofSetColor(255);
    sato.draw(0,0);
    //最初初期化してないの描画してるかも
    img.draw(0,0);
    //vidGrabber.draw(0, 0);
    if (mashiFlg) {
        cap[mashiNum][mashiCount].draw(0,0);
        mashi.draw( 0, 0);
        for(int i = 0; i < 10; i++){
            cap[i][mashiCount].draw(camWidth*i,camHeight);
        }
        mashiCount += 1;
        if (mashiCount >= CAPMAX) {
            mashiCount = 0;
        }
    }
    
    unsigned char* cp = vidGrabber.getPixels();
    unsigned char* mp;
    mp = (unsigned char*)malloc(camWidth * camHeight * 4);
    
    if (img.bAllocated()) {
        for (int y = 0; y < camHeight; y++) {
            for (int x = 0; x < camWidth; x++) {
                ofColor c = img.getColor(x, y);
                ofSetColor(c.r, c.g, c.b);
                mp[(camWidth * y + x) * 4 + 2] = cp[(camWidth * y + x) * 3 + 2];
                mp[(camWidth * y + x) * 4 + 1] = cp[(camWidth * y + x) * 3 + 1];
                mp[(camWidth * y + x) * 4] = cp[(camWidth * y + x) * 3];
                if (((c.g > c.r && c.g > c.b ) && (c.g-c.r > 30)) ||
                    (!(abs(c.r-clickColor.r) > 30) && !(abs(c.g-clickColor.g) > 30) && !(abs(c.b-clickColor.b) > 30))) {
                    //ofSetColor(0, 0, 0, 0);
                    mp[(camWidth * y + x) * 4 + 3] = 0;
                    //ofRect(camWidth+ x, y, 1, 1);
                } else {
                    //ofSetColor(c.r, c.g, c.b);
                    mp[(camWidth * y + x) * 4 + 3] = 255;
                    //ofRect(camWidth+ x, y, 1, 1);
                }
            }
        }
    }
    if(capCount >= CAPMAX) {
        capCount = 0;
        capNum < 9 ? capNum++ : capNum = 0;
    }
    //透過した奴をimg(本体)に代入
    img.setFromPixels(mp,camWidth,camHeight,OF_IMAGE_COLOR_ALPHA);
    //透過した奴をcap配列(分身)に代入
    cap[capNum][capCount].setFromPixels(mp, camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    capCount++;
    
    
//    if(capbFlg) {
//        capb[capbCount].setFromPixels(mp, camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
//        capbCount++;
//        if(capbCount >= CAPMAX) {
//            capbFlg = false;
//            capbCount = 0;
//        }
//    }
    free(mp);
    //ofDisableAlphaBlending();
    frame++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
//    if(key == 'c') {
//        capFlg = true;
//    }
    if(key == 'v') {
        mashiFlg = true;
    }
    if(key == 'z'){
    }
    if(key == 'd') {
        mashiFlg = false;
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
    
    clickColor = img.getColor(x , y);
    
    

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