#include <algorithm>
#include <tinyxml2.h>
#include <SDL2/SDL.h>

#include "log.hpp"
#include "mathf.hpp"
#include "motion.hpp"
#include "fflerror.hpp"
#include "sysconst.hpp"
#include "ascendstr.hpp"
#include "processrun.hpp"
#include "magicrecord.hpp"
#include "protocoldef.hpp"
#include "dbcomrecord.hpp"
#include "attachmagic.hpp"
#include "clientcreature.hpp"
#include "clientmonster.hpp"

extern Log *g_log;
bool ClientCreature::advanceMotionFrame()
{
    m_currMotion->frame = (m_currMotion->frame + 1) % getFrameCountEx(m_currMotion->type, m_currMotion->direction);
    return true;
}

void ClientCreature::updateAttachMagic(double fUpdateTime)
{
    for(auto p = m_attachMagicList.begin(); p != m_attachMagicList.end();){
        if((*p)->update(fUpdateTime)){
            p = m_attachMagicList.erase(p);
        }
        else{
            ++p;
        }
    }
}

void ClientCreature::updateHealth(SDHealth health)
{
    const int pixelX = x() * SYS_MAPGRIDXP + SYS_MAPGRIDXP / 2;
    const int pixelY = y() * SYS_MAPGRIDYP - SYS_MAPGRIDYP * 1;

    if(!m_sdHealth.has_value()){
        m_sdHealth = std::move(health);
        return;
    }

    const int diffHP = health.HP - m_sdHealth.value().HP;
    const int diffMP = health.MP - m_sdHealth.value().MP;

    m_sdHealth = health;

    if(diffHP){
        m_processRun->addAscendStr(ASCENDSTR_NUM0, diffHP, pixelX, pixelY);
    }

    if(diffMP){
        m_processRun->addAscendStr(ASCENDSTR_NUM1, diffMP, pixelX, pixelY - (diffHP ? SYS_MAPGRIDYP : 0));
    }
}

bool ClientCreature::alive() const
{
    if(!motionValid(m_currMotion)){
        throw fflerror("invalid motion detected");
    }

    switch(m_currMotion->type){
        case MOTION_DIE:
        case MOTION_MON_DIE:
            {
                return false;
            }
        default:
            {
                return true;
            }
    }
}

bool ClientCreature::active() const
{
    if(!motionValid(m_currMotion)){
        throw fflerror("invalid motion detected");
    }

    switch(m_currMotion->type){
        case MOTION_DIE:
        case MOTION_MON_DIE:
            {
                return (m_currMotion->frame + 1) < getFrameCountEx(m_currMotion->type, m_currMotion->direction);
            }
        default:
            {
                return true;
            }
    }
}

bool ClientCreature::visible() const
{
    fflassert(motionValid(m_currMotion));
    switch(m_currMotion->type){
        case MOTION_DIE:
            {
                fflassert(type() == UID_PLY);
                return ((m_currMotion->frame + 1) < getFrameCountEx(m_currMotion->type, m_currMotion->direction)) || (m_currMotion->extParam.die.fadeOut < 255);
            }
        case MOTION_MON_DIE:
            {
                // NOTE check (frame + 1) < frameCount
                // because ClientCreature::update() guarantees frame < frmeCount always true

                fflassert(type() == UID_MON);
                if((m_currMotion->frame + 1) < getFrameCountEx(m_currMotion->type, m_currMotion->direction)){
                    return true;
                }

                const auto monCPtr = dynamic_cast<const ClientMonster *>(this);
                if(monCPtr->getMR().deadFadeOut){
                    return m_currMotion->extParam.die.fadeOut < 255;
                }

                fflassert(m_currMotion->extParam.die.fadeOut == 0);
                return false;
            }
        default:
            {
                return true;
            }
    }
}

bool ClientCreature::checkUpdate(double ms)
{
    fflassert(ms >= 0.0);
    m_accuUpdateTime += ms;

    if(m_accuUpdateTime >= m_lastUpdateTime + m_currMotion->frameDelay()){
        m_lastUpdateTime = m_accuUpdateTime;
        return true;
    }
    return false;
}

void ClientCreature::querySelf()
{
    m_lastQuerySelf = SDL_GetTicks();
    m_processRun->queryCORecord(UID());
}

bool ClientCreature::isMonster(const char8_t *name) const
{
    return (type() == UID_MON) && (dynamic_cast<const ClientMonster *>(this)->monsterID() == DBCOM_MONSTERID(name));
}

void ClientCreature::setBuff(int, int)
{
    // do nothing by default
}
