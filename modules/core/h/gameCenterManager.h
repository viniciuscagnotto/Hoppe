#ifndef __GAME_CENTER_MANAGER_H__
#define __GAME_CENTER_MANAGER_H__

#include "s3eIOSGameCenter.h"

class GameCenterManager
{
public:
	bool m_authenticated;

protected:
	

public:
	GameCenterManager() : m_authenticated(false) {}
	~GameCenterManager();

	void Init();

	static void AuthenticationCallback(s3eIOSGameCenterError* error, void* userData);
};

extern GameCenterManager* g_pGameCenterManager;

#endif // __GAME_CENTER_MANAGER_H__
