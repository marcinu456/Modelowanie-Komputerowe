#pragma once
#include "Agent.h"
#include "ofMain.h"

class Fox :
    public Agent
{
private:
public:
    Fox(ofVec2f _position, size_t _hp);
    void draw(ofColor color) override;
};

