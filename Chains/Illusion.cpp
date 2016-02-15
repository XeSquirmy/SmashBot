#include <iostream>

#include "Illusion.h"

void Illusion::PressButtons()
{   //TODO: Implement detection of distance from stage to determine if shortening is a good option
    uint frame = m_state->m_memory->frame - m_startingFrame;
    switch(frame)
    {
        case 0:
        {
            m_controller->tiltAnalog(Controller::BUTTON_MAIN, m_isOnRight ? 0 : 1, 0.5);
            m_controller->pressButton(Controller::BUTTON_B);
            break;
        }
        case 1:
        {
            m_controller->releaseButton(Controller::BUTTON_B);
        }
        case 19:
        {
            if(m_shortenLength == SHORT)
            {
                m_controller->pressButton(Controller::BUTTON_B);
                break;
            }
            else
            {
                break;
            }
        }
        case 20:
        {
            if(m_shortenLength == HALF)
            {
                m_controller->pressButton(Controller::BUTTON_B);
                break;
            }
            else
            {
                break;
            }
        }
        case 21:
        {
            if(m_shortenLength == FULLSHORT)
            {
                m_controller->pressButton(Controller::BUTTON_B);
                break;
            }
            else
            {
                break;
            }
        }
        case 22:
        {
            m_controller->emptyInput();
            break;
        }
        return;
    }
}
bool Illusion::IsInterruptible()
{
    return true;
}

Illusion::Illusion(bool isOnRight, uint shortenLength)
{
    m_isOnRight = isOnRight;
    m_shortenLength = shortenLength;
    m_startingFrame = m_state->m_memory->frame;
    FULL = 0;
    FULLSHORT = 1;
    HALF = 2;
    SHORT = 3;
}

Illusion::~Illusion()
{
}

