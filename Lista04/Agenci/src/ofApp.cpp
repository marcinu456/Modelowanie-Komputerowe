#include "ofApp.h"

#include <vector>
#include <fstream>
#include <string>

ofApp::ofApp() :
	countOfPopulation(1000),
	countOfInvected(10),
	PeopleSize(15.0),
	VELOCITY(2.5),
	IllProbolity(0.025),
	IllTime(20),

	population()
{

	for (int i = 0; i < countOfPopulation; i++) {
		Agent agent(ofVec2f(ofRandom(PeopleSize, 1000 - PeopleSize), ofRandom(PeopleSize, 1000 - PeopleSize)), VELOCITY, susceptible);

		population.push_back(agent);
	}

	for (int i = 0; i < countOfInvected; i++) {
		int rand = ofRandom(population.size());
		if (population[rand].state != infected)
		{
			population[rand].state = infected;
			population[rand].recoveryTime = IllTime;
		}
	}

	graph.setup(50, 50, 500, 500);
	graph.setDx(1.0); // which means delta of time
	graph.setColor(ofColor::black);  // ofColor(255,255,255)

	std::string dirName_0 = "data/";
	std::filesystem::create_directory(dirName_0.c_str());
	std::string dirName_1 = dirName_0 + "symulacja" + std::to_string(Reinfected)+"/";
	std::filesystem::create_directory(dirName_1.c_str());
	
	ofs.open((std::string(dirName_1 + "symulacjaProby") + std::to_string(IllProbolity) + ".txt").c_str());
}

//--------------------------------------------------------------
void ofApp::setup() {

}

//--------------------------------------------------------------
void ofApp::update() {

	if(iter<=totalIter){
	for (size_t agent = 0; agent < countOfPopulation; agent++) {
		population[agent].position += population[agent].velocity;
		if (population[agent].position.x < PeopleSize || population[agent].position.x > 1000 - PeopleSize) {
			population[agent].velocity.x = -population[agent].velocity.x;
		}
		if (population[agent].position.y < PeopleSize || population[agent].position.y > 1000 - PeopleSize) {
			population[agent].velocity.y = -population[agent].velocity.y;
		}

		if (population[agent].recoveryTime > 0) {
			population[agent].recoveryTime--;
		}
		else if (population[agent].recoveryTime == 0) {
			population[agent].state = recovered;
			population[agent].recoveryTime--;
		}

		for (size_t people = agent + 1; people < countOfPopulation; people++) {
			if (Reinfected) {
				if (population[people].state == susceptible && population[agent].state == infected && (population[agent].position - population[people].position).length() < PeopleSize * 2 && ofRandom(1.0) < IllProbolity) {
					population[people].state = infected;
					population[people].recoveryTime = IllTime;
				}
				else if (population[people].state == recovered && population[agent].state == infected && (population[agent].position - population[people].position).length() < PeopleSize * 2 && ofRandom(1.0) < IllProbolity / 2) {
					population[people].state = infected;
					population[people].recoveryTime = IllTime;
				}
				else if (population[agent].state == susceptible && population[people].state == infected && (population[agent].position - population[people].position).length() < PeopleSize * 2 && ofRandom(1.0) < IllProbolity) {
					population[agent].state = infected;
					population[agent].recoveryTime = IllTime;
				}
				else if (population[agent].state == recovered && population[people].state == infected && (population[agent].position - population[people].position).length() < PeopleSize * 2 && ofRandom(1.0) < IllProbolity / 2) {
					population[agent].state = infected;
					population[agent].recoveryTime = IllTime;
				}
			}
			else {
				if (population[people].state == susceptible && population[agent].state == infected && (population[agent].position - population[people].position).length() < PeopleSize * 2 && ofRandom(1.0) < IllProbolity) {
					population[people].state = infected;
					population[people].recoveryTime = IllTime;
				}
				else if (population[agent].state == susceptible && population[people].state == infected && (population[agent].position - population[people].position).length() < PeopleSize * 2 && ofRandom(1.0) < IllProbolity) {
					population[agent].state = infected;
					population[agent].recoveryTime = IllTime;
				}
			}
		}
	}


	size_t susceptibleCount = 0;
	size_t infectedCount = 0;
	size_t recoveredCount = 0;
	for (size_t agent = 0; agent < countOfPopulation; agent++) {
		switch (population[agent].state) {
		case susceptible:
			susceptibleCount++;
			break;
		case infected:
			infectedCount++;
			break;
		case recovered:
			recoveredCount++;
			break;
		}
		ofDrawCircle(population[agent].position, PeopleSize);
	}
	ofs << susceptibleCount << " " << infectedCount << " " << recoveredCount << "\n";
	std::vector<float> dane;
	dane.push_back(susceptibleCount);
	dane.push_back(infectedCount);
	dane.push_back(recoveredCount);
	graph.add(dane);
	graph.setAutoScale(true, 1000);

	iter++;
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	for (int i = 0; i < countOfPopulation; i++) {
		Agent& agent = population[i];
		switch (agent.state) {
		case susceptible:
			ofSetColor(ofColor::black);
			break;
		case infected:
			ofSetColor(ofColor::red);
			break;
		case recovered:
			ofSetColor(ofColor::green);
			break;
		}
		ofDrawCircle(agent.position, PeopleSize);
	}

	//graph.draw();
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
