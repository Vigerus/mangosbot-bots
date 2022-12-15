#pragma once
#include "InventoryAction.h"

namespace ai
{
    class ListSpellsAction : public InventoryAction 
    {
    public:
        ListSpellsAction(PlayerbotAI* ai, string name = "spells") : InventoryAction(ai, name) {}
        virtual bool ExecuteCommand(Event& event) override;
        virtual list<pair<uint32, string> > GetSpellList(string filter = "");

    private:
        static map<uint32, SkillLineAbilityEntry const*> skillSpells;
        static set<uint32> vendorItems;
    };
}
