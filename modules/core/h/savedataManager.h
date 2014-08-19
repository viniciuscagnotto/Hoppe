#ifndef __SAVEDATA_MANAGER_H__
#define __SAVEDATA_MANAGER_H__

class SaveDataManager
{
public:
	SaveDataManager();
	~SaveDataManager();

	void Init();
};

extern SaveDataManager* g_pSaveDataManager;


#endif //__SAVEDATA_MANAGER_H__