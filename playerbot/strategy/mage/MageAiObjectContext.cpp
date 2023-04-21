#include "botpch.h"
#include "../../playerbot.h"
#include "../Strategy.h"
#include "MageActions.h"
#include "MageAiObjectContext.h"
#include "FrostMageStrategy.h"
#include "ArcaneMageStrategy.h"
#include "GenericMageNonCombatStrategy.h"
#include "MageReactionStrategy.h"
#include "FireMageStrategy.h"
#include "../generic/PullStrategy.h"
#include "MageTriggers.h"
#include "../NamedObjectContext.h"

using namespace ai;


namespace ai
{
    namespace mage
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &mage::StrategyFactoryInternal::nc;
                creators["react"] = &mage::StrategyFactoryInternal::react;
                creators["pull"] = &mage::StrategyFactoryInternal::pull;
                creators["fire aoe"] = &mage::StrategyFactoryInternal::fire_aoe;
                creators["frost aoe"] = &mage::StrategyFactoryInternal::frost_aoe;
                creators["arcane aoe"] = &mage::StrategyFactoryInternal::arcane_aoe;
                creators["cure"] = &mage::StrategyFactoryInternal::cure;
                creators["buff"] = &mage::StrategyFactoryInternal::buff;
                creators["boost"] = &mage::StrategyFactoryInternal::boost;
                creators["cc"] = &mage::StrategyFactoryInternal::cc;
            }

        private:
            static Strategy* nc(PlayerbotAI* ai) { return new GenericMageNonCombatStrategy(ai); }
            static Strategy* react(PlayerbotAI* ai) { return new MageReactionStrategy(ai); }
            static Strategy* pull(PlayerbotAI* ai) { return new PullStrategy(ai, "shoot"); }
            static Strategy* fire_aoe(PlayerbotAI* ai) { return new FireMageAoeStrategy(ai); }
            static Strategy* frost_aoe(PlayerbotAI* ai) { return new FrostMageAoeStrategy(ai); }
            static Strategy* arcane_aoe(PlayerbotAI* ai) { return new ArcaneMageAoeStrategy(ai); }
            static Strategy* cure(PlayerbotAI* ai) { return new MageCureStrategy(ai); }
            static Strategy* buff(PlayerbotAI* ai) { return new MageBuffStrategy(ai); }
            static Strategy* boost(PlayerbotAI* ai) { return new MageBoostStrategy(ai); }
            static Strategy* cc(PlayerbotAI* ai) { return new MageCcStrategy(ai); }
        };

        class MageStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            MageStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["frost"] = &mage::MageStrategyFactoryInternal::frost;
                creators["fire"] = &mage::MageStrategyFactoryInternal::fire;
                creators["arcane"] = &mage::MageStrategyFactoryInternal::arcane;
            }

        private:
            static Strategy* frost(PlayerbotAI* ai) { return new FrostMageStrategy(ai); }
            static Strategy* fire(PlayerbotAI* ai) { return new FireMageStrategy(ai); }
            static Strategy* arcane(PlayerbotAI* ai) { return new ArcaneMageStrategy(ai); }
        };

        class MageBuffStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            MageBuffStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["bmana"] = &mage::MageBuffStrategyFactoryInternal::bmana;
                creators["bdps"] = &mage::MageBuffStrategyFactoryInternal::bdps;
            }

        private:
            static Strategy* bmana(PlayerbotAI* ai) { return new MageBuffManaStrategy(ai); }
            static Strategy* bdps(PlayerbotAI* ai) { return new MageBuffDpsStrategy(ai); }
        };
    };
};


