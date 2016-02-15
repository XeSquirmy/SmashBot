#include <typeinfo>
#include <iostream>
#include <math.h>
#include <cmath>

#include "Recover.h"
#include "../Constants.h"
#include "../Chains/Nothing.h"
#include "../Chains/EdgeAction.h"
#include "../Chains/EdgeStall.h"
#include "../Chains/FireFox.h"
#include "../Chains/Illusion.h"

Recover::Recover()
{
    m_chain = NULL;
    m_startingFrame = 0;
    FULL = 0;
    FULLSHORT = 1;
    HALF = 2;
    SHORT = 3;
}

Recover::~Recover()
{
    delete m_chain;
}

void Recover::DetermineChain()
{
    //If we're not in a state to interupt, just continue with what we've got going
    if((m_chain != NULL) && (!m_chain->IsInterruptible()))
    {
        m_chain->PressButtons();
        return;
    }

    //If we're hanging on the egde, do an edge stall
    if(m_state->m_memory->player_two_action == EDGE_HANGING ||
      m_state->m_memory->player_two_action == EDGE_CATCHING)
    {

        bool p1IsOnRight = m_state->m_memory->player_one_x > 0;
        bool movingRight = m_state->m_memory->player_one_speed_ground_x_self > 0;
        //uint frame = m_startingFrame - m_state->m_memory->frame;
        //TODO: made up number 60. Revsit this.
        //Stand up if the enemy is far away, or if they're trying to steal the edge
        //Stand up if the enemy is a lame ass player (10 seconds waiting doing nothing while edgestalling
        if(std::abs(m_state->m_memory->player_one_x - m_state->m_memory->player_two_x) > 60 ||
          (m_state->m_memory->player_one_action == LANDING_SPECIAL &&
          p1IsOnRight != m_state->m_memory->player_one_facing &&
          movingRight == p1IsOnRight &&
          m_state->getStageEdgeGroundPosition() - std::abs(m_state->m_memory->player_one_x) < 10))
        {
            CreateChain2(EdgeAction, Controller::BUTTON_MAIN);
            m_chain->PressButtons();
            return;
        }
        
        CreateChain(EdgeStall);
        m_chain->PressButtons();
        //frame = 0;
        return;
    }

    //TODO: This is only rudimentary recovery. Needs to be expanded
    //If we're off the stage...
    if(std::abs(m_state->m_memory->player_two_x) > m_state->getStageEdgeGroundPosition() + .001 ||
        m_state->m_memory->player_two_y < m_state->getStageHeight())
    {
        bool p2IsOnRight = m_state->m_memory->player_two_x > 0;
        if(m_state->m_memory->player_two_y >= m_state->getStageHeight() && 
            m_state->m_memory->player_two_y <= (m_state->getStageHeight() + 10) &&
            (m_state->m_memory->player_one_action != EDGE_HANGING || 
            m_state->m_memory->player_one_action != EDGE_ROLL_SLOW ||
            m_state->m_memory->player_one_action != EDGE_ATTACK_SLOW ||
            m_state->m_memory->player_one_action != EDGE_GETUP_SLOW))
        {
            if((std::abs(m_state->m_memory->player_two_x) + 
                std::abs(m_state->getStageEdgeGroundPosition())) <= 
                (std::abs(m_state->getStageEdgeGroundPosition())+30))
            {
                CreateChain3(Illusion, p2IsOnRight, SHORT);
                m_chain->PressButtons();
                return;
            }
            if((std::abs(m_state->m_memory->player_two_x) + 
                std::abs(m_state->getStageEdgeGroundPosition())) > 100)
            {
                CreateChain3(Illusion, p2IsOnRight, FULL);
                m_chain->PressButtons();
                return;
            }
        }
        else
        {
            //Firefox back
            CreateChain(FireFox);
            m_chain->PressButtons();
            return;
        }

    }

    //Default to nothing in towards the player
    CreateChain(Nothing);
    m_chain->PressButtons();
    return;
}
