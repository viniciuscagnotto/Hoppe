#ifndef __SAVE_DATA_H__
#define __SAVE_DATA_H__

class SaveData
{
public:
	struct SSaveData{
		int topScore;
		bool mute;
		bool tutorial;
		
		SSaveData(){
			topScore = 0;
			mute = false;
			tutorial = true;
		};
	};

	SSaveData m_saveData;
private:
	std::string m_fileName;

public:
	SaveData();
	~SaveData();

	void LoadSave();
	void Save();
};

extern SaveData* g_pSaveData;

#endif //__SAVE_DATA_H__