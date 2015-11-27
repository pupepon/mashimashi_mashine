//
//  cap.h
//  test
//
//  Created by student on 2015/11/16.
//
//

#ifndef __test__cap__
#define __test__cap__

#include <stdio.h>
#include <ofApp.h>
class ca {
    
public:
    void setup();
    void update();
    void eraseCol(ofColor);
    void chromaKey(unsigned char*);
    
    ofImage  img;
    static const int CAPMAX = 3;
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
    bool            clickFlg;
    ofImage         cap[SAVEMAX][CAPMAX];
    ofImage         sato;
    ofImage         check;
    ofColor         eraseColor[COLNUM];
    ofColor         drawColor[COLNUM];
    ofPoint         erasePos[COLNUM];
    ofPoint         drawPos[COLNUM];
    int             eraseId;
    int             drawId;
    int             threshold;
private:
};

#endif /* defined(__test__cap__) */
