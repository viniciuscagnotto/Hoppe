#include "core.h"

#define FACEBOOK_APP_ID	"955358454521782" //Actual: Dots Rush - 955358454521782

FacebookManager* g_pFacebookManager = 0;

FacebookManager::~FacebookManager(){
}

bool FacebookManager::Init(){
	if (s3eFacebookAvailable() != S3E_TRUE)
		return false;
	return true;
}

bool FacebookManager::LogIn(){
	if (s3eFacebookAvailable() != S3E_TRUE)
		return false;

	if (pCurrentSession == 0)
		pCurrentSession = s3eFBInit(FACEBOOK_APP_ID);

	if (pCurrentSession){
		const char* permissions[] = { "read_stream", "publish_stream" };
		if (s3eFBSession_Login(pCurrentSession, LoginCallback, this, permissions, sizeof(permissions) / sizeof(permissions[0])) != S3E_TRUE)
			return false;
	}

	return true;
}

void FacebookManager::LoginCallback(s3eFBSession *pSession, s3eResult *pResult, void *pData){
	FacebookManager *pContext = (FacebookManager *)pData;
	if (*pResult == S3E_RESULT_SUCCESS){
		pContext->loggedIn = true;
		pContext->PostUpdate();
	}else{
		pContext->loggedIn = false;
		pContext->waiting = false;
	}
}

bool FacebookManager::PostUpdate(const char* update){
	waiting = true;
	statusUpdate = update;
	if (!PostUpdate())
		return false;
	WaitUntilCompleted();
	return true;
}

bool FacebookManager::PostUpdate(){
	if (loggedIn){
		pRequest = s3eFBRequest_WithMethodName(pCurrentSession, "facebook.stream.publish", "POST");
		s3eFBRequest_AddParamString(pRequest, "message", statusUpdate.c_str());
		s3eResult result = s3eFBRequest_Send(pRequest, RequestCallback, this);
		if (result != S3E_RESULT_SUCCESS){
			s3eFBRequest_Delete(pRequest);
			pRequest = NULL;
			return false;
		}
	}else
		return LogIn();

	return true;
}

void FacebookManager::RequestCallback(s3eFBRequest *pRequest, s3eResult *pResult, void *pData){
	FacebookManager *pContext = (FacebookManager *)pData;
	s3eFBRequest_Delete(pContext->pRequest);
	pContext->pRequest = NULL;
	pContext->waiting = false;
}

void FacebookManager::WaitUntilCompleted(){
	while (waiting && !s3eDeviceCheckQuitRequest())
		s3eDeviceYield(100);
}
