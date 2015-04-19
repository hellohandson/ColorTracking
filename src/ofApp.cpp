#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    
    w = 320;
    h = 240;
    
    movie.initGrabber(w, h);
    
    rgb.allocate(w, h);
    hsb.allocate(w, h);
    hue.allocate(w, h);
    sat.allocate(w, h);
    bri.allocate(w, h);
    filtered.allocate(w, h);
    
    smiley.loadImage("smiley.png");

}

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();
    
    if(movie.isFrameNew()){
        //copy webcam pixels to rgb image
        rgb.setFromPixels(movie.getPixels(),w,h);
        
        //mirror horizontal
        rgb.mirror(false, true);
        
        //duplicate rgb
        hsb = rgb;
        
        //convert to hsb
        hsb.convertRgbToHsv();
        
        //store the three channels as grayscale images
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        
        //filter image based on the hue value we are looking for!
        for (int i=0; i<w*h; i++){
            filtered.getPixels()[i] = ofInRange(hue.getPixels()[i], findHue-5, findHue+5);
        }
        
        filtered.flagImageChanged();
        
        //run the contour finder on the filtered image to find
        contours.findContours(filtered, 50, w*h/2, 1, false);
                                                
                                                
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //movie.draw(0, 0);
    ofSetColor(255,255,255);
    
    //draw all cv images
    rgb.draw(0,0);
    hsb.draw(640,0);
    hue.draw(0,240);
    sat.draw(320,240);
    bri.draw(640,240);
    filtered.draw(0,480);
    contours.draw(0,480);
    
   // ofSetColor(255, 0, 0);
    ofFill();
    
    //draw red circles for found blobs
    for (int i=0; i<contours.nBlobs; i++) {
       // ofCircle(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 20);
        
        smiley.draw(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 70, 70);
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
    //calculate local mouse x,y in image
    int mx = x % w;
    int my = y % h;
    
    //get hue value on mouse position
    findHue = hue.getPixels()[my*w+mx];
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
