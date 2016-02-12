#ifndef TECHROLL_H
#define TECHROLL_H

#include "Tactic.h"

class Techroll : public Tactic
{

public:
    Techroll();
    ~Techroll();
    void DetermineChain();

private:
    
    uint IN_PLACE;
    uint LEFT;
    uint RIGHT;
    uint MISSED_UP;
    uint MISSED_ATTACK;
    uint MISSED_LEFT;
    uint MISSED_RIGHT;
};

#endif
