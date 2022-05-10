#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace ai
{
   
    class CurrentCcTargetValue : public TargetValue, public Qualified
	{
	public:
        CurrentCcTargetValue(PlayerbotAI* ai, string name = "current cc target") : TargetValue(ai, name, 2) {}

    public:
        Unit* Calculate();
    };
}
