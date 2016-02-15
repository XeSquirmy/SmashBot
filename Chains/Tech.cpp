#include <iostream>
#include <cmath>

#include "Tech.h"

void Tech::PressButtons()
{
    if(m_option == IN_PLACE)
    {
        uint frame = m_state->m_memory->frame - m_startingFrame;
        std::cout << "Stuck in Tech chain" << std::endl;
        switch(frame)
        {
            case 0:
            {
                m_controller->emptyInput();
                break;
            }
            case 1:
            {
                m_controller->pressButton(Controller::BUTTON_L);
                break;
            }
            case 2:
            {
                m_controller->releaseButton(Controller::BUTTON_L);
                m_controller->emptyInput();
                break;
            }
        }
        return;
    }
}

bool Tech::IsInterruptible()
{
    if(m_state->m_memory->player_two_action != DAMAGE_FLY_HIGH || 
        m_state->m_memory->player_two_action != DAMAGE_FLY_NEUTRAL ||
        m_state->m_memory->player_two_action != DAMAGE_FLY_LOW ||
        m_state->m_memory->player_two_action != DAMAGE_FLY_TOP ||
        m_state->m_memory->player_two_action != DAMAGE_FLY_ROLL ||
        m_state->m_memory->player_two_action == DOWNBOUND_UP ||
        m_state->m_memory->player_two_action == DOWNBOUND_DOWN ||
        (std::abs(m_state->m_memory->player_two_x) > (m_state->getStageEdgeGroundPosition() + 0.001)))
    {
        return true;
    }
    return false;
}

Tech::Tech(uint option)
{
    m_height = m_state->getStageHeight();
    m_option = option;
    m_startingFrame = m_state->m_memory->frame;
    IN_PLACE = 0;
    LEFT = 1;
    RIGHT = 2;
    MISSED_UP = 3;
    MISSED_ATTACK = 4;
    MISSED_LEFT = 5;
    MISSED_RIGHT = 6;
}

Tech::~Tech()
{
}
