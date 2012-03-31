#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){

    
    
    
    string baseUrl = "http://api.nytimes.com/svc/search/v1/article?format=json";
    string apiKey = "&api-key=################################:#:########";      // YOUR API KEY GOES HERE 
    
    
    for (int i = 1981; i < 2012; i++){
            
        string query = "&query=china publication_year:[" + ofToString(i) + "]";
        string facets = "&facets=publication_month";
        
        string url = baseUrl + query + facets + apiKey;
        
        cout << "\n\n----------------------------------------" << endl;
        cout << "\n\n" << url << endl;
        
        string data = ofLoadURL(url).data.getText();
        json.parse(data);
        
        cout << "\n\n" << data << endl;

        
        
        int monthCount[12];
        for (int j = 0; j < 12; j++){
            monthCount[j] = 0;
        }
         
        if (json["facets"].size() > 0){
            if (json["facets"]["publication_month"].size() > 0){
                for (int j = 0; j < json["facets"]["publication_month"].size(); j++){
                    
                    string term = json["facets"]["publication_month"][j]["term"].asString();
                    int count = json["facets"]["publication_month"][j]["count"].asInt();
                    int month = ofToInt(term) - 1; // NY times lists the months as 01,02,03, let's convert to it by 0,1,2,3....
                    monthCount[month] = count;
                    
                }
            }
        }
            
        
        for (int j = 0; j < 12; j++){
            chinaResults.push_back(monthCount[j]);
        }
        
        ofSleepMillis(100);

    }
    
    
    for (int i = 1981; i < 2012; i++){
        
        string query = "&query=japan publication_year:[" + ofToString(i) + "]";
        string facets = "&facets=publication_month";
        
        string url = baseUrl + query + facets + apiKey;
        
        //cout << "\n\n----------------------------------------" << endl;
        //cout << "\n\n" << url << endl;
        
        string data = ofLoadURL(url).data.getText();
        json.parse(data);
        
        //cout << "\n\n" << data << endl;
        
        int monthCount[12];
        for (int j = 0; j < 12; j++){
            monthCount[j] = 0;
        }
        
        if (json["facets"].size() > 0){
            if (json["facets"]["publication_month"].size() > 0){
                for (int j = 0; j < json["facets"]["publication_month"].size(); j++){
                    
                    string term = json["facets"]["publication_month"][j]["term"].asString();
                    int count = json["facets"]["publication_month"][j]["count"].asInt();
                    int month = ofToInt(term) - 1; // NY times lists the months as 01,02,03, let's convert to it by 0,1,2,3....
                    monthCount[month] = count;
                    
                }
            }
        }
        
        
        for (int j = 0; j < 12; j++){
            japanResults.push_back(monthCount[j]);
        }
        
        ofSleepMillis(100);
        
    }
    
  
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(217, 138, 134);
    
    
    float width = (float)ofGetWidth() / (float)chinaResults.size(); 
    
    
    int maxValChina = 0;
    int maxValJapan = 0;
    for (int i = 0; i < chinaResults.size(); i++){
        maxValChina = MAX(maxValChina, chinaResults[i]);
        maxValJapan = MAX(maxValJapan, japanResults[i]);
    }
    
    
    ofSetColor(99, 55, 53);
    
    for (int i = 0; i < chinaResults.size(); i++){
        float height = ofMap(chinaResults[i], 0,maxValChina, 0,100);
        ofRect(i * width, ofGetHeight()/2, width, - height);
    }
    
    ofSetColor(31, 103, 103);
    
    for (int i = 0; i < japanResults.size(); i++){
        float height = ofMap(japanResults[i], 0,maxValJapan, 0,100);
        ofRect(i * width, ofGetHeight()/2, width, height);
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