#include "ofApp.h"

int frame;
bool f = true;
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
    mashiFlg = true;
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
        cap[mashiNum][mashiCount].draw(0,0);
        mashiCount += 1;
        
        // 過去の映像表示
        for(int i=0; i<5; i++){
            for(int j=0; j<2; j++){
                if(cap[i+5*j][mashiCount].bAllocated()){
                    cap[i+5*j][mashiCount].draw(camWidth/5*i, camHeight+camHeight/5*j, camWidth/5, camHeight/5);
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
    
    unsigned char* cp = vidGrabber.getPixels();
    unsigned char* mp;
    mp = (unsigned char*)malloc(camWidth * camHeight * 4);
    
    //mpに現在フレームを透過して代入
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

    //透過した奴をimg(本体)に代入
    img.setFromPixels(mp,camWidth,camHeight,OF_IMAGE_COLOR_ALPHA);
    
    //透過した奴をcap配列(分身)に代入
    cap[capNum][capCount].setFromPixels(mp, camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    capCount++;

    //30フレームごとに次のバッファへ。最大10
    if(capCount >= CAPMAX) {
        if(capNum == 9){
            capNum = 0;
        }else{
            capNum++;
        }
        capCount = 0;
    }

    free(mp);
    //ofDisableAlphaBlending();
    frame++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    if(key == 'v') {
        mashiFlg = true;
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