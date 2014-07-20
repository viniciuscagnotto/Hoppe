#include "include.h"

#define FRAME_TIME  (30.0f / 1000.0f)
//game ID
#define FLURRY_API_KEY "WQFTM6SVNXKJ7958HXNP"
						
CTweenManager*  g_pTweener = 0;

int main()
{
    Iw2DInit();
	g_pSaveDataManager = new SaveDataManager();
	g_pResourceManager = new ResourceManager();
    g_pTweener = new CTweenManager();
    g_pInput = new InputManager();
    g_pAudio = new AudioManager();
	g_pSpriteManager = new SpriteManager();
    g_pSceneManager = new SceneManager();

    if (s3eFlurryAvailable())
        s3eFlurryStartSession(FLURRY_API_KEY);

	g_pSceneManager->Resume();

    while (!s3eDeviceCheckQuitRequest())
    {
        uint64 new_time = s3eTimerGetMs();

        g_pInput->Update();
        g_pAudio->Update();
        g_pTweener->Update(FRAME_TIME);
        g_pSceneManager->Update(FRAME_TIME);

		Iw2DSurfaceClear(0xff000000);
        g_pSceneManager->Render();
		Iw2DSurfaceShow();

        int yield = (int)(FRAME_TIME * 1000 - (s3eTimerGetMs() - new_time));
        if (yield < 0)
            yield = 0;
        // Yield to OS
        s3eDeviceYield(yield);
    }

    if (s3eFlurryAvailable())
        s3eFlurryEndSession();

    delete g_pAudio;
    delete g_pInput;
    delete g_pSceneManager;
	delete g_pSpriteManager;
    delete g_pTweener;
	delete g_pResourceManager;
	delete g_pSaveDataManager;
    Iw2DTerminate();

    return 0;
}
