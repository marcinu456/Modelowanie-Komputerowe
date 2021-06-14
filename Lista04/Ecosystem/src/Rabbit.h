#pragma once
#include "Agent.h"
#include "ofMain.h"

class Rabbit :
    public Agent
{
private:
public:
    Rabbit(ofVec2f _position, size_t _hp);
    void draw(ofColor color) override;
};

