#include "ShieldPressure.h"
#include "../Chains/Multishine.h"
#include "../Chains/Nothing.h"

ShieldPressure::ShieldPressure()
{
    m_chain = NULL;
    m_startingFrame = m_state->m_memory->frame;
}

ShieldPressure::~ShieldPressure()
{
    delete m_chain;
}

void ShieldPressure::DetermineChain()
{
    uint frame = m_state->m_memory->frame - m_startingFrame;
    //TODO: Implement a "bored" function
    if(frame <= 19)
    {
        CreateChain(Nothing);
        m_chain->PressButtons();
        return;
    }
    if(frame >= 20)
    { //dis gun b gud
        if(m_state->m_memory->player_one_action == ACTION::SHIELD)
        {
            CreateChain2(Multishine, true);
            m_chain->PressButtons();
            return;
        }
    }
}
