#include "include.h"

#define FRAME_TIME  (30.0f / 1000.0f)
//game ID
#define FLURRY_API_KEY "WQFTM6SVNXKJ7958HXNP"
						
CTweenManager*  g_pTweener = 0;

int main()
{
    Iw2DInit();
    g_pResources = new Resources();
    g_pTweener = new CTweenManager();
    g_pInput = new Input();
    g_pAudio = new Audio();
    g_pSceneManager = new SceneManager();

    if (s3eFlurryAvailable())
        s3eFlurryStartSession(FLURRY_API_KEY);

    Game* game = new Game();
    game->SetName("game");
    game->Init(8, 8);
    g_pSceneManager->Add(game);
    game->newGame();

    MainMenu* main_menu = new MainMenu();
    main_menu->SetName("mainmenu");
    main_menu->Init();
    g_pSceneManager->Add(main_menu);

    PauseMenu* pause_menu = new PauseMenu();
    pause_menu->SetName("pausemenu");
    pause_menu->Init();
    g_pSceneManager->Add(pause_menu);

    g_pSceneManager->SwitchTo(main_menu);

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
    delete g_pTweener;
    delete g_pResources;
    Iw2DTerminate();

    return 0;
}
