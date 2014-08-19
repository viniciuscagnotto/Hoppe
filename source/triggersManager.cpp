#include "header.h"

TriggersManager::TriggersManager()
{
	InitTriggers();
	Reset();
}

TriggersManager::~TriggersManager()
{
	
}

void TriggersManager::InitTriggers(){
	m_numTriggers = 0;
	m_triggers[m_numTriggers++] = STriggerRange(kTriggerType_Asteroid_Small, 1.0f, PointInt(0, 5000), PointInt(1, 3));
	m_triggers[m_numTriggers++] = STriggerRange(kTriggerType_Asteroid_Big, 0.75f, PointInt(0, 5000), PointInt(1, 2));
}

void TriggersManager::Reset(){
	for (uint i = 0; i < s_kLastTriggers; i++)
		m_lastTriggers[i] = STrigger();
}

TriggersManager::STrigger TriggersManager::GenerateTrigger(int distance){
	if (HasTriggetAtDistance(distance))
		return STrigger();

	STriggerRange triggerRange = GetTriggerAtDistance(distance);
	if (triggerRange.type != kTriggerType_Count){
		STrigger trigger;
		trigger.type = triggerRange.type;
		trigger.amount = RandomInt(triggerRange.amountRange.x, triggerRange.amountRange.y);
		trigger.distance = distance;
		m_lastTriggers.AddAt(0, trigger);
		return trigger;
	}

	return STrigger();
}

TriggersManager::STriggerRange TriggersManager::GetTriggerAtDistance(int distance){
	EasyArray<STriggerRange, s_kMaxTriggers> possibleTriggers;
	uint numPossibleTriggers = 0;
	
	for (uint i = 0; i < m_numTriggers; i++){
		STriggerRange trigger = m_triggers[i];
		if (distance > trigger.distanceRange.x && distance < trigger.distanceRange.y)
			possibleTriggers[numPossibleTriggers++] = trigger;
	}

	STriggerRange triggerRange;
	if (numPossibleTriggers > 0){
		bool found = false;
		while (!found){
			uint chosenIndex = RandomInt(0, numPossibleTriggers-1);
			if (possibleTriggers[chosenIndex].chance >= Random()){
				triggerRange = possibleTriggers[chosenIndex];
				found = true;
			}
		}
	}else{

	}

	return triggerRange;
}

bool TriggersManager::HasTriggetAtDistance(int distance){
	for (uint i = 0; i < s_kLastTriggers; i++){
		if (m_lastTriggers[i].distance == distance)
			return true;
	}

	return false;
}