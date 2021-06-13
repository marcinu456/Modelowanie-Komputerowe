#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	plants.reserve(PLANT_COUNT);
	for (int i = 0; i < PLANT_COUNT; i++) {
		plants.emplace_back(Plant(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PLANT_MAX_HP));
	}

	preys.reserve(PREY_COUNT);
	for (int i = 0; i < PREY_COUNT; i++) {
		preys.emplace_back(Fox(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PREY_MAX_HUNGRY_HP_LEVEL));
	}

	predators.reserve(PREDATOR_COUNT);
	for (int i = 0; i < PREDATOR_COUNT; i++) {
		predators.emplace_back(Rabbit(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PREDATOR_MAX_HUNGRY_HP_LEVEL));
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

	// prey
	for (int i = 0; i < preys.size(); i++) {
		Fox& prey = preys[i];
		if (prey.hp != 0) {
			prey.hp--;
		}
		else {
			preys.erase(preys.begin() + i);
			i--;
			continue;
		}
	}

	for (int kol = 0; kol < 1; kol++)
	{
		for (int i = 0; i < preys.size(); i++) {
			Fox& prey = preys[i];

			if (prey.hp <= PREY_MAX_HUNGRY_HP_LEVEL) {
				if (plants.size() > 0) {
					size_t atractorIndex = 0;
					ofVec2f atractor = plants[atractorIndex].position - prey.position;
					float atractortDist = atractor.length();
					for (int j = 1; j < plants.size(); j++) {
						Plant& plant = plants[j];
						ofVec2f vec = plant.position - prey.position;
						float dist = vec.length();
						if (dist < atractortDist) {
							atractorIndex = j;
							atractor = vec;
							atractortDist = dist;
						}
					}
					prey.position += atractor / atractortDist * PREY_VELOCITY;

					if ((prey.position - plants[atractorIndex].position).length() < SIZE) {
						plants.erase(plants.begin() + atractorIndex);
						prey.hp = PREY_MAX_HP;
					}
				}
			}
			else {
				size_t atractorIndex = i;
				ofVec2f atractor = prey.position;
				float atractortDist = 1000;
				for (int j = 1; j < preys.size(); j++) {
					Fox& partner = preys[j];
					ofVec2f vec = partner.position - prey.position;
					float dist = vec.length();
					if (dist < atractortDist && partner.hp > PREY_MAX_HUNGRY_HP_LEVEL && j != i) {
						atractorIndex = j;
						atractor = vec;
						atractortDist = dist;
					}
				}
				Fox& partner = preys[atractorIndex];
				if (&prey != &partner) {
					prey.position += atractor / atractortDist * PREY_VELOCITY;
					if ((prey.position - preys[atractorIndex].position).length() < SIZE) {
						prey.hp = PREY_MAX_HUNGRY_HP_LEVEL;
						partner.hp = PREY_MAX_HUNGRY_HP_LEVEL;
						for (int j = 0; j < PREY_REPRODUCE_COUNT; j++) {
							preys.push_back(Fox(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PREY_MAX_HUNGRY_HP_LEVEL));
						}
					}
				}
			}
		}
	}

	// predator
	for (int i = 0; i < predators.size(); i++) {
		Rabbit& predator = predators[i];
		if (predator.hp != 0) {
			predator.hp--;
		}
		else {
			predators.erase(predators.begin() + i);
			i--;
			continue;
		}
	}

	for (int i = 0; i < predators.size(); i++) {
		Rabbit& predator = predators[i];

		if (predator.hp <= PREDATOR_MAX_HUNGRY_HP_LEVEL) {
			if (preys.size() > 0) {
				size_t atractorIndex = 0;
				ofVec2f atractor = preys[atractorIndex].position - predator.position;
				float atractortDist = atractor.length();
				for (int j = 1; j < preys.size(); j++) {
					Fox& prey = preys[j];
					ofVec2f vec = prey.position - predator.position;
					float dist = vec.length();
					if (dist < atractortDist) {
						atractorIndex = j;
						atractor = vec;
						atractortDist = dist;
					}
				}
				predator.position += atractor / atractortDist * PREDATOR_VELOCITY;

				if ((predator.position - preys[atractorIndex].position).length() < SIZE) {
					preys.erase(preys.begin() + atractorIndex);
					predator.hp = PREDATOR_MAX_HP;
				}
			}
		}
		else {
			size_t atractorIndex = i;
			ofVec2f atractor = predator.position;
			float atractortDist = 1000;
			for (int j = 1; j < predators.size(); j++) {
				Rabbit& partner = predators[j];
				ofVec2f vec = partner.position - predator.position;
				float dist = vec.length();
				if (dist < atractortDist && partner.hp > PREDATOR_MAX_HUNGRY_HP_LEVEL && j != i) {
					atractorIndex = j;
					atractor = vec;
					atractortDist = dist;
				}
			}
			Rabbit& partner = predators[atractorIndex];
			if (&predator != &partner) {
				predator.position += atractor / atractortDist * PREDATOR_VELOCITY;
				if ((predator.position - predators[atractorIndex].position).length() < SIZE) {
					predator.hp = PREDATOR_MAX_HUNGRY_HP_LEVEL;
					partner.hp = PREDATOR_MAX_HUNGRY_HP_LEVEL;
					for (int j = 0; j < PREDATOR_REPRODUCE_COUNT; j++) {
						predators.push_back(Rabbit(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), PREDATOR_MAX_HUNGRY_HP_LEVEL));
					}
				}
			}
		}
	}

	if(iter%10 == 0){
		ofs << plants.size() << " " << preys.size() << " " << predators.size() << "\n";
	}
	iter++;
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//cam.begin();

	for (int i = 0; i < plants.size(); i++) {
		//ofDrawCircle(plants[i].position, SIZE);
		ofColor tmp;
		tmp.r = 50;
		tmp.g = 255;
		tmp.b = 0;
		plants[i].draw(tmp);
	}

	for (int i = 0; i < preys.size(); i++) {
		ofColor tmp;
		tmp.r = 50;
		tmp.g = 0;
		tmp.b = 255;
		preys[i].draw(tmp);
	}

	for (int i = 0; i < predators.size(); i++) {
		ofColor tmp;
		tmp.r = 255;
		tmp.g = 0;
		tmp.b = 50;
		predators[i].draw(tmp);
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
