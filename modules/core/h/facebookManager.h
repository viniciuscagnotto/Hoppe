#ifndef __FACEBOOK_MANAGER_H__
#define __FACEBOOK_MANAGER_H__

#include "s3eFacebook.h"

class FacebookManager
{
public:
	bool loggedIn;
	bool waiting;
protected:
	std::string statusUpdate;
	s3eFBSession* pCurrentSession;
	s3eFBRequest* pRequest;
	
	bool LogIn();
	void WaitUntilCompleted();

public:
	FacebookManager() : pCurrentSession(0), pRequest(NULL), loggedIn(false), waiting(false) {}
	~FacebookManager();

	bool Init();
	bool PostUpdate(const char* update);
	bool PostUpdate();
	static void LoginCallback(s3eFBSession *pSession, s3eResult *pResult, void *pData);
	static void RequestCallback(s3eFBRequest *pRequest, s3eResult *pResult, void *pData);
};

extern FacebookManager* g_pFacebookManager;

#endif //__FACEBOOK_MANAGER_H__
