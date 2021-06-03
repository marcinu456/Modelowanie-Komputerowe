#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	std::random_device rd;
	std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);
	double d = 0;
	for (int i = 0; i < countOfHouse; i++) {
		ofVec2f test;
		d += 0.5;
		test.x = cos(d) * (2000. / 2 - 1) + 2000 / 2;
		test.y = sin(d) * (2000. / 2 - 1) + 2000 / 2;

		House house(ofVec2f(test.x, test.y), i);
		houses.push_back(house);
		if (i < countOfHouse / 4)
		{
			State s;
		if (i < countOfHouse / 8)
			s = coward;
		else
			s = beard;
		Agent agent(ofVec2f(test.x, test.y), s);
		houses[i].householder.push_back(agent);
		countOfPopulation++;
		}
	}

	for (int i = 0; i < countOfTrees; i++)
	{
		ofVec2f test;
		double alpha = dist(rd) * 2 * M_PI;
		test.x = cos(alpha) * (ofRandom(treeSize, 2000 - treeSize) / 2 - 1) + 2000 / 2;
		test.y = sin(alpha) * (ofRandom(treeSize, 2000 - treeSize) / 2 - 1) + 2000 / 2;
		if (i < numberOfPredators)
		{
			Tree tree(true, test);
			trees.push_back(tree);
		}
		else
		{
			Tree tree(false, test);
			trees.push_back(tree);
		}
		
	}
	std::string dirName_0 = "data/";
	std::filesystem::create_directory(dirName_0.c_str());
	std::string dirName_1 = dirName_0 + "symulacja/";
	std::filesystem::create_directory(dirName_1.c_str());

	ofs.open((std::string(dirName_1 + "symulacjaProby.txt").c_str()));
}

//--------------------------------------------------------------
void ofApp::update(){
	std::random_device rd;
	std::mt19937 gen(rd());
	if (iter <= totalIter) {

		std::vector<Agent*> walkers;
		for (size_t i = 0; i < countOfHouse; i++) {
			House& house = houses[i];
			for (int j = 0; j < house.householder.size(); j++)
			{
				walkers.push_back(&house.householder[j]);
			}
			house.householder.clear();
		}


		size_t cowardP = 0;
		size_t beardP = 0;
		for (int i = 0; i < walkers.size(); i++)
		{
			if (walkers[i]->state == coward)
			{
				cowardP++;
			}
			if (walkers[i]->state == beard)
			{
				beardP++;
			}

		}
		ofs << cowardP << " " << beardP <<"\n";

		std::uniform_int_distribution<int> treeDist(0, countOfTrees-1);
		for (size_t i = 0; i < walkers.size(); i++)
		{
			bool done = true;
			while (done) 
			{
				auto treeNB = treeDist(rd);
				if (trees[treeNB].agents.size() < 2 && walkers.size()!=0)
				{
					trees[treeNB].agents.push_back(walkers[i]);
					done = false;
				}
				else if (walkers.size() == 0)
				{
					done = false;
				}

			}
		}
		for (size_t i = 0; i < countOfTrees; i++)
		{
			Tree& tree = trees[i];
			tree.Eat();
			tree.agents.clear();
		}

		iter++;
		countOfPopulation = 0;
		std::uniform_int_distribution<int> houseDist(0, countOfHouse-1);
		for (size_t j = 0; j < walkers.size(); j++)
		{
			auto houseNB = houseDist(rd);
			Agent& agent = *walkers[j];
			if (agent.currentStatus != false)
			{
				houses[houseNB].householder.push_back(agent);
			}
			else
			{
				int i = 0;
			}
		}

		for (size_t i = 0; i < countOfHouse; i++) {
			House& house = houses[i];
			house.Grow();
			countOfPopulation += house.householder.size();
		}	
	}
	else
	{
		ofExit();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	camera.begin();
	for (int i = 0; i < countOfHouse; i++) {
		House& house = houses[i];
		ofDrawRectangle(house.position, houseSize, houseSize);

		ofSetColor(ofColor::green);
		for (int j = 0; j < house.householder.size(); j++)
		{
			Agent& agent = house.householder[j];
			ofVec2f test;
			test.x = agent.position.x+houseSize * .25;
			test.y = agent.position.y+houseSize*.75;
			if(agent.currentStatus==true)
			ofDrawCircle(test, 10);
		}
		ofSetColor(ofColor::white);
	}
	for (int i = 0; i < countOfTrees; i++) {
		Tree& tree = trees[i];
		ofVec2f p1;
		p1.x = tree.position.x;
		p1.y = tree.position.y;
		ofVec2f p2;
		p2.x = tree.position.x+treeSize;
		p2.y = tree.position.y;
		ofVec2f p3;
		p3.x = tree.position.x + treeSize*.5;
		p3.y = tree.position.y + treeSize;
		ofSetColor(ofColor::green);
		ofDrawTriangle(p1, p2, p3);

		/*ofSetColor(ofColor::green);
		for (int j = 0; j < house.householder.size(); j++)
		{
			Agent& agent = house.householder[j];
			ofVec2f test;
			test.x = agent.position.x+houseSize * .25;
			test.y = agent.position.y+houseSize*.75;
			ofDrawCircle(test, 10);
		}*/
		ofSetColor(ofColor::white);
	}
	ofVec2f test;
	test.x = 1000;
	test.y = 1000;
	ofNoFill();
	ofDrawCircle(test, 1000);
	ofFill();
	camera.end();
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
