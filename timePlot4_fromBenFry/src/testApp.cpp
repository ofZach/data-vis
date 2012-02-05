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
        
        valuesSmoothed.push_back(0);
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
    
    
    // let's round up to the next "10" on the max value
    maxValue = ceil(maxValue / 10) * 10;

    
    
    dimensions.x = 150;
    dimensions.y = 150;
    dimensions.width = 700;
    dimensions.height = 400;
    
    font.loadFont("bfont.ttf", 20);
    labelFont.loadFont("bFont.ttf", 10);
    
    ofBackground(220,220,220);
    
    which = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){

    
    for (int i = 0; i < valuesSmoothed.size(); i++){
        
        if (which == 0) valuesSmoothed[i] = 0.97f * valuesSmoothed[i] + 0.03 * dataPoints[i].milk;
        if (which == 1) valuesSmoothed[i] = 0.97f * valuesSmoothed[i] + 0.03 * dataPoints[i].tea;
        if (which == 2) valuesSmoothed[i] = 0.97f * valuesSmoothed[i] + 0.03 * dataPoints[i].coffee;

        
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){

    ofSetColor(255,255,255);
    ofRect(dimensions.x, dimensions.y, dimensions.width, dimensions.height);
    
    ofSetColor(90,90,90);
    
    ofBeginShape();
    ofVertex(dimensions.x, dimensions.y + dimensions.height);
    for (int i = 0; i < dataPoints.size(); i++){
        
        float value = valuesSmoothed[i];
      
        float x = dimensions.x + ofMap( dataPoints[i].year, minYear, maxYear, 0,dimensions.width);
        float y = dimensions.y + ofMap( value, 0, maxValue, dimensions.height, 0);
        
        if (i == 0) ofVertex(x,y); 
        ofCurveVertex(x,y);
         if (i == dataPoints.size()-1) ofVertex(x,y); 
        
        //ofCircle(x,y, 2);
    }
    ofVertex(dimensions.x + dimensions.width, dimensions.y + dimensions.height);
    ofEndShape();
    
    if (which == 0) ofSetColor(180,90,90);
    else ofSetColor(90,90,90);
    font.drawString("Milk", dimensions.x, dimensions.y-15);
    
    if (which == 1) ofSetColor(180,90,90);
    else ofSetColor(90,90,90);
    font.drawString("Tea", dimensions.x + 80, dimensions.y-15);
    
    if (which == 2) ofSetColor(180,90,90);
    else ofSetColor(90,90,90);
    font.drawString("Coffee", dimensions.x + 160, dimensions.y-15);
    
    // draw tick marks and labels
    
    for (int i = 0; i < dataPoints.size(); i++){
        
        if (dataPoints[i].year % 10 == 0){
            float x = dimensions.x + ofMap( dataPoints[i].year, minYear, maxYear, 0,dimensions.width);
            float y = dimensions.y + dimensions.height;
            ofSetColor(90,90,90);
            labelFont.drawString(ofToString( dataPoints[i].year), x, y + 20);
            ofSetColor(220,220,220);
            //ofLine(x, y, x,  dimensions.y);
        }
    }
    
    for (int i = 0; i <= (int)maxValue; i++){
        if (i % 10 == 0){
            float x = dimensions.x;
            float y = dimensions.y + ofMap(i, 0, maxValue, dimensions.height, 0);
            
            ofSetColor(90,90,90);
            labelFont.drawString(ofToString( i ), x - 30, y + 5);
            ofLine(x,y, x-5,y);
        }
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

    
    ofRectangle rect = font.getStringBoundingBox("Milk", dimensions.x, dimensions.y-15);
    if (rect.inside(ofPoint(x,y))){
        which = 0;
    }
    
    rect = font.getStringBoundingBox("Tea", dimensions.x + 80, dimensions.y-15);
    if (rect.inside(ofPoint(x,y))){
        which = 1;
    }

    rect = font.getStringBoundingBox("Coffee", dimensions.x + 160, dimensions.y-15);
    if (rect.inside(ofPoint(x,y))){
        which = 2;
    }
        

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