#pragma once

#include "ofMain.h"

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
    
    
        ofImage  img;
        static const int CAPMAX = 8;
        static const int COLNUM = 10;
        ofVideoGrabber  vidGrabber;
        ofTexture       videoTexture;
        int             camWidth;
        int             camHeight;
        bool            capFlg;
        int             capCount;
        int             mashiNum;
        int             mashiCount;
        int             capNum;
        bool            clickFlg;
        ofImage         cap[30][CAPMAX];
        ofImage         sato;
        ofColor         eraseColor[COLNUM];
        ofColor         drawColor[COLNUM];
        ofPoint         erasePos[COLNUM];
        ofPoint         drawPos[COLNUM];
        int             eraseId;
        int             drawId;
        int             threshold;
};
