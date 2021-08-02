#include "dbcomid.hpp"
#include "processrun.hpp"
#include "dbcomrecord.hpp"
#include "clientshipwrecklord.hpp"

bool ClientShipwreckLord::onActionAttack(const ActionNode &action)
{
    const auto [endX, endY, endDir] = motionEndGLoc().at(1);
    m_motionQueue = makeWalkMotionQueue(endX, endY, action.x, action.y, SYS_MAXSPEED);

    switch(const auto magicID = action.extParam.attack.damageID){
        case DBCOM_MAGICID(u8"物理攻击"):
            {
                m_motionQueue.push_back(std::unique_ptr<MotionNode>(new MotionNode
                {
                    .type = MOTION_MON_ATTACK0,
                    .direction = m_processRun->getAimDirection(action, currMotion()->direction),
                    .x = action.x,
                    .y = action.y,
                }));

                m_motionQueue.back()->addUpdate(false, [this](MotionNode *motionPtr) -> bool
                {
                    addAttachMagic(std::unique_ptr<AttachMagic>(new AttachMagic(u8"霸王教主_火刃", u8"运行", motionPtr->direction - DIR_BEGIN)));
                    return true;
                });
                return true;
            }
        case DBCOM_MAGICID(u8"霸王教主_野蛮冲撞"):
            {
                m_motionQueue.push_back(std::unique_ptr<MotionNode>(new MotionNode
                {
                    .type = MOTION_MON_SPELL0,
                    .direction = m_processRun->getAimDirection(action, currMotion()->direction),
                    .x = action.x,
                    .y = action.y,
                }));
                return true;
            }
        default:
            {
                throw fflerror("invalid DC: id = %d, name = %s", to_d(magicID), to_cstr(DBCOM_MAGICRECORD(magicID).name));
            }
    }
}

bool ClientShipwreckLord::onActionDie(const ActionNode &action)
{
    const auto result = ClientMonster::onActionDie(action);

    fflassert(result);
    fflassert(m_forcedMotionQueue.back()->type == MOTION_MON_DIE);

    m_forcedMotionQueue.back()->addUpdate(true, [this](MotionNode *) -> bool
    {
        addAttachMagic(std::unique_ptr<AttachMagic>(new AttachMagic(u8"霸王教主_死亡特效", u8"运行")));
        return true;
    });
    return result;
}