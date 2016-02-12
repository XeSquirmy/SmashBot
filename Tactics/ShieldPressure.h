#ifndef SHIELDPRESSURE_H
#define SHIELDPRESSURE_H

#include "Tactic.h"

class ShieldPressure : public Tactic
{

public:
    ShieldPressure();
    ~ShieldPressure();
    void DetermineChain();
    
private:
    uint m_hitlagFramesLeftP1;
    uint m_hitlagFramesLeftP2;
    uint m_startingFrame;
    uint crazyMultishine;
    uint shieldMultishine;
    uint normalMultishine;
    bool m_isFacingRightP1;
    bool m_isFacingRightP2;
    
};

#endif
