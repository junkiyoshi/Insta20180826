#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	this->size_start = 0.001;
	this->size_max = 0.5;

	this->number_of_targets = 15;
	for (int i = 0; i < this->number_of_targets; i++) {

		glm::vec4 target = glm::vec4(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 0.f, 0.f);
		this->targets.push_back(target);

		this->sizes.push_back(ofRandom(this->size_start, this->size_max));
	}

	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < this->sizes.size(); i++) {

		if (this->sizes[i] >= this->size_max) {
			
			this->targets[i] = glm::vec4(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 0.f, 0.f);
			this->sizes[i] = this->size_start;
		}
		else {

			this->sizes[i] += 0.01;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform4fv("targets", &this->targets[0].x, this->number_of_targets);
	this->shader.setUniform1fv("sizes", &this->sizes[0], this->number_of_targets);
	this->shader.setUniform1f("size_max", this->size_max);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(1280, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}