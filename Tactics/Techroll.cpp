#include <iostream>
#include <string>

#include "Techroll.h"
#include "../Chains/Tech.h"

Techroll::Techroll()
{
    m_chain = NULL;
    /*std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,7);
    randomNumber = distribution(generator);*/
    IN_PLACE = 0;
    LEFT = 1;
    RIGHT = 2;
    MISSED_UP = 3;
    MISSED_ATTACK = 4;
    MISSED_LEFT = 5;
    MISSED_RIGHT = 6;
}

Techroll::~Techroll()
{
    delete m_chain;
}

void Techroll::DetermineChain()
{
    CreateChain2(Tech, IN_PLACE);
    m_chain->PressButtons();
    return;
}
