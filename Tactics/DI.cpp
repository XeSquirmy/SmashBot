#include "DI.h"
#include "../Chains/SmashDI.h"

DI::DI()
{
    m_chain = NULL;
    m_isFacingRightP1 = m_state->m_memory->player_one_facing;
    m_isFacingRightP2 = m_state->m_memory->player_two_facing;
    m_hitlagFramesLeftP1 = m_state->m_memory->player_one_hitlag_frames_left;
    m_hitlagFramesLeftP2 = m_state->m_memory->player_two_hitlag_frames_left;
}

DI::~DI()
{
    delete m_chain;
}

void DI::DetermineChain()
{
    if(m_hitlagFramesLeftP2 > 0)
    {
        if(m_isFacingRightP1 == true)
        {
            CreateChain2(SmashDI, true);
            m_chain->PressButtons();
        }
        if(m_isFacingRightP1 == false)
        {
            CreateChain2(SmashDI, false);
            m_chain->PressButtons();
        }
    }
}