namespace ai
{
    namespace mage
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["fireball"] = &TriggerFactoryInternal::fireball;
                creators["pyroblast"] = &TriggerFactoryInternal::pyroblast;
                creators["combustion"] = &TriggerFactoryInternal::combustion;
                creators["icy veins"] = &TriggerFactoryInternal::icy_veins;
                creators["arcane intellect"] = &TriggerFactoryInternal::arcane_intellect;
                creators["arcane intellect on party"] = &TriggerFactoryInternal::arcane_intellect_on_party;
                creators["arcane brilliance on party"] = &TriggerFactoryInternal::arcane_brilliance_on_party;
                creators["mage armor"] = &TriggerFactoryInternal::mage_armor;
                creators["remove curse"] = &TriggerFactoryInternal::remove_curse;
                creators["remove curse on party"] = &TriggerFactoryInternal::remove_curse_on_party;
                creators["counterspell"] = &TriggerFactoryInternal::counterspell;
                creators["polymorph"] = &TriggerFactoryInternal::polymorph;
                creators["spellsteal"] = &TriggerFactoryInternal::spellsteal;
                creators["missile barrage"] = &TriggerFactoryInternal::missile_barrage;
                creators["arcane blast"] = &TriggerFactoryInternal::arcane_blast;
                creators["counterspell on enemy healer"] = &TriggerFactoryInternal::counterspell_enemy_healer;
                creators["arcane power"] = &TriggerFactoryInternal::arcane_power;
                creators["presence of mind"] = &TriggerFactoryInternal::presence_of_mind;
                creators["fire ward"] = &TriggerFactoryInternal::fire_ward;
                creators["frost ward"] = &TriggerFactoryInternal::frost_ward;
                creators["blink"] = &TriggerFactoryInternal::blink;
                creators["mana shield"] = &TriggerFactoryInternal::mana_shield;
                creators["summon water elemental"] = &TriggerFactoryInternal::summon_water_elemental;
                creators["ice lance"] = &TriggerFactoryInternal::ice_lance;
                creators["fire spells locked"] = &TriggerFactoryInternal::fire_spells_locked;
                creators["cold snap"] = &TriggerFactoryInternal::cold_snap;
                creators["ice barrier"] = &TriggerFactoryInternal::ice_barrier;
#ifdef MANGOSBOT_TWO
                creators["hot streak"] = &TriggerFactoryInternal::hot_streak;
                creators["fireball!"] = &TriggerFactoryInternal::fireball_or_frostfire_bolt_free;
                creators["finger of frost"] = &TriggerFactoryInternal::finger_of_frost;
                creators["mirror image"] = &TriggerFactoryInternal::mirror_image;
                creators["learn glyph of fireball"] = &TriggerFactoryInternal::learn_glyph_of_fireball;
                creators["remove glyph of fireball"] = &TriggerFactoryInternal::remove_glyph_of_fireball;
                creators["learn glyph of frostbolt"] = &TriggerFactoryInternal::learn_glyph_of_frostbolt;
                creators["remove glyph of frostbolt"] = &TriggerFactoryInternal::remove_glyph_of_frostbolt;
                creators["learn glyph of living bomb"] = &TriggerFactoryInternal::learn_glyph_of_living_bomb;
                creators["remove glyph of living bomb"] = &TriggerFactoryInternal::remove_glyph_of_living_bomb;
                creators["learn glyph of mirror image"] = &TriggerFactoryInternal::learn_glyph_of_mirror_image;
                creators["remove glyph of mirror image"] = &TriggerFactoryInternal::remove_glyph_of_mirror_image;
                creators["learn glyph of molten armor"] = &TriggerFactoryInternal::learn_glyph_of_molten_armor;
                creators["remove glyph of molten armor"] = &TriggerFactoryInternal::remove_glyph_of_molten_armor;
                creators["no improved scorch"] = &TriggerFactoryInternal::no_improved_scorch;
#else
                creators["no fire vulnerability"] = &TriggerFactoryInternal::no_fire_vulnerability;
#endif
#ifndef MANGOSBOT_ZERO
                creators["living bomb"] = &TriggerFactoryInternal::living_bomb;
#endif
            }

        private:
            static Trigger* ice_lance(PlayerbotAI* ai) { return new IceLanceTrigger(ai); }
            static Trigger* summon_water_elemental(PlayerbotAI* ai) { return new WaterElementalBoostTrigger(ai); }
            static Trigger* mana_shield(PlayerbotAI* ai) { return new ManaShieldTrigger(ai); }
            static Trigger* blink(PlayerbotAI* ai) { return new BlinkTrigger(ai); }
            static Trigger* frost_ward(PlayerbotAI* ai) { return new FrostWardTrigger(ai); }
            static Trigger* fire_ward(PlayerbotAI* ai) { return new FireWardTrigger(ai); }
            static Trigger* presence_of_mind(PlayerbotAI* ai) { return new PresenceOfMindTrigger(ai); }
            static Trigger* arcane_power(PlayerbotAI* ai) { return new ArcanePowerTrigger(ai); }
            static Trigger* fireball(PlayerbotAI* ai) { return new FireballTrigger(ai); }
            static Trigger* pyroblast(PlayerbotAI* ai) { return new PyroblastTrigger(ai); }
            static Trigger* combustion(PlayerbotAI* ai) { return new CombustionTrigger(ai); }
            static Trigger* icy_veins(PlayerbotAI* ai) { return new IcyVeinsTrigger(ai); }
            static Trigger* arcane_intellect(PlayerbotAI* ai) { return new ArcaneIntellectTrigger(ai); }
            static Trigger* arcane_intellect_on_party(PlayerbotAI* ai) { return new ArcaneIntellectOnPartyTrigger(ai); }
            static Trigger* arcane_brilliance_on_party(PlayerbotAI* ai) { return new ArcaneBrillianceOnPartyTrigger(ai); }
            static Trigger* mage_armor(PlayerbotAI* ai) { return new MageArmorTrigger(ai); }
            static Trigger* remove_curse(PlayerbotAI* ai) { return new RemoveCurseTrigger(ai); }
            static Trigger* remove_curse_on_party(PlayerbotAI* ai) { return new PartyMemberRemoveCurseTrigger(ai); }
            static Trigger* counterspell(PlayerbotAI* ai) { return new CounterspellInterruptSpellTrigger(ai); }
            static Trigger* polymorph(PlayerbotAI* ai) { return new PolymorphTrigger(ai); }
            static Trigger* spellsteal(PlayerbotAI* ai) { return new SpellstealTrigger(ai); }
            static Trigger* missile_barrage(PlayerbotAI* ai) { return new MissileBarrageTrigger(ai); }
            static Trigger* arcane_blast(PlayerbotAI* ai) { return new ArcaneBlastTrigger(ai); }
            static Trigger* counterspell_enemy_healer(PlayerbotAI* ai) { return new CounterspellEnemyHealerTrigger(ai); }
            static Trigger* fire_spells_locked(PlayerbotAI* ai) { return new FireSpellsLocked(ai); }
            static Trigger* cold_snap(PlayerbotAI* ai) { return new ColdSnapTrigger(ai); }
            static Trigger* ice_barrier(PlayerbotAI* ai) { return new IceBarrierTrigger(ai); }
