#include "testApp.h"



static bool sortOnLinks( topURL A, topURL B ){
    return ( A.numLinks > B.numLinks );
}

static bool sortOnImgs( topURL A, topURL B ){
    return ( A.numImages > B.numImages );
}

static bool sortOnRank( topURL A, topURL B ){
    return ( A.position > B.position );
}




#include "Poco/RegularExpression.h"
using Poco::RegularExpression;

// Some explanation on regular expressions
// http://gnosis.cx/publish/programming/regular_expressions.html

// more info 
// http://www.regular-expressions.info/reference.html




//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(0,0,0);
    ofSetCircleResolution(100);
    ofEnableAlphaBlending();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    // let's get the top 100 sites in text files.  Use CURL so we can handle redirects, etc. 
    
    
     
    
    
    ofBuffer file = ofBufferFromFile("top100Sites.txt");
    
    int count = 0;
    while (!file.isLastLine()){
        
        
        string line = file.getNextLine();
        vector < string > split = ofSplitString(line, ",");
        
        /*
        // do we want to download sites?
        string fileName = ofToDataPath("output_" + ofToString(count) + ".txt");
        cout << "saving " << split[1] << " to " << fileName << endl;
        string command = "curl -L -o " + fileName + " http://www." + split[1] + " &";
        system(command.c_str());
        */
        
        topURL url;
        url.URLname = split[1];
        url.position = count;
        urls.push_back(url);
        
        count ++;
        
        
        
    }
    
    
    // this might take a while, now let's load them in and do some processing!
    
    for (int i = 0; i < urls.size(); i++){
        
        cout << "--------------------------------- " << endl;
        cout << i << endl;
        string htmlAsStr = ofBufferFromFile("output_" + ofToString(i) + ".txt");
        //cout << htmlAsStr << end;
        
        RegularExpression regEx("<a href=\"[^\"]*");
        RegularExpression::Match hrefMatch;
        string contents = htmlAsStr;
        int countOfLinks = 0; 
        // now lets search for img tags in the content 
        // we keep search till we run out of img tags
        while(regEx.match(contents, hrefMatch) != 0) {
            // we get the sub string from the content
            // and then trim the content so that we
            // can continue to search 
            string foundStr = contents.substr(hrefMatch.offset, hrefMatch.length);
            cout << foundStr << endl;
            contents = contents.substr(hrefMatch.offset + hrefMatch.length);
            
            countOfLinks++;
        }
        
        
        RegularExpression regExImg("<img[^>]*src=\"([^\"]*)");
        RegularExpression::Match imgMatch;
        contents = htmlAsStr;
        int countOfImgs = 0; 
        // now lets search for img tags in the content 
        // we keep search till we run out of img tags
        while(regExImg.match(contents, imgMatch) != 0) {
            // we get the sub string from the content
            // and then trim the content so that we
            // can continue to search 
            string foundStr = contents.substr(imgMatch.offset, imgMatch.length);
            contents = contents.substr(imgMatch.offset + imgMatch.length);
            
            countOfImgs++;
        }

        urls[i].numLinks = countOfLinks;
        urls[i].numImages = countOfImgs;
    }
    
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    ofTranslate(0, ofMap(mouseY, 0, ofGetHeight(), 0, -ofGetHeight() * 8));
    
    for (int i = 0; i < urls.size(); i++){
        ofSetColor(255,0,255, 50);
        ofCircle(ofPoint(100, ofMap(i, 0, urls.size(), 0, ofGetHeight() * 8)), urls[i].numLinks/5);
        
        
        ofSetColor(255,255,0, 50);
        ofCircle(ofPoint(100, ofMap(i, 0, urls.size(), 0, ofGetHeight() * 8)), urls[i].numImages/2);
        
    }
    
    for (int i = 0; i < urls.size(); i++){
        ofSetColor(255,255,255);
        ofDrawBitmapString(urls[i].URLname, ofPoint(100, ofMap(i, 0, urls.size(), 0, ofGetHeight() * 8)));
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if (key == 'l'){
        sort(urls.begin(), urls.end(), sortOnLinks);
    }
    
    if (key == 'i'){
        sort(urls.begin(), urls.end(), sortOnImgs);
    }
    
    if (key == 'r'){
        sort(urls.begin(), urls.end(), sortOnRank);
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