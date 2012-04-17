#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(80,80,80);
    
    ofBuffer file = ofBufferFromFile("zips.txt");
    
    // grab the first line, which is just info. 
    string infoLine = file.getNextLine();
    vector < string > info = ofSplitString(infoLine, ",");
    minX = ofToFloat(info[1]);
    maxX = ofToFloat(info[2]);
    minY = ofToFloat(info[3]);
    maxY = ofToFloat(info[4]);
    
    
    while (!file.isLastLine()){
        
        string line = file.getNextLine();
        vector < string > split = ofSplitString(line, "\t");
        
        zipCode tempZip;
        tempZip.zip = split[0];
        tempZip.longitude = ofToFloat(split[1]);
        tempZip.latitude = ofToFloat(split[2]);
        tempZip.placeName = split[3];
        tempZip.color = 1.0;
        tempZip.colorTarget = 1.0;
        zipCodes.push_back(tempZip);
    
    }
    
    map.set(30,30,ofGetWidth()-60, ofGetHeight()-60);
    
    enteredZip = "";
    
    
    scale = 1;
    scaleTarget = 1;
    center.set( minX + (maxX - minX)/2, minY + (maxY - minY)/2);
    centerTarget.set( minX + (maxX - minX)/2, minY + (maxY - minY)/2);
}

//--------------------------------------------------------------
void testApp::update(){
    
    scale = 0.95 * scale + 0.05 * scaleTarget;
    center = 0.95 * center + 0.05 * centerTarget;
    
    for (int i = 0; i < zipCodes.size(); i++){
        zipCodes[i].color = 0.95f * zipCodes[i].color + 0.05 * zipCodes[i].colorTarget;
    }
    // figure out how zoomed in we are. 
    
    if (enteredZip.length() > 0){
        
        
        // find matches
        
        vector < zipCode > zipsThatMatch; 
        
        for (int i = 0; i < zipCodes.size(); i++){
            
            bool bMatch = true;
            for (int j = 0; j < enteredZip.length(); j++){
                if (zipCodes[i].zip[j] != enteredZip[j]){
                    bMatch = false;
                }
            }
            if (bMatch == true){
                zipCodes[i].colorTarget = 1.0;
                zipsThatMatch.push_back(zipCodes[i]); 
            } else {
                
                zipCodes[i].colorTarget = 0.0;
            }
            
        }
        
        
        if (zipsThatMatch.size() > 0){
        
            // now, let's find the min and the max of zipsMatching x/y;
            
            float matchMinX, matchMinY, matchMaxX, matchMaxY;
            
            for (int i = 0;  i < zipsThatMatch.size(); i++){
                if (i == 0){
                    matchMinX = zipsThatMatch[i].longitude;
                    matchMaxX = zipsThatMatch[i].longitude;
                    matchMinY = zipsThatMatch[i].latitude;
                    matchMaxY = zipsThatMatch[i].latitude;
                } else {
                    matchMinX = min(matchMinX, zipsThatMatch[i].longitude);
                    matchMaxX = max(matchMaxX, zipsThatMatch[i].longitude);
                    matchMinY = min(matchMinY, zipsThatMatch[i].latitude);
                    matchMaxY = max(matchMaxY, zipsThatMatch[i].latitude);
                }
            }
            
            // now, let's figure out which we zoom on 
            
            bool bZoomHoriz;
            
            float sizeX = matchMaxX - matchMinX;
            float sizeY = matchMaxY - matchMinY;
            
            float ratio = (float)(maxX-minX) / (float)(maxY-minY);
            float newRatio = (float)sizeX / (float) sizeY;
            
            
            if (newRatio > ratio){
                bZoomHoriz = true;
                if (sizeX > 0.00001)
                scaleTarget =  (float)(maxX-minX) / sizeX;
            
            } else {
                bZoomHoriz = false;
                 if (sizeY > 0.00001)
                scaleTarget = (float)(maxY-minY) / sizeY;
            }
         
            centerTarget.set( matchMinX + (matchMaxX - matchMinX)/2, matchMinY+ (matchMaxY - matchMinY)/2);

            
        } else {
            
            //centerTarget.set( minX + (maxX - minX)/2, minY+ (maxY - minY)/2);
            //scaleTarget = 1;
            
        }
        
    } else {
        
        for (int i = 0; i < zipCodes.size(); i++){
            zipCodes[i].colorTarget = 1.0;
        }
        centerTarget.set( minX + (maxX - minX)/2, minY+ (maxY - minY)/2);
        scaleTarget = 1;
    }
    
    
    

}

//--------------------------------------------------------------
void testApp::draw(){
    
   
    
    ofEnableAlphaBlending();
    
    for (int i = 0; i < zipCodes.size(); i++){
        
        ofSetColor(255,255,255,50 + 205 * zipCodes[i].color);
        
        
        float x = ofMap( (zipCodes[i].longitude - center.x) * scale + (minX + (maxX-minX)/2), minX, maxX, map.x, map.x+map.width);
        float y = ofMap((zipCodes[i].latitude - center.y) * scale+ (minY + (maxY-minY)/2), minY, maxY, map.y+map.height, map.y);
        /*
        float x = ofMap(zipCodes[i].longitude, minX, maxX, map.x, map.x+map.width);
        float y = ofMap(zipCodes[i].latitude, minY, maxY, map.y+map.height, map.y);
        */

        ofRect(x,y,2,2);
        
        
        if (enteredZip.length() == 4 && zipCodes[i].colorTarget > 0){
            ofSetColor(255,255,255);
            string lastDigit;
            lastDigit += zipCodes[i].zip[4];
            ofDrawBitmapString(lastDigit, x+5,y);
        }
        if (enteredZip.length() == 5 && zipCodes[i].colorTarget > 0){
            ofSetColor(255,255,255);
            ofDrawBitmapString(zipCodes[i].placeName, x+5,y);
        }
        
    }
    
    ofSetColor(255,255,255); 
    
    ofDrawBitmapString(enteredZip, 30,30);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    
    if (enteredZip.length() < 5){
        if (key == '0') enteredZip += "0";
        if (key == '1') enteredZip += "1";
        if (key == '2') enteredZip += "2";
        if (key == '3') enteredZip += "3";
        if (key == '4') enteredZip += "4";
        if (key == '5') enteredZip += "5";
        if (key == '6') enteredZip += "6";
        if (key == '7') enteredZip += "7";
        if (key == '8') enteredZip += "8";
        if (key == '9') enteredZip += "9";
    }
    
    if (key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
        if (enteredZip.size() > 0){
            enteredZip.erase(enteredZip.end()-1);
        }
    }
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