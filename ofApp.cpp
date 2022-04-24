#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);

	this->hexagon_height = 8;
	this->hexagon_width = 4;

	for (float x = this->hexagon_width * 9; x <= ofGetWidth() - this->hexagon_width * 9; x += this->hexagon_height * 1.5) {

		for (float y = this->hexagon_height * 3; y <= ofGetHeight() - this->hexagon_height * 3; y += this->hexagon_height * 3) {

			this->number_list.push_back(make_pair(glm::vec2(x, y), 0));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	
	for (int i = 0; i < this->number_list.size(); i++) {

		this->number_list[i].second = this->number_list[i].second > 0 ? this->number_list[i].second - 2 : 0;
		auto noise_value = ofNoise(glm::vec3(this->number_list[i].first * 0.005, ofGetFrameNum() * 0.01));

		if (noise_value > 0.7) {

			this->number_list[i].second = this->number_list[i].second < 100 ? this->number_list[i].second + 4 : 100;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (auto& number : this->number_list) {

		if (number.second > 0) {

			auto alpha = 255;
			if (number.second <= 30) {
			
				alpha = ofMap(number.second, 0, 30, 0, 255);
			}
			int number_index = ofMap(ofNoise(glm::vec3(number.first * 0.05, ofGetFrameNum() * 0.02)), 0, 1, 0, 10);
			this->draw_digital(number.first, number_index, alpha);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_digital(glm::vec2 location, int number_index, float alpha) {

	vector<pair<glm::vec2, float>> part_list = {
		make_pair<glm::vec2, float>(location + glm::vec2(0, -this->hexagon_height), 90),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * 0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * 0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(0, 0), 90),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * -0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * -0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(0, this->hexagon_height), 90)
	};

	vector<vector<int>> index_list = {
		{ 0, 1, 2, 4, 5, 6 },
		{ 2, 5 },
		{ 0, 1, 3, 5, 6 },
		{ 0, 2, 3, 5, 6 },
		{ 2, 3, 4, 5 },
		{ 0, 2, 3, 4, 6 },
		{ 0, 1, 2, 3, 4, 6 },
		{ 0, 2, 5 },
		{ 0, 1, 2, 3, 4, 5, 6 },
		{ 0, 2, 3, 4, 5, 6 },
	};

	for (auto& index : index_list[number_index]) {

		this->draw_hexagon(part_list[index].first, part_list[index].second, alpha);
	}
}

//--------------------------------------------------------------
void ofApp::draw_hexagon(glm::vec2 location, float deg, float alpha) {

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(deg);

	vector<glm::vec2> vertices;
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * 0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height * 0.5));
	vertices.push_back(glm::vec2(this->hexagon_width * 0.4, this->hexagon_height * 0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * 0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height * -0.5));

	ofFill();
	ofSetColor(ofColor(0, alpha));

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(ofColor(128, 255, 255, alpha));

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}