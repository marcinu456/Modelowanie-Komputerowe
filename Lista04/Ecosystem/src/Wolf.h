#pragma once
#include "Agent.h"
class Wolf :
    public Agent
{
public:
    Wolf(ofVec2f _position, size_t _hp);
    void draw(ofColor color) override;
};

