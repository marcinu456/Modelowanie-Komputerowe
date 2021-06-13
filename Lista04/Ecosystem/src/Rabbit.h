#pragma once
#include "Agent.h"
class Rabbit :
    public Agent
{
public:
    Rabbit(ofVec2f _position, size_t _hp);
    void draw(ofColor color) override;
};

