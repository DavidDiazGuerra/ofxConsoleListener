#pragma once

#include "ofMain.h"

#include "ofxConsoleListener.h"

#define MIN_FONT_SIZE 12
#define MAX_FONT_SIZE 64

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxConsoleListener consoleListener;

		std::string letter;
		ofTrueTypeFont trueTypeFont;
		ofColor color;
		int x, y;
};
