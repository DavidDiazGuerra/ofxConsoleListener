#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60.0);
	ofSetBackgroundColor(54, 54, 54);

	consoleListener.setup(ofxConsoleListener::POLL_KEY_MODE);
	#ifdef __unix__
		printw("Introduce a character to print it and use the arrows to move it.\n");
	#elif defined(_WIN32) || defined(_WIN64)
		printf("Introduce a character to print it and use the arrows to move it.\n");
	#endif


	x = ofGetWidth() / 2 - 64;
	y = ofGetHeight() / 2 + 32;

	trueTypeFont.load("cooperBlack.ttf", 128);
}

//--------------------------------------------------------------
void ofApp::update(){
	int key = consoleListener.checkKeyInput();
	if (key != -1) {
		switch (key) {
		case OF_KEY_ESC:   ofExit(); break;
		case OF_KEY_UP: y--; break;
		case OF_KEY_DOWN: y++; break;
		case OF_KEY_LEFT: x--; break;
		case OF_KEY_RIGHT: x++; break;
		default:
			letter = std::string(1, (char)key);
			color = ofColor((int)ofRandom(64, 255), (int)ofRandom(64, 255), (int)ofRandom(64, 255));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(ofColor::white);
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 5, 15);
	ofDrawBitmapString("Introduce a character in the console to print it\nand use the arrows to move it.", 5, 275);

	ofSetColor(color);
	trueTypeFont.drawString(letter, x, y);
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