#ifdef MANGOSBOT_TWO
            static Trigger* hot_streak(PlayerbotAI* ai) { return new HotStreakTrigger(ai); }
            static Trigger* fireball_or_frostfire_bolt_free(PlayerbotAI* ai) { return new FireballOrFrostfireBoltFreeTrigger(ai); }
            static Trigger* finger_of_frost(PlayerbotAI* ai) { return new FingersOfFrostTrigger(ai); }
            static Trigger* mirror_image(PlayerbotAI* ai) { return new MirrorImageTrigger(ai); }
            static Trigger* learn_glyph_of_fireball(PlayerbotAI* ai) { return new LearnGlyphOfFireballTrigger(ai); }
            static Trigger* remove_glyph_of_fireball(PlayerbotAI* ai) { return new RemoveGlyphOfFireballTrigger(ai); }
            static Trigger* learn_glyph_of_frostbolt(PlayerbotAI* ai) { return new LearnGlyphOfFrostboltTrigger(ai); }
            static Trigger* remove_glyph_of_frostbolt(PlayerbotAI* ai) { return new RemoveGlyphOfFrostboltTrigger(ai); }
            static Trigger* learn_glyph_of_living_bomb(PlayerbotAI* ai) { return new LearnGlyphOfLivingBombTrigger(ai); }
            static Trigger* remove_glyph_of_living_bomb(PlayerbotAI* ai) { return new RemoveGlyphOfLivingBombTrigger(ai); }
            static Trigger* learn_glyph_of_mirror_image(PlayerbotAI* ai) { return new LearnGlyphOfMirrorImageTrigger(ai); }
            static Trigger* remove_glyph_of_mirror_image(PlayerbotAI* ai) { return new RemoveGlyphOfMirrorImageTrigger(ai); }
            static Trigger* learn_glyph_of_molten_armor(PlayerbotAI* ai) { return new LearnGlyphOfMoltenArmorTrigger(ai); }
            static Trigger* remove_glyph_of_molten_armor(PlayerbotAI* ai) { return new RemoveGlyphOfMoltenArmorTrigger(ai); }
            static Trigger* no_improved_scorch(PlayerbotAI* ai) { return new NoImprovedScorchDebuffTrigger(ai); }
#else
            static Trigger* no_fire_vulnerability(PlayerbotAI* ai) { return new NoFireVulnerabilityTrigger(ai); }
