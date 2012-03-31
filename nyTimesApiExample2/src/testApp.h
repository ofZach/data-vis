#pragma once

#include "ofMain.h"
#include "ofxJSONElement.h"


typedef struct {
    string name;
    int count;
} facet;

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
    
        //ofTrueTypeFont  franklinBook;
        ofxJSONElement json;
    
    
        vector < facet > yearFacets;
        map < string, vector < facet > > subFacets;
    
        int which;
		
};
