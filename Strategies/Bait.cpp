#include <cmath>
#include <math.h>
#include <iostream>

#include "Bait.h"
#include "../Constants.h"
#include "../Tactics/CloseDistance.h"
#include "../Tactics/CreateDistance.h"
#include "../Tactics/DI.h"
#include "../Tactics/Edgeguard.h"
#include "../Tactics/Laser.h"
#include "../Tactics/Parry.h"
#include "../Tactics/Punish.h"
#include "../Tactics/Recover.h"
#include "../Tactics/ShieldPressure.h"
#include "../Tactics/ShineCombo.h"
#include "../Tactics/Techroll.h"
#include "../Tactics/Wait.h"

Bait::Bait()
{
    m_tactic = NULL;
    m_attackFrame = 0;
    m_lastAction = (ACTION)m_state->m_memory->player_one_action;
    m_shieldedAttack = false;
    m_actionChanged = true;
    m_chargingLastFrame = false;
    m_lastActionCount = 0;
}

Bait::~Bait()
{
    delete m_tactic;
}

void Bait::DetermineTactic()
{
    //std::cout << std::abs(m_state->m_memory->player_one_x - m_state->m_memory->player_two_x) << std::endl;

    //Determine how many frames of lag our opponent has during the LANDING_SPECIAL action
    // Unfortunately, the game reuses LANDING_SPECIAL for both landing from an UP-B and from a wavedash
    // So it's non-trivial to figure out which it is.
    if(m_state->m_memory->player_one_action == LANDING_SPECIAL)
    {
        if(m_lastAction == DEAD_FALL || m_lastAction == UP_B)
        {
            m_state->setLandingState(true);
        }
        if(m_lastAction == AIRDODGE)
        {
            m_state->setLandingState(false);
        }
    }

    //Has opponent just released a sharged smash attack?
    bool m_chargedSmashReleased = false;
    if(!m_state->m_memory->player_one_charging_smash && m_chargingLastFrame)
    {
        m_chargedSmashReleased = true;
    }
    m_chargingLastFrame = m_state->m_memory->player_one_charging_smash;

    //So, turns out that the game changes the player's action state (to 2 or 3) on us when they're charging
    //If this happens, just change it back. Maybe there's a more elegant solution
    if(m_state->m_memory->player_one_action == 0x02 ||
        m_state->m_memory->player_one_action == 0x03)
    {
        m_state->m_memory->player_one_action = m_lastAction;
    }

    //Update the attack frame if the enemy started a new action
    if((m_lastAction != (ACTION)m_state->m_memory->player_one_action) ||
        (m_state->m_memory->player_one_action_counter > m_lastActionCount) ||
        (m_state->m_memory->player_one_action_frame == 0))
    {
        m_lastActionCount = m_state->m_memory->player_one_action_counter;
        m_shieldedAttack = false;
        m_actionChanged = true;
        m_lastAction = (ACTION)m_state->m_memory->player_one_action;
        if(isAttacking((ACTION)m_state->m_memory->player_one_action))
        {
            m_attackFrame = m_state->m_memory->frame;
        }
    }
    //Continuing same previous action
    else
    {
        m_actionChanged = false;
        if(m_state->m_memory->player_two_action == SHIELD_STUN ||
            m_state->m_memory->player_two_action == SPOTDODGE ||
            m_state->m_memory->player_two_action == EDGE_GETUP_QUICK ||
            m_state->m_memory->player_two_action == EDGE_GETUP_SLOW)
        {
            m_shieldedAttack = true;
        }
    }
    if(!isAttacking((ACTION)m_state->m_memory->player_one_action))
    {
        m_attackFrame = 0;
    }

    //If we're not in a state to interupt, just continue with what we've got going
    if((m_tactic != NULL) && (!m_tactic->IsInterruptible()))
    {
        m_tactic->DetermineChain();
        return;
    }

    //If we're still warping in at the start of the match or in shield stun, then just hang out and do nothing
    if(m_state->m_memory->player_two_action == ENTRY ||
        m_state->m_memory->player_two_action == ENTRY_START ||
        m_state->m_memory->player_two_action == ENTRY_END ||
        m_state->m_memory->player_two_action == SHIELD_STUN ||
        m_state->m_memory->player_two_action == LANDING_SPECIAL)
    {
        CreateTactic(Wait);
        m_tactic->DetermineChain();
        return;
    }

    //Calculate distance between players
    double distance = pow(m_state->m_memory->player_one_x - m_state->m_memory->player_two_x, 2);
    distance += pow(m_state->m_memory->player_one_y - m_state->m_memory->player_two_y, 2);
    distance = sqrt(distance);

    //If we're able to upsmash our opponent, let's do that
    bool player_two_is_to_the_left = (m_state->m_memory->player_two_x - m_state->m_memory->player_one_x > 0);
    if((m_state->m_memory->player_one_action == SPOTDODGE ||
        m_state->m_memory->player_one_action == MARTH_COUNTER ||
        m_state->m_memory->player_one_action == MARTH_COUNTER_FALLING ||
        m_state->m_memory->player_one_action == LANDING_SPECIAL) &&
        distance < FOX_UPSMASH_RANGE-2 &&
        m_state->m_memory->player_two_facing != player_two_is_to_the_left)
    {
        CreateTactic(Punish);
        m_tactic->DetermineChain();
        return;
    }

    //If our opponent is stuck in the windup for an attack, let's hit them with something harder than shine
    if(isAttacking((ACTION)m_state->m_memory->player_one_action) &&
        distance < FOX_UPSMASH_RANGE-2 &&
        m_state->m_memory->player_two_facing != player_two_is_to_the_left)
    {
        //How many frames do we have until the attack lands? If it's at least 3, then we can start a Punish
        int frames_left = m_state->firstHitboxFrame((CHARACTER)m_state->m_memory->player_one_character,
            (ACTION)m_state->m_memory->player_one_action) - m_state->m_memory->player_one_action_frame - 1;
        if(frames_left > 3)
        {
            CreateTactic(Punish);
            m_tactic->DetermineChain();
            return;
        }
    }

    //If our opponent is rolling, punish it on the other end
    if(m_state->m_memory->player_one_action == ROLL_FORWARD ||
        m_state->m_memory->player_one_action == ROLL_BACKWARD ||
        m_state->m_memory->player_one_action == EDGE_ROLL_SLOW ||
        m_state->m_memory->player_one_action == EDGE_ROLL_QUICK ||
        m_state->m_memory->player_one_action == EDGE_GETUP_QUICK ||
        m_state->m_memory->player_one_action == EDGE_GETUP_SLOW ||
        m_state->m_memory->player_two_action == LANDING_SPECIAL)
    {
        CreateTactic(Punish);
        m_tactic->DetermineChain();
        return;
    }

    //If we're hanging on the egde, and they are falling above the stage, punish it
    if(m_state->m_memory->player_one_action == DEAD_FALL &&
        m_state->m_memory->player_two_action == EDGE_HANGING &&
        std::abs(m_state->m_memory->player_one_x) < m_state->getStageEdgeGroundPosition() + .001)
    {
        CreateTactic(Punish);
        m_tactic->DetermineChain();
        return;
    }

    //How many frames do we have until the attack is over?
    int frames_left = m_state->totalActionFrames((CHARACTER)m_state->m_memory->player_one_character,
        (ACTION)m_state->m_memory->player_one_action) - m_state->m_memory->player_one_action_frame - 1;

    //If our oponnent is stuck in a laggy ending animation, punish it
    if(isAttacking((ACTION)m_state->m_memory->player_one_action) &&
        m_state->m_memory->player_one_action_frame >
            m_state->lastHitboxFrame((CHARACTER)m_state->m_memory->player_one_character,
            (ACTION)m_state->m_memory->player_one_action))
    {
        if(frames_left > 3)
        {
            //Unless we need to wavedash in, then give us more time
            if(m_state->m_memory->player_two_action != SHIELD_RELEASE ||
                frames_left > 10)
            {
                CreateTactic(Punish);
                m_tactic->DetermineChain();
                return;
            }
        }
    }

    //If we're able to shine p1 right now, let's do that
    if(std::abs(distance) < FOX_SHINE_RADIUS)
    {
        //Are we in a state where we can shine?
        if(ReadyForAction(m_state->m_memory->player_two_action))
        {
            //Is the opponent in a state where they can get hit by shine?
            if(m_state->m_memory->player_one_action != SHIELD &&
                m_state->m_memory->player_one_action != SHIELD_REFLECT &&
                m_state->m_memory->player_one_action != MARTH_COUNTER &&
                m_state->m_memory->player_one_action != MARTH_COUNTER_FALLING &&
                m_state->m_memory->player_one_action != EDGE_CATCHING &&
                m_state->m_memory->player_one_action != SPOTDODGE)
            {
                CreateTactic(ShineCombo);
                m_tactic->DetermineChain();
                return;
            }
        }
    }

    //If we're hanging on the egde, and the oponnent is on the stage area, then recover
    if((m_state->m_memory->player_two_action == EDGE_HANGING ||
        m_state->m_memory->player_two_action == EDGE_CATCHING) &&
        std::abs(m_state->m_memory->player_one_x) < m_state->getStageEdgeGroundPosition() + .001 &&
        m_state->m_memory->player_one_y > -5)
    {
        CreateTactic(Recover);
        m_tactic->DetermineChain();
        return;
    }

    //If we just shielded a downtilt and they're still in the attack, get out of there
    if(m_state->m_memory->player_two_action == SHIELD_RELEASE &&
        m_state->m_memory->player_one_action == DOWNTILT)
    {
        CreateTactic(CreateDistance);
        m_tactic->DetermineChain();
        return;
    }

    //If the enemy is in a looping attack outside our range, back off
    if(distance > 35 &&
        distance < 60 &&
        (m_state->m_memory->player_one_action == DOWNTILT ||
        m_state->m_memory->player_one_action == NEUTRAL_ATTACK_1 ||
        m_state->m_memory->player_one_action == NEUTRAL_ATTACK_2))
    {
        CreateTactic(CreateDistance);
        m_tactic->DetermineChain();
        return;
    }

    //If we need to defend against an attack, that's next priority. Unless we've already shielded this attack
    if(!m_shieldedAttack && distance < MARTH_FSMASH_RANGE)
    {
        //Don't bother parrying if the attack is over
        if(m_state->lastHitboxFrame((CHARACTER)m_state->m_memory->player_one_character, (ACTION)m_state->m_memory->player_one_action) >=
            m_state->m_memory->player_one_action_frame)
        {
            //Don't bother parrying if the attack is in the wrong direction
            bool player_one_is_to_the_left = (m_state->m_memory->player_one_x - m_state->m_memory->player_two_x > 0);
            if((m_state->m_memory->player_one_facing != player_one_is_to_the_left || (isReverseHit((ACTION)m_state->m_memory->player_one_action))) &&
                (m_state->m_memory->player_two_on_ground ||
                m_state->m_memory->player_two_action == EDGE_HANGING ||
                m_state->m_memory->player_two_action == EDGE_CATCHING))
            {
                if(isAttacking((ACTION)m_state->m_memory->player_one_action))
                {
                    //If the p1 action changed, scrap the old Parry and make a new one.
                    if(m_actionChanged || m_chargedSmashReleased)
                    {
                        delete m_tactic;
                        m_tactic = NULL;
                    }

                    CreateTactic(Parry);
                    m_tactic->DetermineChain();
                    return;
                }
            }
        }
    }

    //If the opponent is off the stage, let's edgeguard them
    //NOTE: Sometimes players can get a little below 0 in Y coordinates without being off the stage
    if(std::abs(m_state->m_memory->player_one_x) > m_state->getStageEdgeGroundPosition() + .001 ||
        m_state->m_memory->player_one_y < -5.5 ||
        m_state->m_memory->player_one_action == EDGE_CATCHING ||
        m_state->m_memory->player_one_action == EDGE_HANGING)
    {
        CreateTactic(Edgeguard);
        m_tactic->DetermineChain();
        return;
    }

    //If we're off the stage and don't need to edgeguard, get back on
    if(std::abs(m_state->m_memory->player_two_x) > m_state->getStageEdgeGroundPosition() + .001)
    {
        CreateTactic(Recover);
        m_tactic->DetermineChain();
        return;
    }

    //If we're far away, just laser
    if(std::abs(m_state->m_memory->player_one_x - m_state->m_memory->player_two_x) > 90 &&
        std::abs(m_state->m_memory->player_one_x) < 130)
    {
        CreateTactic(Laser);
        m_tactic->DetermineChain();
        return;
    }

    //If we're not in shine range, get in close
    if(std::abs(m_state->m_memory->player_one_x - m_state->m_memory->player_two_x) > FOX_SHINE_RADIUS)
    {
        CreateTactic(CloseDistance);
        m_tactic->DetermineChain();
        return;
    }
    //If we're in close and p2 is shielding, apply shield pressure
    if(m_state->m_memory->player_one_action == ACTION::SHIELD)
    {
        CreateTactic(ShieldPressure);
        m_tactic->DetermineChain();
        return;
    }
    //"I'm shot!" - John Lennon
    //Implement Smash DI (Beta)
    if(m_state->m_memory->player_two_hitlag_frames_left > 0 &&
        (m_state->m_memory->player_two_action != ACTION::SHIELD ||
        m_state->m_memory->player_two_action != ACTION::DOWN_B_STUN))
    {
        CreateTactic(DI);
        m_tactic->DetermineChain();
        return;
    }
    //Implement Tech Rolling
    if(m_state->m_memory->player_two_action == ACTION::DAMAGE_FLY_HIGH || 
        m_state->m_memory->player_two_action == ACTION::DAMAGE_FLY_NEUTRAL ||
        m_state->m_memory->player_two_action == ACTION::DAMAGE_FLY_LOW ||
        m_state->m_memory->player_two_action == ACTION::DAMAGE_FLY_TOP ||
        m_state->m_memory->player_two_action == ACTION::DAMAGE_FLY_ROLL && 
        !(m_state->m_memory->player_two_y < m_state->getStageHeight()))
    {
        CreateTactic(Techroll);
        m_tactic->DetermineChain();
        return;
    }
    //TODO: For now, just default to waiting if nothing else fits
    CreateTactic(Wait);
    m_tactic->DetermineChain();
    return;
}

