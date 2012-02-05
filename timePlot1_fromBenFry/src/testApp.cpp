#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    
    ofBuffer file = ofBufferFromFile("milk-tea-coffee.tsv");
   
    // grab the first line, which is just names. 
    string nameLine = file.getNextLine();
   
    while (!file.isLastLine()){
        string line = file.getNextLine();
        vector < string > split = ofSplitString(line, "\t");
        timeData data;
        data.year = ofToInt(split[0]);
        data.milk = ofToFloat(split[1]);
        data.tea = ofToFloat(split[2]);
        data.coffee = ofToFloat(split[3]);
        dataPoints.push_back(data);
    }
    
    
    // let's find the min and max years, and the max value for the data. 
    // years are easy, we know it's the first and last year of the array.
    
    minYear = dataPoints[0].year;
    maxYear = dataPoints[dataPoints.size()-1].year;
    
    // search lineraly through the data to find the max value;
    
    maxValue = 0;
    for (int i = 0; i < dataPoints.size(); i++){
        if (dataPoints[i].milk > maxValue){
            maxValue = dataPoints[i].milk;
        }
        if (dataPoints[i].coffee > maxValue){
            maxValue = dataPoints[i].coffee;
        }
        if (dataPoints[i].tea > maxValue){
            maxValue = dataPoints[i].tea;
        }
    }
    
    
    dimensions.x = 150;
    dimensions.y = 150;
    dimensions.width = 700;
    dimensions.height = 400;
    
    
    ofBackground(180,180,180);
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    ofSetColor(255,255,255);
    ofRect(dimensions.x, dimensions.y, dimensions.width, dimensions.height);
    
    ofSetColor(90,90,90);
    for (int i = 0; i < dataPoints.size(); i++){
        
        float x = dimensions.x + ofMap( dataPoints[i].year, minYear, maxYear, 0,dimensions.width);
        float y = dimensions.y + ofMap( dataPoints[i].coffee, 0, maxValue, dimensions.height, 0);
        
        ofCircle(x,y, 2);
    }
    
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