#include <iostream>

#include "SmashDI.h"

SmashDI::SmashDI(bool facingRight)
{
    m_startingFrame = m_state->m_memory->frame;
    m_facingRight = facingRight;
}

SmashDI::~SmashDI()
{
}

bool SmashDI::IsInterruptible()
{
    if(m_state->m_memory->player_two_hitlag_frames_left == 0) 
    {
        return true;
    }
    return false;
}

void SmashDI::PressButtons()
{
    uint frame = m_state->m_memory->frame - m_startingFrame;
    if(m_facingRight == true)
    {
        for(uint i = 0; i <= m_state->m_memory->player_two_hitlag_frames_left; i++)
        {
            if(i % 2 == 0)
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            else
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
        }
        //we can only have a maximum of a 19 frame window to input SDI directions
        /*switch(frame)
        {
            case 0:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 1:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 2:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 3:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 4:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 5:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 6:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 7:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 8:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 9:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 10:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 11:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 12:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 13:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 14:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 15:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 16:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 17:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 18:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 0.5);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            case 19:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, 1);
                std::cout << "Debug: SDI'd to the RIGHT on frame " << frame+1 << std::endl;
                break;
            }
            
        }*/
    }
    if(m_facingRight == false)
    {
        switch(frame)
        {
            case 0:
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, 0, 0.5);
                std::cout << "Debug: SDI'd to the LEFT on frame " << frame+1 << std::endl;
                break;
            }
        }
    }
}
