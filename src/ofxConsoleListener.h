
#include "ofMain.h"
#include "ofThread.h"

#ifdef __unix__ 
	#include <ncurses.h>
#elif defined(_WIN32) || defined(_WIN64)
	#include <conio.h>
#endif

class ofxConsoleListener : public ofThread {

public:
	enum ReadMode {
		POLL_KEY_MODE = 1,		// Manually check if a new key is available with checkKeyInput()
		POLL_LINE_MODE = 2,		// Manually check if a new line is available with checkLineInput()
		NOTIFY_KEY_MODE = 3,	// Use newKeyEvent to notify that there is a new key available
		NOTIFY_LINE_MODE = 4	// Use newLineEvent to notify that there is a new line available
	};

	ofxConsoleListener();
	ofxConsoleListener(ReadMode mode);
	~ofxConsoleListener();

	ReadMode getReadMode();

	void setup();
	void setup(ReadMode mode);

	void stop();

	int checkKeyInput();
	std::string checkLineInput();

	void threadedFunction();

	ofEvent<int> newKeyEvent;
	ofEvent<std::string> newLineEvent;

private:
	static const int KEY_ARROW_INTRO = 224;
	static const int KEY_ARROW_UP = 72;
	static const int KEY_ARROW_DOWN = 80;
	static const int KEY_ARROW_LEFT = 75;
	static const int KEY_ARROW_RIGHT = 77;
	static const int KEY_ESC = 27;

	void start();
	void clearChannels();

	static int num_instances;
	
	ReadMode readMode;
		
	ofThreadChannel<int> keyChannel;
	ofThreadChannel<std::string> lineChannel;
};
