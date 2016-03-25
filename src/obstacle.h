#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "ISerializable.h"

class Obstacle : public ISerializable
{
public:
    Obstacle(std::pair<float, float> pos, float radius, float factor);
    Obstacle(const json& r);
    
    float getPosX() const { return m_pos.first; }
    float getPosY() const { return m_pos.second; }
    float getRadius() const { return m_radius; }
    float getFactor() const { return m_factor; }
    
    json serialize() const;
protected:
private:
    std::pair<float, float> m_pos;
    float m_radius;
    float m_factor;
    
    bool deserialize(const json& r);
};

#endif