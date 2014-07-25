#if !defined(__TRIGGERS_MANAGER_H__)
#define __TRIGGERS_MANAGER_H__

class TriggersManager
{
public:
	static const uint s_kMaxTriggers = 64;
	static const uint s_kLastTriggers = 10;

	enum ETriggerType{
		kTriggerType_Stars_Pattern1 = 0,
		kTriggerType_Stars_Pattern2,
		kTriggerType_Stars_Pattern3,
		kTriggerType_Stars_Pattern4,
		kTriggerType_Stars_Pattern5,

		kTriggerType_Asteroid_Small,
		kTriggerType_Asteroid_Small_Shower,
		kTriggerType_Asteroid_Small_Wall,
		kTriggerType_Asteroid_Big,
		kTriggerType_Asteroid_Big_Shower,
		kTriggerType_Asteroid_Big_Wall,

		kTriggerType_Satellite,
		kTriggerType_SatelliteMix,

		kTriggerType_Comet,
		kTriggerType_Comet_Shower_LeftToRight,
		kTriggerType_Comet_Shower_RightToLeft,
		kTriggerType_Comet_Shower_Center,
		kTriggerType_Comet_Shower_Diagonal,

		kTriggerType_BlackHole,
		kTriggerType_BlackHole_Wall,

		kTriggerType_Item,
		kTriggerType_Count
	};

	struct STriggerRange{
		Point distanceRange;
		Point amountRange;
		ETriggerType type;
		float chance;

		STriggerRange(){
			distanceRange = Point();
			amountRange = Point();
			chance = 1.0f;
			type = kTriggerType_Count;
		};

		STriggerRange(ETriggerType t, float c, Point dRange, Point aRange){
			type = t;
			chance = c;
			distanceRange = dRange;
			amountRange = aRange;
		};
	};

	struct STrigger{
		ETriggerType type;
		float distance;
		uint amount;

		STrigger(){
			type = kTriggerType_Count;
			distance = 0.0f;
			amount = 0;
		};

		STrigger(ETriggerType t, float d, uint a){
			type = t;
			distance = d;
			amount = a;
		}
	};

private:
	EasyArray<STriggerRange, s_kMaxTriggers> m_triggers;
	uint m_numTriggers;

	EasyArray<ETriggerType, s_kLastTriggers> m_lastTriggers;

public:
	TriggersManager();
	~TriggersManager();

	void Reset();
	void InitTriggers();
	STrigger GenerateTrigger(float distance, float gameSpeed);
	STriggerRange GetTriggerAtDistance(float distance);
};

#endif  // __TRIGGERS_MANAGER_H__

