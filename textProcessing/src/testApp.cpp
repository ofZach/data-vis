#include "testApp.h"



bool sortByCount(const wordCountValue & a, const wordCountValue & b){
    
    return a.count > b.count;
}


//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(0,0,0);
    ofSetCircleResolution(100);
    ofEnableAlphaBlending();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    // let's get the top 100 sites in text files.  Use CURL so we can handle redirects, etc. 
    
    
     
    
    
    ofBuffer file = ofBufferFromFile("kingSpeech.txt");
    string textAsString = file;
    
    //let's get rid of every period, comma, tab, newline
    
    for (int i = 0; i < textAsString.size(); i++){
        if (textAsString[i] == '.'){
            textAsString[i] = ' ';
        }
        if (textAsString[i] == '\n'){
            textAsString[i] = ' ';
        }
        if (textAsString[i] == '\t'){
            textAsString[i] = ' ';
        }
        if (textAsString[i] == ','){
            textAsString[i] = ' ';
        }
        if (textAsString[i] == '!'){
            textAsString[i] = ' ';
        }
        if (textAsString[i] == '!'){
            textAsString[i] = ' ';
        }
        if (textAsString[i] == ':'){
            textAsString[i] = ' ';
        }
        if (textAsString[i] == '\"'){
            textAsString[i] = ' ';
        }
    }
    
    
    vector < string > textBrokenUp = ofSplitString(textAsString, " ", true, true);
    for (int i = 0; i < textBrokenUp.size(); i++){
        bool bAnyMatch = false;
        int whichMatch = -1;
        for (int j = 0; j < words.size(); j++){
            if (textBrokenUp[i] == words[j].word){
                whichMatch = j;
                bAnyMatch = true;
            }
        }
        
        if (bAnyMatch == true){
            words[whichMatch].count++;
        } else {
            wordCountValue temp;
            temp.word = textBrokenUp[i];
            temp.count = 1;
            words.push_back(temp);
        }
    }
    
    sort(words.begin(), words.end(), sortByCount);
    
    for (int i = 0; i < words.size(); i++){
        cout << words[i].word << " " << words[i].count << endl;
    }
    
   
    
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    
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