#endif
#ifndef MANGOSBOT_ZERO
            static Trigger* living_bomb(PlayerbotAI* ai) { return new LivingBombTrigger(ai); }
#endif
        };
    };
};


namespace ai
{
    namespace mage
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["arcane power"] = &AiObjectContextInternal::arcane_power;
                creators["presence of mind"] = &AiObjectContextInternal::presence_of_mind;
                creators["frostbolt"] = &AiObjectContextInternal::frostbolt;
                creators["blizzard"] = &AiObjectContextInternal::blizzard;
                creators["frost nova"] = &AiObjectContextInternal::frost_nova;
                creators["arcane intellect"] = &AiObjectContextInternal::arcane_intellect;
                creators["arcane intellect on party"] = &AiObjectContextInternal::arcane_intellect_on_party;
                creators["arcane brilliance on party"] = &AiObjectContextInternal::arcane_brilliance_on_party;
                creators["conjure water"] = &AiObjectContextInternal::conjure_water;
                creators["conjure food"] = &AiObjectContextInternal::conjure_food;
                creators["molten armor"] = &AiObjectContextInternal::molten_armor;
                creators["mage armor"] = &AiObjectContextInternal::mage_armor;
                creators["ice armor"] = &AiObjectContextInternal::ice_armor;
                creators["frost armor"] = &AiObjectContextInternal::frost_armor;
                creators["fireball"] = &AiObjectContextInternal::fireball;
                creators["pyroblast"] = &AiObjectContextInternal::pyroblast;
                creators["flamestrike"] = &AiObjectContextInternal::flamestrike;
                creators["fire blast"] = &AiObjectContextInternal::fire_blast;
                creators["scorch"] = &AiObjectContextInternal::scorch;
                creators["counterspell"] = &AiObjectContextInternal::counterspell;
                creators["remove curse"] = &AiObjectContextInternal::remove_curse;
                creators["remove curse on party"] = &AiObjectContextInternal::remove_curse_on_party;
                creators["remove lesser curse"] = &AiObjectContextInternal::remove_lesser_curse;
                creators["remove lesser curse on party"] = &AiObjectContextInternal::remove_lesser_curse_on_party;
                creators["icy veins"] = &AiObjectContextInternal::icy_veins;
                creators["combustion"] = &AiObjectContextInternal::combustion;
                creators["ice block"] = &AiObjectContextInternal::ice_block;
                creators["polymorph"] = &AiObjectContextInternal::polymorph;
                creators["spellsteal"] = &AiObjectContextInternal::spellsteal;
                creators["invisibility"] = &AiObjectContextInternal::invisibility;
                creators["evocation"] = &AiObjectContextInternal::evocation;
                creators["arcane blast"] = &AiObjectContextInternal::arcane_blast;
                creators["arcane barrage"] = &AiObjectContextInternal::arcane_barrage;
                creators["arcane missiles"] = &AiObjectContextInternal::arcane_missiles;
                creators["counterspell on enemy healer"] = &AiObjectContextInternal::counterspell_on_enemy_healer;
                creators["fire ward"] = &AiObjectContextInternal::fire_ward;
                creators["frost ward"] = &AiObjectContextInternal::frost_ward;
                creators["blink"] = &AiObjectContextInternal::blink;
                creators["ice barrier"] = &AiObjectContextInternal::ice_barrier;
                creators["mana shield"] = &AiObjectContextInternal::mana_shield;
                creators["arcane explosion"] = &AiObjectContextInternal::arcane_explosion;
                creators["cone of cold"] = &AiObjectContextInternal::cone_of_cold;
                creators["summon water elemental"] = &AiObjectContextInternal::summon_water_elemental;
                creators["ice lance"] = &AiObjectContextInternal::ice_lance;
                creators["cold snap"] = &AiObjectContextInternal::cold_snap;
#ifndef MANGOSBOT_ZERO
                creators["dragon's breath"] = &AiObjectContextInternal::dragons_breath;
                creators["blast wave"] = &AiObjectContextInternal::blast_wave;
                creators["living bomb"] = &AiObjectContextInternal::living_bomb;
#endif
#ifdef MANGOSBOT_TWO
                creators["frostfire bolt"] = &AiObjectContextInternal::frostfire_bolt;
                creators["deep freeze"] = &AiObjectContextInternal::deep_freeze;
                creators["mirror image"] = &AiObjectContextInternal::mirror_image;
                creators["learn glyph of fireball"] = &AiObjectContextInternal::learn_glyph_of_fireball;
                creators["remove glyph of fireball"] = &AiObjectContextInternal::remove_glyph_of_fireball;
                creators["learn glyph of frostbolt"] = &AiObjectContextInternal::learn_glyph_of_frostbolt;
                creators["remove glyph of frostbolt"] = &AiObjectContextInternal::remove_glyph_of_frostbolt;
                creators["learn glyph of living bomb"] = &AiObjectContextInternal::learn_glyph_of_living_bomb;
                creators["remove glyph of living bomb"] = &AiObjectContextInternal::remove_glyph_of_living_bomb;
                creators["learn glyph of mirror image"] = &AiObjectContextInternal::learn_glyph_of_mirror_image;
                creators["remove glyph of mirror image"] = &AiObjectContextInternal::remove_glyph_of_mirror_image;
                creators["learn glyph of molten armor"] = &AiObjectContextInternal::learn_glyph_of_molten_armor;
                creators["remove glyph of molten armor"] = &AiObjectContextInternal::remove_glyph_of_molten_armor;
#endif
            }

        private:
            static Action* ice_lance(PlayerbotAI* ai) { return new CastIceLanceAction(ai); }
            static Action* summon_water_elemental(PlayerbotAI* ai) { return new CastSummonWaterElementalAction(ai); }
            static Action* cone_of_cold(PlayerbotAI* ai) { return new CastConeOfColdAction(ai); }
            static Action* arcane_explosion(PlayerbotAI* ai) { return new CastArcaneExplosionAction(ai); }
            static Action* mana_shield(PlayerbotAI* ai) { return new CastManaShieldAction(ai); }
            static Action* ice_barrier(PlayerbotAI* ai) { return new CastIceBarrierAction(ai); }
            static Action* blink(PlayerbotAI* ai) { return new CastBlinkAction(ai); }
            static Action* frost_ward(PlayerbotAI* ai) { return new CastFrostWardAction(ai); }
            static Action* fire_ward(PlayerbotAI* ai) { return new CastFireWardAction(ai); }
            static Action* presence_of_mind(PlayerbotAI* ai) { return new CastPresenceOfMindAction(ai); }
            static Action* arcane_power(PlayerbotAI* ai) { return new CastArcanePowerAction(ai); }
            static Action* arcane_missiles(PlayerbotAI* ai) { return new CastArcaneMissilesAction(ai); }
            static Action* arcane_barrage(PlayerbotAI* ai) { return new CastArcaneBarrageAction(ai); }
            static Action* arcane_blast(PlayerbotAI* ai) { return new CastArcaneBlastAction(ai); }
            static Action* frostbolt(PlayerbotAI* ai) { return new CastFrostboltAction(ai); }
            static Action* blizzard(PlayerbotAI* ai) { return new CastBlizzardAction(ai); }
            static Action* frost_nova(PlayerbotAI* ai) { return new CastFrostNovaAction(ai); }
            static Action* arcane_intellect(PlayerbotAI* ai) { return new CastArcaneIntellectAction(ai); }
            static Action* arcane_intellect_on_party(PlayerbotAI* ai) { return new CastArcaneIntellectOnPartyAction(ai); }
            static Action* arcane_brilliance_on_party(PlayerbotAI* ai) { return new CastArcaneBrillianceOnPartyAction(ai); }
            static Action* conjure_water(PlayerbotAI* ai) { return new CastConjureWaterAction(ai); }
            static Action* conjure_food(PlayerbotAI* ai) { return new CastConjureFoodAction(ai); }
            static Action* molten_armor(PlayerbotAI* ai) { return new CastMoltenArmorAction(ai); }
            static Action* mage_armor(PlayerbotAI* ai) { return new CastMageArmorAction(ai); }
            static Action* ice_armor(PlayerbotAI* ai) { return new CastIceArmorAction(ai); }
            static Action* frost_armor(PlayerbotAI* ai) { return new CastFrostArmorAction(ai); }
            static Action* fireball(PlayerbotAI* ai) { return new CastFireballAction(ai); }
            static Action* pyroblast(PlayerbotAI* ai) { return new CastPyroblastAction(ai); }
            static Action* flamestrike(PlayerbotAI* ai) { return new CastFlamestrikeAction(ai); }
            static Action* fire_blast(PlayerbotAI* ai) { return new CastFireBlastAction(ai); }
            static Action* scorch(PlayerbotAI* ai) { return new CastScorchAction(ai); }
            static Action* counterspell(PlayerbotAI* ai) { return new CastCounterspellAction(ai); }
            static Action* remove_curse(PlayerbotAI* ai) { return new CastRemoveCurseAction(ai); }
            static Action* remove_curse_on_party(PlayerbotAI* ai) { return new CastRemoveCurseOnPartyAction(ai); }
            static Action* remove_lesser_curse(PlayerbotAI* ai) { return new CastRemoveLesserCurseAction(ai); }
            static Action* remove_lesser_curse_on_party(PlayerbotAI* ai) { return new CastRemoveLesserCurseOnPartyAction(ai); }
            static Action* icy_veins(PlayerbotAI* ai) { return new CastIcyVeinsAction(ai); }
            static Action* combustion(PlayerbotAI* ai) { return new CastCombustionAction(ai); }
            static Action* ice_block(PlayerbotAI* ai) { return new CastIceBlockAction(ai); }
            static Action* polymorph(PlayerbotAI* ai) { return new CastPolymorphAction(ai); }
            static Action* spellsteal(PlayerbotAI* ai) { return new CastSpellstealAction(ai); }
            static Action* invisibility(PlayerbotAI* ai) { return new CastInvisibilityAction(ai); }
            static Action* evocation(PlayerbotAI* ai) { return new CastEvocationAction(ai); }
            static Action* counterspell_on_enemy_healer(PlayerbotAI* ai) { return new CastCounterspellOnEnemyHealerAction(ai); }
            static Action* cold_snap(PlayerbotAI* ai) { return new CastColdSnapAction(ai); }
