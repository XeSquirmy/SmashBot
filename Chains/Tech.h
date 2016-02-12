#ifndef TECH_H
#define TECH_H

#include "Chain.h"

class Tech : public Chain
{

public:
    Tech(uint option);
    ~Tech();
    bool IsInterruptible();
    void PressButtons();
    
private:
    uint m_height;
    uint m_option;
    uint m_startingFrame;
    uint IN_PLACE;
    uint LEFT;
    uint RIGHT;
    uint MISSED_UP;
    uint MISSED_ATTACK;
    uint MISSED_LEFT;
    uint MISSED_RIGHT;
 
};

#endif
