#include "obstacle.h"

Obstacle::Obstacle(std::pair<float, float> pos, float radius, float factor)
: m_pos(pos), m_radius(radius), m_factor(factor)
{}

Obstacle::Obstacle(const json& r) 
{
    if (!deserialize(r)) {
        throw std::runtime_error("Obstacle creation failed!");
        exit(1);  
    } 
}

json Obstacle::serialize() const {
    json r;
    r["pos"]["x"] = m_pos.first;
    r["pos"]["y"] = m_pos.second;
    r["radius"] = m_radius;
    r["factor"] = m_factor;
    return r;
}

bool Obstacle::deserialize(const json& r) {
    try {
        m_pos.first = r["pos"]["x"];
        m_pos.second = r["pos"]["y"];
        m_radius = r["radius"];
        m_factor = r["factor"];
    } catch (const std::exception& e) {
        std::cerr << e.what();
        return false;
    }
    return true;
}