#ifndef MANGOSBOT_ZERO
            static Action* dragons_breath(PlayerbotAI* ai) { return new CastDragonsBreathAction(ai); }
            static Action* blast_wave(PlayerbotAI* ai) { return new CastBlastWaveAction(ai); }
            static Action* living_bomb(PlayerbotAI* ai) { return new CastLivingBombAction(ai); }
#endif
#ifdef MANGOSBOT_TWO
            static Action* frostfire_bolt(PlayerbotAI* ai) { return new CastFrostfireBoltAction(ai); }
            static Action* deep_freeze(PlayerbotAI* ai) { return new DeepFreezeAction(ai); }
            static Action* mirror_image(PlayerbotAI* ai) { return new MirrorImageAction(ai); }
            static Action* learn_glyph_of_fireball(PlayerbotAI* ai) { return new LearnGlyphOfFireballAction(ai); }
            static Action* remove_glyph_of_fireball(PlayerbotAI* ai) { return new RemoveGlyphOfFireballAction(ai); }
            static Action* learn_glyph_of_frostbolt(PlayerbotAI* ai) { return new LearnGlyphOfFrostboltAction(ai); }
            static Action* remove_glyph_of_frostbolt(PlayerbotAI* ai) { return new RemoveGlyphOfFrostboltAction(ai); }
            static Action* learn_glyph_of_living_bomb(PlayerbotAI* ai) { return new LearnGlyphOfLivingBombAction(ai); }
            static Action* remove_glyph_of_living_bomb(PlayerbotAI* ai) { return new RemoveGlyphOfLivingBombAction(ai); }
            static Action* learn_glyph_of_mirror_image(PlayerbotAI* ai) { return new LearnGlyphOfMirrorImageAction(ai); }
            static Action* remove_glyph_of_mirror_image(PlayerbotAI* ai) { return new RemoveGlyphOfMirrorImageAction(ai); }
            static Action* learn_glyph_of_molten_armor(PlayerbotAI* ai) { return new LearnGlyphOfMoltenArmorAction(ai); }
            static Action* remove_glyph_of_molten_armor(PlayerbotAI* ai) { return new RemoveGlyphOfMoltenArmorAction(ai); }
#endif
        };
    };
};



MageAiObjectContext::MageAiObjectContext(PlayerbotAI* ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::mage::StrategyFactoryInternal());
    strategyContexts.Add(new ai::mage::MageStrategyFactoryInternal());
    strategyContexts.Add(new ai::mage::MageBuffStrategyFactoryInternal());
    actionContexts.Add(new ai::mage::AiObjectContextInternal());
    triggerContexts.Add(new ai::mage::TriggerFactoryInternal());
}
