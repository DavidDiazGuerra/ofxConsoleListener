#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60.0);
	ofSetBackgroundColor(54, 54, 54);

	consoleListener.setup(ofxConsoleListener::NOTIFY_LINE_MODE);
	ofAddListener(consoleListener.newLineEvent, this, &ofApp::newLineFromConsole);
}

void ofApp::newLineFromConsole(string & newLine) {
	if (inputLines.size() >= LIST_MAX_SIZE) inputLines.pop_back();
	inputLines.push_front(newLine);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(245, 58, 135);
	ofDrawBitmapString("Echo from the console: ", 10, 20);

	int y = 40;
	ofSetColor(ofColor::white);
	for (auto it = inputLines.begin(); it != inputLines.end(); it++) {
		ofDrawBitmapString(*it, 20, y+=20);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
