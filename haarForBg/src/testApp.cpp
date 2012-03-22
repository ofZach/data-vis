#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	//img.loadImage("test.jpg");
	finder.setup("haarcascade_frontalface_default.xml");
	//finder.findHaarObjects(img);
    grabber.initGrabber(320,240);
    
    color = 255;
}

//--------------------------------------------------------------
void testApp::update(){

    grabber.update();
    finder.findHaarObjects(grabber.getPixelsRef());
    
     ofBackground(color, color, color);
}

//--------------------------------------------------------------
void testApp::draw(){
    
    grabber.draw(0, 0);
	
	for(int i = 0; i < finder.blobs.size(); i++) {
		
        ofRectangle cur = finder.blobs[i].boundingRect;
		ofSetColor(255,255,255); //, <#int g#>, <#int b#>)
        ofRect(cur.x, cur.y, cur.width, cur.height);
        
        if (i == 0){
            ofPoint midPt;
            midPt.set(cur.x + cur.width/2, cur.y + cur.height/2);
            color = ofMap(midPt.x, 0,320,0,255);

            
        }
        
        
        
	}
    
    
    
	ofNoFill();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}