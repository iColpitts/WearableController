#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
    
    score = 0;
	
	bSendSerialMessage = false;
	ofBackground(255);	
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	font.loadFont("DIN.otf", 64);
	
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 9600;
	serial.setup(0, baud); //open the first device
	//serial.setup("COM4", baud); // windows example
	//serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);
}

//--------------------------------------------------------------
void testApp::update(){
	
	if (serial.available() > 0){
		
        serial.writeByte('a');
        
		nTimesRead = 0;
		nBytesRead = 0;
		int nRead  = 0;  // a temp variable to keep count per read
		
		unsigned char bytesReturned[3];
		
		memset(bytesReadString, 0, 4);
		memset(bytesReturned, 0, 3);
		
		while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
			nTimesRead++;	
			nBytesRead = nRead;
		};
		
		memcpy(bytesReadString, bytesReturned, 3);
		randomNumber = ofRandom(100);
		bSendSerialMessage = false;
		readTime = ofGetElapsedTimef();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
		//randomNumber = ofRandom(100);
        if (randomNumber < 15) {
            hitOrMiss = "Hit";
            serial.writeByte('h');
            score ++;
            ofSleepMillis(1000);
        } else {
            hitOrMiss = "Miss";
        }
        ofSetColor(0);
	} else {
		ofSetColor(220);
	}
	
    string msg;
	msg += "BANG! \n";
    
    font.drawString(msg, 300, 250);
    font.drawString(hitOrMiss, 300, 400);
    font.drawString("Score:" + ofToString(score), 300, 550);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	bSendSerialMessage = true;
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

