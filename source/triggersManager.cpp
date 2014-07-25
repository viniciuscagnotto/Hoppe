#include "include.h"

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
	m_triggers[m_numTriggers++] = STriggerRange(kTriggerType_Asteroid_Small, 1.0f, Point(0, 50), Point(1, 3));
}

void TriggersManager::Reset(){
	for (uint i = 0; i < s_kLastTriggers; i++)
		m_lastTriggers[i] = kTriggerType_Count;
}

TriggersManager::STriggerRange TriggersManager::GetTriggerAtDistance(float distance){
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