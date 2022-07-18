#include "qdnodeeditgroup.hpp"

QD_NodeEditGroup::QD_NodeEditGroup(int argX, int argY, int argW, int argH, const char *argLabel)
    : Fl_Group(argX, argY, argW, argH, argLabel)
{
    {   m_title = new QD_InputLineButton(50, 50, 665, 20, "设置节点名称");
        m_title->input_align(FL_ALIGN_CENTER);
        m_title->wrap(false);
    }

    {   m_questLog = new QD_InputMultilineButton(50, 80, 665, 200, "设置节点日志");
        m_questLog->input_align(FL_ALIGN_LEFT);
        m_questLog->wrap(true);
    }

    {   m_enterTrigger = new QD_InputMultilineButton(50, 300, 665, 200, "设置节点进入逻辑");
        m_enterTrigger->input_align(FL_ALIGN_LEFT);
        m_enterTrigger->wrap(true);
    }

    this->end();
}

int QD_NodeEditGroup::handle(int event)
{
    const auto result = Fl_Group::handle(event);
    if(event == FL_PUSH && !result){
        m_title->edit(false);
        m_questLog->edit(false);
        m_enterTrigger->edit(false);
        return 1;
    }
    return result;
}