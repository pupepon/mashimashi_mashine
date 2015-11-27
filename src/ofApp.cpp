#include "ofApp.h"
//1フレームずれてる！！！

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
    capCount        = 0;
    capNum          = 0;
    eraseId         = 0;
    drawId          = 0;
    copyCapNum      = 0;
    copyCapCount    = 0;
    backPastNum     = 0;
    backPastCount   = 0;
    pastNum         = 0;
    pastCount       = 0;
    clickFlg        = true;
    threshold       = 30;
    for(int i=0; i<COLNUM; i++){
        eraseColor[i] = ofColor(0,100+i*5,0);
        drawColor[i] = ofColor(0,0,0);
    }
    capNum = 0;
   // cap.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    ofxGuiSetTextPadding(4);
    ofxGuiSetDefaultWidth(300);
    ofxGuiSetDefaultHeight(18);
    gui.setup();
    gui.add(capSld.setup("capmax", 10, 1, CAPMAX));
    gui.add(saveSld.setup("savemax", 5, 1, SAVEMAX));
    gui.add(random.setup("random"));
    gui.add(t.setup("toggle", false));
    gui.add(colSld.setup("color",ofColor(255,255,255),ofColor(0,0),ofColor(255,255)));
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    vidGrabber.update();
    ofEnableAlphaBlending();
    //最初初期化してないの描画してるかも
    //img.draw(0,0);

    unsigned char* cp = vidGrabber.getPixels();
    img.setFromPixels(cp,camWidth,camHeight,OF_IMAGE_COLOR);
    
    //透過した奴をcap配列(分身)に代入
    //cout << capNum << endl;
    cap[capNum][capCount].setFromPixels(onAlpha(cp), camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    //drawCap();
    drawCol();
    drawSub();
    drawPast();
    drawPastBack();
    //drawLocus();
    drawRandom();
    ofSetColor(colSld);
    //cap[capNum][capCount].draw(0,0);
    
    capCount++;
    //capmaxフレームごとに次のバッファへ。
    if(capCount == capmax) {
        if(capNum == savemax-1){
            capNum = 0;
        }else{
            capNum++;
        }
        capCount = 0;
    }
    //ofDisableAlphaBlending();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    if(key == 'r'){
        for(int i=0; i<COLNUM; i++){
            savemax = saveSld;
            capmax = capSld;
            eraseColor[i] = ofColor(0,100+i*5,0);
            drawColor[i]  = ofColor(0,0,0);
            capCount        = 0;
            capNum          = 0;
            eraseId         = 0;
            drawId          = 0;
            copyCapNum      = 0;
            copyCapCount    = 0;
            backPastNum     = 0;
            backPastCount   = 0;
            pastNum         = 0;
            pastCount       = 0;
            clickFlg        = true;
            threshold       = 30;
            for(int i=0; i<SAVEMAX; i++){
                for(int j=0; j<CAPMAX; j++){
                    cap[i][j].clear();
                }
            }
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
    if(key == ' '){
    }
    if(key == 'c'){
        for(int i=0; i< savemax; i++){
            for(int j=0; j<capmax; j++){
                capDam[i][j] = cap[i][j];
            }
        }
        copyCapCount    = capCount;
        pastCount       = capCount;
        backPastCount   = capCount;
        
        copyCapNum      = capNum;
        pastNum         = capNum;
        backPastNum     = capNum;
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
        eraseColor[eraseId] = img.getColor(x,y);
        eraseId++;
    }else{
        if(drawId == COLNUM){drawId = 0;}
        drawColor[drawId] = img.getColor(x,y);
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

unsigned char* ofApp::onAlpha(unsigned char *cp){

    //mpに現在フレームを透過して代入
    unsigned char* mp;
    mp = (unsigned char*)malloc(camWidth * camHeight * 4);
    if (img.bAllocated()) {
        for (int y = 0; y < camHeight; y++) {
            for (int x = 0; x < camWidth; x++) {
                ofColor c = img.getColor(x, y);
                ofSetColor(c.r, c.g, c.b);
                mp[(camWidth * y + x) * 4 + 2] = c.b;
                mp[(camWidth * y + x) * 4 + 1] = c.g;
                mp[(camWidth * y + x) * 4]     = c.r;
                mp[(camWidth * y + x) * 4 + 3] = 255;
                //指定色を透過
                for(int i = 0; i<COLNUM; i++){
                    if(((c.g > c.r && c.g > c.b ) && (c.g-c.r > threshold)) ||
                       ((abs(c.r-eraseColor[i].r) < threshold) && (abs(c.g-eraseColor[i].g) < threshold) && (abs(c.b-eraseColor[i].b) < threshold))){
                        mp[(camWidth * y + x) * 4 + 3] = 0;
                        break;
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
    free(mp);
    return mp;
}

void ofApp::drawCol(){
    for(int i =0; i<COLNUM/5; i++){
        for(int j = 0; j<5; j++){
            ofSetColor(eraseColor[i*5+j]);
            ofRect(camWidth+80*j,camHeight+0+i*50,50,50);
            ofSetColor(drawColor[i*5+j]);
            ofRect(camWidth+80*j,camHeight+100+i*50,50,50);
        }
    }
}

void ofApp::drawCap(){
    int num = capNum;
    ofColor col = colSld;
    for(int i=0; i<savemax; i++){
        num--;
        if(num < 0){num = savemax-1;}
        if(cap[num][capmax-1].bAllocated()){
            col.a = (savemax -1 - i) * 255/savemax;
            ofSetColor(col);
            //cout << num << endl;
            cout << col << endl;
            cap[num][capCount].draw(0,0);
        }
    }
}

void ofApp::drawPastBack(){
    ofSetColor(colSld);
    
    backPastCount--;
    if(backPastCount == -1){
        backPastCount = capmax-1;
        
        if(backPastNum == 0){
            backPastNum = savemax-1;
        }else{
            backPastNum--;
        }
    }
    if(capDam[backPastNum][backPastCount].bAllocated()){
        capDam[backPastNum][backPastCount].draw(camWidth*2,0);
    }
}

void ofApp::drawPast(){
    ofSetColor(colSld);
    if(capDam[pastNum][pastCount].bAllocated()){
        capDam[pastNum][pastCount].draw(camWidth,0);
        pastCount++;
    }
    
    if(pastCount == capmax){
        pastCount = 0;
        if(pastNum == savemax-1){
            pastNum = 0;
        }else{
            pastNum++;
        }
    }
}

void ofApp::drawLocus(){
    int num = capNum;
    locusCol = colSld;
    for(int i=0; i<savemax; i++){
        num--;
        if(num < 0){num = savemax-1;}
        if(cap[num][capmax-1].bAllocated()){
            locusCol.a = (savemax -1 - i) * 255/savemax;
            ofSetColor(locusCol);
            cap[num][capmax-1].draw(0,0);
        }
    }
}

void ofApp::drawSub(){
ofSetColor(colSld);
    if (cap[capNum][capCount].bAllocated()) {
        // 過去の映像表示
        for(int i=0; i<savemax/5; i++){
            for(int j=0; j<5; j++){
                if(cap[i*5+j][capCount].bAllocated()){
                    cap[i*5+j][capCount].draw(camWidth/5*j, camHeight+camHeight/5*i, camWidth/5, camHeight/5);
                }
            }
        }
    }
}

void ofApp::drawRandom(){
    if(random){
        randPos.x = ofRandom(camWidth/4, camWidth/4*3);
        randPos.y = ofRandom(camHeight/4,camHeight/4*3);
        randScale = ofRandom(0,1);
    }
    cap[0][capCount].draw(randPos.x-camWidth*randScale/2,randPos.y-camWidth*randScale/2, camWidth*randScale, camHeight*randScale);
    
}