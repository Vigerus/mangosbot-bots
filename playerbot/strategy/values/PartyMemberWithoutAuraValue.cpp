#include "botpch.h"
#include "../../playerbot.h"
#include "PartyMemberWithoutAuraValue.h"

#include "../../ServerFacade.h"
using namespace ai;

extern vector<string> split(const string &s, char delim);

class PlayerWithoutAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutAuraPredicate(PlayerbotAI* ai, string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), auras(split(aura, ',')) {}

public:
    virtual bool Check(Unit* unit)
    {
        Pet* pet = dynamic_cast<Pet*>(unit);
        if (pet && (pet->getPetType() == MINI_PET || pet->getPetType() == SUMMON_PET))
            return false;

        if (!sServerFacade.IsAlive(unit)) return false;

        for (vector<string>::iterator i = auras.begin(); i != auras.end(); ++i)
        {
            if (ai->HasAura(*i, unit))
                return false;
        }

        return true;
    }

private:
    vector<string> auras;
};

Unit* FriendlyUnitWithoutAuraValue::Calculate()
{
    PlayerWithoutAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate);
}

Unit* PartyMemberWithoutAuraValue::Calculate()
{
	PlayerWithoutAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate, true);
}

class PlayerWithoutMyAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutMyAuraPredicate(PlayerbotAI* ai, string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), auras(split(aura, ',')) {}

public:
    virtual bool Check(Unit* unit)
    {
        Pet* pet = dynamic_cast<Pet*>(unit);
        if (pet && (pet->getPetType() == MINI_PET || pet->getPetType() == SUMMON_PET))
            return false;

        if (!sServerFacade.IsAlive(unit)) return false;
        if (sServerFacade.GetDistance2d(unit, ai->GetBot()) > 30.0f) return false;

        for (vector<string>::iterator i = auras.begin(); i != auras.end(); ++i)
        {
            if (ai->HasMyAura(*i, unit))
                return false;
        }

        return true;
    }

private:
    vector<string> auras;
};

Unit* PartyMemberWithoutMyAuraValue::Calculate()
{
    PlayerWithoutMyAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate);
}

class TankWithoutAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    TankWithoutAuraPredicate(PlayerbotAI* ai, string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), auras(split(aura, ',')) {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit && unit->IsPlayer() && sServerFacade.IsAlive(unit))
        {
            if (ai->IsTank((Player*)unit))
            {
                bool missingAura = false;
                for (vector<string>::iterator i = auras.begin(); i != auras.end(); ++i)
                {
                    if (!ai->HasAura(*i, unit))
                    {
                        missingAura = true;
                        break;
                    }
                }

                return missingAura;
            }
        }

        return false;
    }

private:
    vector<string> auras;
};

Unit* PartyTankWithoutAuraValue::Calculate()
{
    TankWithoutAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate);
}
