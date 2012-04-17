#pragma once

#include "ofMain.h"

typedef struct {
    string zip;  //90210, 11211, 60201 "00391"           // let's keep this as a zip, because otherwise we'll need to pad 0s on zips like 01099
    float longitude;
    float latitude;
    string placeName;
    float color;
    float colorTarget;
} zipCode;

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        vector < zipCode > zipCodes;
    
        ofRectangle map;
        
        float minX, maxX, minY, maxY;
    
        string enteredZip;
        
        float scale;
        float scaleTarget;
        ofPoint center;
        ofPoint centerTarget;
    
    
};
