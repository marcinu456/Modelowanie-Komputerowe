#include "ofApp.h"

void write_bmp(const char* path, const unsigned width, const unsigned height, const std::vector<std::vector<float>> data) {
	const unsigned pad = (4 - (3 * width) % 4) % 4, filesize = 54 + (3 * width + pad) * height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
	char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
	for (unsigned i = 0; i < 4; i++) {
		header[2 + i] = (char)((filesize >> (8 * i)) & 255);
		header[18 + i] = (char)((width >> (8 * i)) & 255);
		header[22 + i] = (char)((height >> (8 * i)) & 255);
	}
std:vector<char> img(filesize);
	for (unsigned i = 0; i < 54; i++) img[i] = header[i];
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			const int i = 54 + 3 * x + y * (3 * width + pad);
			img[i] = static_cast<char>(255 * data[x][y]);
			img[i + 1] = static_cast<char>(255 * data[x][y]);
			img[i + 2] = static_cast<char>(255 * data[x][y]);
		}
		for (unsigned p = 0; p < pad; p++) img[54 + (3 * width + p) + y * (3 * width + pad)] = 0;
	}
	std::ofstream file(path, std::ios::out | std::ios::binary);
	file.write(&img[0], filesize);
	file.close();
}


ofApp::~ofApp() {
		std::vector<std::vector<float>> matrix(states.size());
		float max = -1.0;
		for (int i = 0; i < states.size(); i++) {
			matrix[i] = std::vector<float>(states.size());
			for (int j = i + 1; j < states.size(); j++) {
				matrix[i][j] = glm::length(states[i] - states[j]);
				if (matrix[i][j] > max) {
					max = matrix[i][j];
				}
			}
		}
		for (int i = 0; i < states.size(); i++) {
			for (int j = i + 1; j < states.size(); j++) {
				matrix[i][j] = matrix[i][j] / max;
				matrix[j][i] = matrix[i][j];
			}
		}
		write_bmp("test.bmp", states.size(), states.size(), matrix);
	

	ofs_energy.close();

	ofs_positions.close();

	ofs_phases.close();

}


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(false);
	ofSetFrameRate(0);

	for (size_t i = 0; i < numberOfPendulus; i++)
	{
		pendulum.push_back(Pendulum(400, 400, M_PI / 2.0 + 0.15, 150, 1, M_PI / 2.0 + 0.15 + 0.0001 * (i/double(numberOfPendulus)), 150, 1));
	    //pendulum.push_back(Pendulum(400, 400, 0.55 * M_PI, 150, 1, 0.55* M_PI, 150, 1));
		pendulum[i].setColors(ofColor::white, ofColor::red, ofColor::yellow);
	}
	ofs_energy.open("data/energy.txt");
	ofs_positions.open("data/positions.txt");
	ofs_phases.open("data/phases.txt");
	

}

//--------------------------------------------------------------
void ofApp::update() {
	for (size_t i = 0; i < numberOfPendulus; i++)
	{
		//pendulum[i].computeAnglesRunge(.01);
		pendulum[i].computeAnglesEuler(.01);
		pendulum[i].computePosition();
		//pendulum[i].air();
	}

	iter++;

		if (!((iter + 1) % static_cast<unsigned long>(50))) {

			states.emplace_back(pendulum[0].getState());
		}
	


		static unsigned int i_en = 0;
		if (!(i_en % 10)) {
			ofs_energy << pendulum[0].streamEnergy() << " " << pendulum.back().streamEnergy() << "\n";
			i_en = 1;
		}
		else {
			i_en++;
		}
	

		static unsigned int i_pos = 0;
		if (!(i_pos % 10)) {
			ofs_positions << pendulum[0].streamPosition() << " " << pendulum.back().streamPosition() << "\n";
			i_pos = 1;
		}
		else {
			i_pos++;
		}
	
		static unsigned int i_ph = 0;
		if (!(i_ph % 10)) {
			ofs_phases << pendulum[0].streamPhase() << " " << pendulum.back().streamPhase() << "\n";
			i_ph = 1;
		}
		else {
			i_ph++;
		}
	
		/*if (iter > 12000)
		{
			OF_EXIT_APP(0);
		}*/
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (size_t i = 0; i < numberOfPendulus; i++)
	{
		pendulum[i].drawLines();
		//pendulum[i].trails();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
