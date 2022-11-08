#include "botpch.h"
#include "../../playerbot.h"
#include "WaitForAttackAction.h"
#include "../generic/CombatStrategy.h"

using namespace ai;

bool WaitForAttackSetTimeAction::Execute(Event& event)
{
    string newTimeStr = event.getParam();
    if (!newTimeStr.empty())
    {
        // Check if the param is a number
        if (newTimeStr.find_first_not_of("0123456789") == std::string::npos)
        {
            const int newTime = stoi(newTimeStr.c_str());
            if (newTime <= 99)
            {
                ai->GetAiObjectContext()->GetValue<uint8>("wait for attack time")->Set(newTime);
                ostringstream out; out << "Wait for attack time set to " << newTime << " seconds";
                ai->TellMaster(out);
                return true;
            }
            else
            {
                ai->TellError("Please provide valid time to set (in seconds) between 1 and 99");
            }
        }
        else
        {
            ai->TellError("Please provide valid time to set (in seconds) between 1 and 99");
        }
    }
    else
    {
        ai->TellError("Please provide a time to set (in seconds)");
    }

    return false;   
}

bool WaitForAttackKeepSafeDistanceAction::Execute(Event& event)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (target)
    {
        const Map* map = target->GetMap();
        const WorldPosition botPosition(bot);
        const WorldPosition targetPosition(target);
        const float safeDistance = WaitForAttackStrategy::GetSafeDistance();
        const float safeDistanceThreshold = WaitForAttackStrategy::GetSafeDistanceThreshold();

        // Generate points around the target
        std::vector<WorldPosition> points;
        const float angleIncrement = (10.0f / 180.0f) * (M_PI_F);
        for (float angle = 0.0f; angle < (2.0f * M_PI_F); angle += angleIncrement)
        {
            float x = targetPosition.getX() + safeDistance * cos(angle);
            float y = targetPosition.getY() + safeDistance * sin(angle);
            float z = targetPosition.getZ() + 1.0f;

            // Check walls and obstacles around the target
#ifndef MANGOSBOT_TWO
            map->GetHitPosition(targetPosition.getX(), targetPosition.getY(), targetPosition.getZ() + 1.0f, x, y, z, -0.5f);
#else
            map->GetHitPosition(targetPosition.getX(), targetPosition.getY(), targetPosition.getZ() + 1.0f, x, y, z, bot->GetPhaseMask(), -0.5f);
#endif                       
            // Reset z to original value to avoid too much difference from original point before GetHeightInRange
            z = targetPosition.getZ();

            // Get proper height coordinate
#ifndef MANGOSBOT_TWO
            if (map->GetHeightInRange(x, y, z))
#else
            if (map->GetHeightInRange(bot->GetPhaseMask(), x, y, z))
#endif
            {
                // Project vector to get only positive value
                const float ab = fabs(botPosition.getX() - x);
                const float ac = fabs(botPosition.getZ() - z);

                // Slope represented by c angle (in radian)
                // 50 (degrees) max seem best value for walkable slope
                const float MAX_SLOPE_IN_RADIAN = 50.0f / 180.0f * M_PI_F;

                // Check ab vector to avoid divide by 0
                if (ab > 0.0f)
                {
                    // Compute c angle and convert it from radians to degrees
                    const float slope = atan(ac / ab);
                    if (slope < MAX_SLOPE_IN_RADIAN)
                    {
                        points.push_back(WorldPosition(target->GetMapId(), x, y, z));
                    }
                }
            }
        }

        if (!points.empty())
        {
            // Filter and select the best point
            float bestDistance = 9999.0f;
            const WorldPosition* bestPoint = nullptr;
            for (const WorldPosition& point : points)
            {
                // Check if the point is not too close to the target
                if (target->GetDistance(point.getX(), point.getY(), point.getZ()) > (safeDistance - safeDistanceThreshold))
                {
                    // Check if the target is visible from the point
                    if (target->IsWithinLOS(point.getX(), point.getY(), point.getZ() + bot->GetCollisionHeight()))
                    {
                        const float distanceToPoint = sqrt(bot->GetDistance(point.getX(), point.getY(), point.getZ()));
                        if (distanceToPoint < bestDistance)
                        {
                            bestPoint = &point;
                            bestDistance = distanceToPoint;
                        }

                        if (ai->HasStrategy("debug move", BotState::BOT_STATE_COMBAT))
                        {
                            Creature* wpCreature = bot->SummonCreature(15631, point.getX(), point.getY(), point.getZ(), 0.0f, TEMPSPAWN_TIMED_DESPAWN, 5000.0f);
                        }
                    }
                }
            }

            if (bestPoint)
            {
                // Move to the best point
                return MoveTo(bestPoint->getMapId(), bestPoint->getX(), bestPoint->getY(), bestPoint->getZ());
            }
        }
    }

    return false;
}