#ifndef MULTISHINE_H
#define MULTISHINE_H

#include "Chain.h"

//Multishines
class Multishine : public Chain
{

public:

    Multishine(uint shineType);
    ~Multishine();
    //Determine what buttons to press in order to execute our tactic
    void PressButtons();
    bool IsInterruptible();
    
private:
    
    uint m_shineType;
    uint crazyMultishine;
    uint shieldMultishine;
    uint normalMultishine;
};

#endif
