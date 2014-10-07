#include "core.h"

GameCenterManager* g_pGameCenterManager = 0;

GameCenterManager::~GameCenterManager(){
	
}

void GameCenterManager::Init(){
	if (!s3eIOSGameCenterAvailable())
		return;

	if (!m_authenticated)
		m_authenticated = s3eIOSGameCenterGetInt(S3E_IOSGAMECENTER_LOCAL_PLAYER_IS_AUTHENTICATED) ? true : false;

	s3eIOSGameCenterAuthenticate(AuthenticationCallback, NULL);
}

void GameCenterManager::AuthenticationCallback(s3eIOSGameCenterError* error, void* userData)
{
	if (*error != S3E_IOSGAMECENTER_ERR_NONE)
	{
		g_pGameCenterManager->m_authenticated = false;
		return;
	}

	g_pGameCenterManager->m_authenticated = true;
	//const char* alias = s3eIOSGameCenterGetString(S3E_IOSGAMECENTER_LOCAL_PLAYER_ALIAS);
	//s3eIOSGameCenterSetInviteHandler(InviteCallback);
}

