#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofImage  img;
        static const int CAPMAX = 30;
        ofVideoGrabber  vidGrabber;
        ofTexture       videoTexture;
        int             camWidth;
        int             camHeight;
        bool            capFlg;
        bool            convertFlg;
        int             capCount;
        int             mashiNum;
        int             mashiCount;
        int             capNum;
        string          mashiText;
        bool            mashiFlg;
        ofImage         cap[10][CAPMAX];
        ofImage         sato;
        ofColor         clickColor;
};
