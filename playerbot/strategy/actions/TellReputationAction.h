#pragma once
#include "GenericActions.h"

namespace ai
{
    class TellReputationAction : public ChatCommandAction
    {
    public:
        TellReputationAction(PlayerbotAI* ai) : ChatCommandAction(ai, "reputation") {}

    private:
        bool ExecuteCommand(Event& event) override;
    };
}