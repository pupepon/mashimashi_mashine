#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        unsigned char* onAlpha(unsigned char* cp);
        void drawCol();
    
        //過去の映像を描画
        void drawCap();
    
        //'c'を押した時点の過去の映像を逆再生
        void drawPastBack();
    
        //'c'を押した時点の過去の映像を再生
        void drawPast();
    
        //過去の静止画を描画
        void drawLocus();
    
        //cap配列を描画(小さく５個並んでる奴)
        void drawSub();
    
        ofImage  img;
        static const int CAPMAX = 10;
        static const int COLNUM = 10;
        static const int SAVEMAX = 5;
        ofVideoGrabber  vidGrabber;
        ofTexture       videoTexture;
        int             camWidth;
        int             camHeight;
        bool            capFlg;
        int             capCount;
        int             mashiNum;
        int             mashiCount;
        int             capNum;
        int             copyCapNum;
        int             copyCapCount;
        int             pastCount;
        int             pastNum;
        int             backPastNum;
        int             backPastCount;
        bool            clickFlg;
        ofImage         cap[SAVEMAX][CAPMAX];
        ofImage         capDam[SAVEMAX][CAPMAX];
        ofImage         sato;
        ofColor         locusCol;
        ofColor         eraseColor[COLNUM];
        ofColor         drawColor[COLNUM];
        ofPoint         erasePos[COLNUM];
        ofPoint         drawPos[COLNUM];
        int             eraseId;
        int             drawId;
        int             threshold;
    
        ofxPanel gui;
        ofxIntSlider sld;
        ofxColorSlider colSld;
        ofxButton b;
        ofxToggle t;
};
