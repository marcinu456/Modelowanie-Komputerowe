#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	for (int i = 0; i < PLANT_COUNT; i++) {
		plants.push_back(Plant(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PLANT_MAX_HP));
	}


	for (int i = 0; i < RABBIT_COUNT; i++) {
		rabbits.push_back(Rabbit(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), RABBIT_MAX_HUNGRY_HP_LEVEL));
	}


	for (int i = 0; i < WOLF_COUNT; i++) {
		wolfes.push_back(Wolf(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), WOLF_MAX_HUNGRY_HP_LEVEL));
	}

	std::string dirName_0 = "data/";
	std::filesystem::create_directory(dirName_0.c_str());

	ofs.open((std::string(dirName_0 + "test.txt").c_str()));

}

//--------------------------------------------------------------
void ofApp::update() {


	// plant
	if (iter % PLANT_REPRODUCE_TIME == 0) {
		for (int i = 0; i < PLANT_REPRODUCE_COUNT; i++) {
			plants.push_back(Plant(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PLANT_MAX_HP));
		}
	}



	for (int i = 0; i < plants.size(); i++) {
		Plant& plant = plants[i];
		if (plant.hp != 0) {
			plant.hp--;
		}
		else {
			plants.erase(plants.begin() + i);
			i--;
			continue;
		}
	}

	// rabbits

	if (rabbits.size() == 0)
	{
		for (int i = 0; i < RABBIT_COUNT; i++) {
			rabbits.push_back(Rabbit(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), RABBIT_MAX_HUNGRY_HP_LEVEL));
		}
	}

	for (int i = 0; i < rabbits.size(); i++) {
		Rabbit& rabbit = rabbits[i];
		if (rabbit.hp != 0) {
			rabbit.hp--;
		}
		else {
			rabbits.erase(rabbits.begin() + i);
			i--;
			continue;
		}
	}

	for (int i = 0; i < rabbits.size(); i++) {
		Rabbit& rabbit = rabbits[i];

		if (rabbit.hp <= RABBIT_MAX_HUNGRY_HP_LEVEL) {
			if (plants.size() > 0) {
				size_t atractorIndex = 0;
				ofVec2f atractor = plants[atractorIndex].position - rabbit.position;
				float atractortDist = atractor.length();
				for (int j = 1; j < plants.size(); j++) {
					Plant& plant = plants[j];
					ofVec2f vec = plant.position - rabbit.position;
					float dist = vec.length();
					if (dist < atractortDist) {
						atractorIndex = j;
						atractor = vec;
						atractortDist = dist;
					}
				}
				rabbit.position += atractor / atractortDist * RABBIT_VELOCITY;

				if ((rabbit.position - plants[atractorIndex].position).length() < SIZE) {
					plants.erase(plants.begin() + atractorIndex);
					rabbit.hp = RABBIT_MAX_HP;
				}
			}
		}
		else {
			size_t atractorIndex = i;
			ofVec2f atractor = rabbit.position;
			float atractortDist = 1000;
			for (int j = 1; j < rabbits.size(); j++) {
				Rabbit& partner = rabbits[j];
				ofVec2f vec = partner.position - rabbit.position;
				float dist = vec.length();
				if (dist < atractortDist && partner.hp > RABBIT_MAX_HUNGRY_HP_LEVEL && j != i) {
					atractorIndex = j;
					atractor = vec;
					atractortDist = dist;
				}
			}
			Rabbit& partner = rabbits[atractorIndex];
			if (&rabbit != &partner) {
				rabbit.position += atractor / atractortDist * RABBIT_VELOCITY;
				if ((rabbit.position - rabbits[atractorIndex].position).length() < SIZE) {
					rabbit.hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
					partner.hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
					for (int j = 0; j < RABBIT_REPRODUCE_COUNT; j++) {
						rabbits.push_back(Rabbit(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), RABBIT_MAX_HUNGRY_HP_LEVEL));
					}
				}
			}
		}
	}
	

	// wolfes

	if (wolfes.size() == 0)
	{
		for (int i = 0; i < WOLF_COUNT; i++) {
			wolfes.push_back(Wolf(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), WOLF_MAX_HUNGRY_HP_LEVEL));
		}
	}

	for (int i = 0; i < wolfes.size(); i++) {
		Wolf& wolf = wolfes[i];
		if (wolf.hp != 0) {
			wolf.hp--;
		}
		else {
			wolfes.erase(wolfes.begin() + i);
			i--;
			continue;
		}
	}

	for (int i = 0; i < wolfes.size(); i++) {
		Wolf& wolf = wolfes[i];

		if (wolf.hp <= WOLF_MAX_HUNGRY_HP_LEVEL) {
			if (rabbits.size() > 0) {
				size_t atractorIndex = 0;
				ofVec2f atractor = rabbits[atractorIndex].position - wolf.position;
				float atractortDist = atractor.length();
				for (int j = 1; j < rabbits.size(); j++) {
					Rabbit& rabbit = rabbits[j];
					ofVec2f vec = rabbit.position - wolf.position;
					float dist = vec.length();
					if (dist < atractortDist) {
						atractorIndex = j;
						atractor = vec;
						atractortDist = dist;
					}
				}
				wolf.position += atractor / atractortDist * WOLF_VELOCITY;

				if ((wolf.position - rabbits[atractorIndex].position).length() < SIZE) {
					rabbits.erase(rabbits.begin() + atractorIndex);
					wolf.hp = WOLF_MAX_HP;
				}
			}
		}
		else {
			size_t atractorIndex = i;
			ofVec2f atractor = wolf.position;
			float atractortDist = 1000;
			for (int j = 1; j < wolfes.size(); j++) {
				Wolf& partner = wolfes[j];
				ofVec2f vec = partner.position - wolf.position;
				float dist = vec.length();
				if (dist < atractortDist && partner.hp > WOLF_MAX_HUNGRY_HP_LEVEL && j != i) {
					atractorIndex = j;
					atractor = vec;
					atractortDist = dist;
				}
			}
			Wolf& partner = wolfes[atractorIndex];
			if (&wolf != &partner) {
				wolf.position += atractor / atractortDist * WOLF_VELOCITY;
				if ((wolf.position - wolfes[atractorIndex].position).length() < SIZE) {
					wolf.hp = WOLF_MAX_HUNGRY_HP_LEVEL;
					partner.hp = WOLF_MAX_HUNGRY_HP_LEVEL;
					for (int j = 0; j < WOLF_REPRODUCE_COUNT; j++) {
						wolfes.push_back(Wolf(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), WOLF_MAX_HUNGRY_HP_LEVEL));
					}
				}
			}
		}
	}

	if (iter % 10 == 0) {
		ofs << plants.size() << " " << rabbits.size() << " " << wolfes.size() << "\n";
	}
	iter++;

}

//--------------------------------------------------------------
void ofApp::draw() {
	//cam.begin();

	for (int i = 0; i < plants.size(); i++) {
		//ofDrawCircle(plants[i].position, SIZE);
		ofColor tmp;
		tmp.r = 50;
		tmp.g = 255;
		tmp.b = 0;
		plants[i].draw(tmp);
	}

	for (int i = 0; i < rabbits.size(); i++) {
		ofColor tmp;
		tmp.r = 50;
		tmp.g = 0;
		tmp.b = 255;
		rabbits[i].draw(tmp);
	}

	for (int i = 0; i < wolfes.size(); i++) {
		ofColor tmp;
		tmp.r = 255;
		tmp.g = 0;
		tmp.b = 50;
		wolfes[i].draw(tmp);
	}
	//ofDisableDepthTest();
	//cam.end();
	
}

//--------------------------------------------------------------
ofApp::~ofApp() {
	ofs.close();
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
