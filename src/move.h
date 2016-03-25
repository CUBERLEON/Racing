#ifndef MOVE_H
#define MOVE_H

#include <utility>

class Move
{
public:
    Move(const std::pair<float,float>& speed = {0, 0}) : m_speed(speed) {}
    
    void setSpeed(const std::pair<float,float>& r) { m_speed = r; }
    std::pair<float,float> getSpeed() const { return m_speed; }
protected:
private:
    std::pair<float,float> m_speed;
};

#endif