bool Bait::isAttacking(ACTION action)
{
    switch(action)
    {
        case FSMASH_MID:
        case DOWNSMASH:
        case UPSMASH:
        case DASH_ATTACK:
        case GRAB:
        case GRAB_RUNNING:
        case FTILT_HIGH:
        case FTILT_HIGH_MID:
        case FTILT_MID:
        case FTILT_LOW_MID:
        case FTILT_LOW:
        case UPTILT:
        case DOWNTILT:
        case SWORD_DANCE_1:
        case SWORD_DANCE_2_HIGH:
        case SWORD_DANCE_2_MID:
        case SWORD_DANCE_3_HIGH:
        case SWORD_DANCE_3_MID:
        case SWORD_DANCE_3_LOW:
        case SWORD_DANCE_4_HIGH:
        case SWORD_DANCE_4_MID:
        case SWORD_DANCE_4_LOW:
        case SWORD_DANCE_1_AIR:
        case SWORD_DANCE_2_HIGH_AIR:
        case SWORD_DANCE_2_MID_AIR:
        case SWORD_DANCE_3_HIGH_AIR:
        case SWORD_DANCE_3_MID_AIR:
        case SWORD_DANCE_3_LOW_AIR:
        case SWORD_DANCE_4_HIGH_AIR:
        case SWORD_DANCE_4_MID_AIR:
        case SWORD_DANCE_4_LOW_AIR:
        case UP_B:
        case UP_B_GROUND:
        case NAIR:
        case UAIR:
        case DAIR:
        case BAIR:
        case FAIR:
        case NEUTRAL_ATTACK_1:
        case NEUTRAL_ATTACK_2:
        case NEUTRAL_ATTACK_3:
        case NEUTRAL_B_ATTACKING:
        case NEUTRAL_B_ATTACKING_AIR:
        case EDGE_ATTACK_QUICK:
        case EDGE_ATTACK_SLOW:
        {
            return true;
        }
        default:
        {
            return false;
        }
    }
}

bool Bait::isReverseHit(ACTION action)
{
    switch(action)
    {
        case DOWNSMASH:
        case UPSMASH:
        case GRAB_RUNNING:
        case UPTILT:
        case NAIR:
        case UAIR:
        case DAIR:
        case BAIR:
        {
            return true;
        }
        default:
        {
            return false;
        }
    }
}
