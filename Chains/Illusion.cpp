#include <iostream>

#include "Illusion.h"

void Illusion::PressButtons()
{   //TODO: Implement detection of distance from stage to determine if shortening is a good option
    uint frame = m_state->m_memory->frame - m_startingFrame;
    if(m_isFacingRight == true)
    {
        m_controller->tiltAnalog(Controller::BUTTON_MAIN, 0, 0.5);
        m_controller->pressButton(Controller::BUTTON_B);
        std::cout << "Illusion to the left" << std::endl;
        return;
    }
    else
    {
        m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
        m_controller->pressButton(Controller::BUTTON_B);
        std::cout << "Illusion to the right" << std::endl;
        return;
    }
}
bool Illusion::IsInterruptible()
{
    return true;
}

Illusion::Illusion(bool isFacingRight, uint shortenLength)
{
    m_isFacingRight = isFacingRight;
    m_shortenLength = shortenLength;
    m_startingFrame = m_state->m_memory->frame;
}

Illusion::~Illusion()
{
}

