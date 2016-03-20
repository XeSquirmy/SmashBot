#ifndef RECOVER_H
#define RECOVER_H

#include "Tactic.h"

//Keep the opponent in the air
class Recover : public Tactic
{

public:
    Recover();
    ~Recover();
    void DetermineChain();
    std::string ToString(){return "Recover";};

private:
    uint m_startingFrame;
    uint FULL;
    uint FULLSHORT;
    uint HALF;
    uint SHORT;
};

#endif
