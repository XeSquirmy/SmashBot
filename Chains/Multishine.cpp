#include "Multishine.h"

Multishine::Multishine(uint shineType)
{
    m_startingFrame = m_state->m_memory->frame;
    m_shineType = shineType;
    crazyMultishine = 0;
    shieldMultishine = 1;
    normalMultishine = 2;
}

Multishine::~Multishine()
{
}

bool Multishine::IsInterruptible()
{
    uint frame = m_state->m_memory->frame - m_startingFrame;
    if(frame >= 15)
    {
        return true;
    }
    if(m_shineType == shieldMultishine)
    {
        return false;
    }
    return false;
}

void Multishine::PressButtons()
{
    uint frame = m_state->m_memory->frame - m_startingFrame;
    if(m_shineType == shieldMultishine)
    {
        switch(frame)
        {
            case 0:
            {
                //Down-B
                m_controller->pressButton(Controller::BUTTON_B);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 0);
                break;
            }
            case 8:
            {
                //Let go of Down-B
                m_controller->releaseButton(Controller::BUTTON_B);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, .5);

                //Jump
                m_controller->pressButton(Controller::BUTTON_Y);

                break;
            }
            case 9:
            {
                //Let go of Jump
                m_controller->releaseButton(Controller::BUTTON_Y);
                break;
            }
            case 11:
            {
                //Down-B again
                m_controller->pressButton(Controller::BUTTON_B);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 0);
                break;
            }
            case 12:
            {
                //Let go of Down-B
                m_controller->releaseButton(Controller::BUTTON_B);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, .5);
                m_controller->emptyInput();
                break;
            }
        }
    }
    
    if(m_shineType == crazyMultishine)
    {
        switch(frame)
        {
            case 0:
            {
                //Down-B
                m_controller->releaseButton(Controller::BUTTON_Y);
                m_controller->pressButton(Controller::BUTTON_B);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 0);
                break;
            }
            case 1:
            {
                //Release B button in order to be able to add extra shield pressure
                m_controller->releaseButton(Controller::BUTTON_B);
                break;
            }
            case 3:
            {
                //reset stick to inactive state
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, .5);
                //jump
                m_controller->pressButton(Controller::BUTTON_Y);
                break;
            }
            case 4:
            {
                m_controller->releaseButton(Controller::BUTTON_Y);
                break;
            }
            case 6: //0
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 0);
                m_controller->pressButton(Controller::BUTTON_B);
                break;
            }
            case 7: //1
            {
                m_controller->releaseButton(Controller::BUTTON_B);
                break;
            }
            case 9://3
            {
                //reset stick to inactive state
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, .5);
                //jump
                m_controller->pressButton(Controller::BUTTON_Y);
                break;
            }
            case 11:
            {
                m_controller->releaseButton(Controller::BUTTON_Y);
                break;
            }
        }
    } 
    
    if(m_shineType == normalMultishine)
    {
        switch(frame)
        {
            case 0:
            {
                //Down-B
                m_controller->pressButton(Controller::BUTTON_B);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 0);
                break;
            }
            case 3:
            {
                //Let go of Down-B
                m_controller->releaseButton(Controller::BUTTON_B);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, .5);

                //Jump
                m_controller->pressButton(Controller::BUTTON_Y);

                break;
            }
            case 4:
            {
                //Let go of Jump
                m_controller->releaseButton(Controller::BUTTON_Y);
                break;
            }
            case 6:
            {
                //Down-B again
                m_controller->pressButton(Controller::BUTTON_B);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 0);
                break;
            }
            case 7:
            {
                //Let go of Down-B
                m_controller->releaseButton(Controller::BUTTON_B);
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, .5);
                break;
            }
        }
    }  
}
