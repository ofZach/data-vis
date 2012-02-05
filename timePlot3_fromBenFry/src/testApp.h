#pragma once

#include "ofMain.h"


typedef struct {
    
    int year;
    float milk;
    float tea;
    float coffee;
    
} timeData;


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
		
    
    
        vector < timeData > dataPoints;
        
        
        int minYear;
        int maxYear;
        float maxValue;
    
        ofRectangle dimensions;
    
        ofTrueTypeFont font;
        ofTrueTypeFont labelFont;
    
        int which;
        
    
};
