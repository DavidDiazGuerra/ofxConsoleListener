#include "ofxConsoleListener.h"

int ofxConsoleListener::num_instances = 0;

ofxConsoleListener::ofxConsoleListener() {
	if (num_instances == 0) num_instances++;
	else throw "Only an instance of ofxConsoleListener is allowed.";
}

ofxConsoleListener::ofxConsoleListener(ReadMode mode) : readMode(mode) {
	ofxConsoleListener();
}

ofxConsoleListener::~ofxConsoleListener() {
	// when the class is destroyed
	// close both channels and wait for
	// the thread to finish
	keyChannel.close();
	lineChannel.close();
	num_instances--;
	if (isThreadRunning()) {
		stop();
		waitForThread();
	}
	#ifdef __unix__ 
	endwin();
	#endif
}

ofxConsoleListener::ReadMode ofxConsoleListener::getReadMode() {
	return readMode;
}

void ofxConsoleListener::setup() {
	clearChannels();
	
	#ifdef __unix__ 
	if (readMode == POLL_KEY_MODE || readMode == NOTIFY_KEY_MODE) {
		initscr();
		keypad(stdscr, TRUE);
		noecho();
	}
	#endif
	
	start();
}

void ofxConsoleListener::setup(ReadMode mode) {
	if (isThreadRunning()) throw "ofxConsoleListener is already running.";
	else {
		readMode = mode;
		setup();
	}
}

// Start the thread.
void ofxConsoleListener::start() {
	startThread(false);
}

// Stop the thread.
void ofxConsoleListener::stop() {
	stopThread(); // The thread won't stop until a new key or line is writed in the console
	cout << "Press enter to finish the console listener." << endl;
	// terminate(); // It generates an ugly exception
}

// Check if there's a new key in the console input.
// It returns an int with the value of the oldest nonreaded key in the 
// input or -1 if there wasn't any.
// It rasises an exception if the readMode is not READ_CHAR_MODE.
int ofxConsoleListener::checkKeyInput() {
	if (readMode != POLL_KEY_MODE) throw "checkKeyInput() can only be used in POLL_KEY_MODE";
	else {
		int newChar;
		if (keyChannel.tryReceive(newChar)) {
			return newChar;
		}
		else return -1;
	}
}

// Check if there's a new line in the console input.
// It returns a string with the oldest nonreaded line input or an
// emtpy string if there wasn't any.
// It rasises an exception if the readMode is not READ_LINE_MODE.
std::string ofxConsoleListener::checkLineInput() {
	if (readMode != POLL_LINE_MODE) throw "line asked while being in READ_CHAR_MODE";
	else {
		std::string newLine;
		if (lineChannel.tryReceive(newLine)) {
			return newLine;
		}
		else return "";
	}
}

/// Everything in this function will happen in a different
/// thread which leaves the main thread completelty free for
/// other tasks.
void ofxConsoleListener::threadedFunction() {
	if (readMode == POLL_KEY_MODE || readMode == NOTIFY_KEY_MODE) {
		int c;
		while (isThreadRunning()) {
			c = getch();
			#ifdef __unix__ 
			switch (c) {
			case KEY_UP:    c = OF_KEY_UP;    break;
			case KEY_DOWN:  c = OF_KEY_DOWN;  break;
			case KEY_RIGHT: c = OF_KEY_RIGHT; break;
			case KEY_LEFT:  c = OF_KEY_LEFT;  break;
			}
			#elif defined(_WIN32) || defined(_WIN64)
			if (c == KEY_ARROW_INTRO) {
				switch (getch()) {
				case ofxConsoleListener::KEY_ARROW_UP:    c = OF_KEY_UP;    break;
				case ofxConsoleListener::KEY_ARROW_DOWN:  c = OF_KEY_DOWN;  break;
				case ofxConsoleListener::KEY_ARROW_RIGHT: c = OF_KEY_RIGHT; break;
				case ofxConsoleListener::KEY_ARROW_LEFT:  c = OF_KEY_LEFT;  break;
				}
			}
			#endif
			if (isThreadRunning()) {
				if (readMode == POLL_KEY_MODE)
					keyChannel.send(c);
				else ofNotifyEvent(newKeyEvent, c);
			}
		}
	}
	else if (readMode == POLL_LINE_MODE || readMode == NOTIFY_LINE_MODE) {
		std::string line;
		while (isThreadRunning()) {
			std::getline(std::cin, line);
			if (isThreadRunning()) {
				if (readMode == POLL_LINE_MODE) lineChannel.send(line);
				else ofNotifyEvent(newLineEvent, line);
			}
		}
	}
}

void ofxConsoleListener::clearChannels() {
	int keyTrash;
	while (keyChannel.tryReceive(keyTrash));
	std::string lineTrash;
	while (lineChannel.tryReceive(lineTrash));
}
