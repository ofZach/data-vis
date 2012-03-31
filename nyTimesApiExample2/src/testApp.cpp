#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){

    
    
    
    string baseUrl = "http://api.nytimes.com/svc/search/v1/article?format=json";
    string apiKey = "&api-key=################################:#:########";         /// YOUR API KEY GOES HERE 
    string query = "&query=publication_year:[2011]";
    string facets = "&facets=per_facet,org_facet";
    
    string url = baseUrl + query + facets + apiKey;
    string data = ofLoadURL(url).data.getText();
   
    json.parse(data);
    
    
    for (int i = 0; i < json["facets"]["org_facet"].size(); i++){
        string name = json["facets"]["org_facet"][i]["term"].asString();
        int count = json["facets"]["org_facet"][i]["count"].asInt();
        facet tempFacet;
        tempFacet.name = name;
        tempFacet.count = count;
        yearFacets.push_back(tempFacet);
    }
    
    for (int i = 0; i < json["facets"]["per_facet"].size(); i++){
        string name = json["facets"]["per_facet"][i]["term"].asString();
        int count = json["facets"]["per_facet"][i]["count"].asInt();
        facet tempFacet;
        tempFacet.name = name;
        tempFacet.count = count;
        yearFacets.push_back(tempFacet);
    }
    
    ofSleepMillis(100); 

    
    for (int i = 0; i < yearFacets.size(); i++){
        
        string queryName = yearFacets[i].name;
        query = "&query='" + yearFacets[i].name + "' publication_year:[2011]";
        string facets = "&facets=per_facet,org_facet";
        
        string url = baseUrl + query + facets + apiKey;
        
        cout << url << endl;
        string data = ofLoadURL(url).data.getText();
        
        json.parse(data);
        
        for (int i = 0; i < json["facets"]["per_facet"].size(); i++){
            string name = json["facets"]["per_facet"][i]["term"].asString();
            int count = json["facets"]["per_facet"][i]["count"].asInt();
            facet tempFacet;
            tempFacet.name = name;
            tempFacet.count = count;
            subFacets[queryName].push_back(tempFacet);
        }
        
        for (int i = 0; i < json["facets"]["org_facet"].size(); i++){
            string name = json["facets"]["org_facet"][i]["term"].asString();
            int count = json["facets"]["org_facet"][i]["count"].asInt();
            facet tempFacet;
            tempFacet.name = name;
            tempFacet.count = count;
            subFacets[queryName].push_back(tempFacet);
        }
        
        
        ofSleepMillis(100);
    }
    

    which = 0;
    
    
}

//--------------------------------------------------------------
void testApp::update(){

        
}


//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0,0,0);
    
    for (int i = 0; i < yearFacets.size(); i++){
        if (i == which) ofSetColor(255,0,128);
        else ofSetColor(255,255,255);
        ofDrawBitmapString(yearFacets[i].name, ofPoint(20, 20 + i * 20));
    }
    
    ofSetColor(255, 255, 255);
    
    string name = yearFacets[which].name;
    
    for (int i = 0; i < subFacets[name].size(); i++){
        ofSetColor(255,255,255);
        ofDrawBitmapString(subFacets[name][i].name, ofPoint(360, 20 + i * 20));
    }

    	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    
    which++;
    which %= yearFacets.size();
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