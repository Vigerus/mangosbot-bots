#pragma once
#include "InventoryAction.h"

namespace ai
{
    class AhAction : public InventoryAction
    {
    public:
        AhAction(PlayerbotAI* ai, string name = "ah") : InventoryAction(ai, name) {}
        virtual bool ExecuteCommand(Event& event) override;

    private:
        virtual bool ExecuteCommand(string text, Unit* auctioneer);
        bool PostItem(Item* item, uint32 price, Unit* auctioneer, uint32 time);
#ifdef GenerateBotHelp
        virtual string GetHelpName() { return "ah"; } //Must equal iternal name
        virtual string GetHelpDescription()
        {
            return "This command will make bots auction items to a nearby auctionhouses.\n"
                "Usage: ah [itemlink] <money>\n"
                "Example: ah vendor (post items based on item use)\n"
                "Example: ah [itemlink] 5g\n";
        }
        virtual vector<string> GetUsedActions() { return {}; }
        virtual vector<string> GetUsedValues() { return { "nearest npcs", "inventory items", "item usage", "free money for" }; }
#endif 
    protected:
        uint32 GetSellPrice(ItemPrototype const* proto);
    };


    class AhBidAction : public AhAction
    {
    public:
        AhBidAction(PlayerbotAI* ai) : AhAction(ai, "ah bid") {}

#ifdef GenerateBotHelp
        virtual string GetHelpName() { return "ah bid"; } //Must equal iternal name
        virtual string GetHelpDescription()
        {
            return "This command will make bots bid on a specific item with a specific budget on a nearby auctionhouse.\n"
                "The higest item/gold aution will be used that falls below the given budget.\n"
                "Usage: ah bid [itemlink] <money>\n"
                "Example: ah bid vendor (bid on items based on item use)\n"
                "Example: ah bid [itemlink] 5g\n";
        }
        virtual vector<string> GetUsedActions() { return {}; }
        virtual vector<string> GetUsedValues() { return { "nearest npcs", "item usage", "free money for" }; }
#endif 
    private:
        virtual bool ExecuteCommand(string text, Unit* auctioneer);
        bool BidItem(AuctionEntry* auction, uint32 price, Unit* auctioneer);
    };
}
