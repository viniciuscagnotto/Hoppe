#include "header.h"

int Game::s_gameSpacement = 0;
bool Game::s_is2X = false;
bool Game::s_isIphone5 = false;

Game::Game(){
	Init();
}

Game::~Game(){

}

void Game::Init(){
	Iw2DInit();

	s_gameSpacement = 3;
	if (IwGxGetScreenHeight() > 480)
		s_is2X = true;

	if (IwGxGetScreenHeight() > 960){
		s_gameSpacement = 6;
		s_isIphone5 = true;
	}

	s3eDeviceRegister(S3E_DEVICE_PAUSE, (s3eCallback)PauseCB, NULL);
	
	LoadResources();
	g_pSaveData = new SaveData();
	g_pTweener = new CTweenManager();
	g_pInput = new InputManager();

	g_pAudio = new AudioManager();
	g_pAudio->SetMute(g_pSaveData->m_saveData.mute);

	g_pSpriteManager = new SpriteManager();
	g_pSceneManager = new SceneManager();

	if (s3eFlurryAvailable())
		s3eFlurryStartSession(FLURRY_API_KEY);

	g_pAdsManager = new AdsManager();
	if (g_pAdsManager->Init())
		g_pAdsManager->NewAd(0, (Iw2DGetSurfaceHeight() * (TOP_ADS_HEIGHT / 100.0f)), AdsManager::kAdProvider_Leadbolt, AdsManager::kAdType_Banner, "566664249");

	g_pSceneManager->Resume();
}

void Game::LoadResources(){
	g_pResourceManager = new ResourceManager();
	
	//Atlases

	//Graphics
	if (s_is2X){
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Logo_Main, "textures/logo_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Tutorial_Main, "textures/tutorial_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Main, "textures/pause_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Sound, "textures/options_sound_pause_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_On, "textures/options_sound_pause_on_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Off, "textures/options_sound_pause_off_2x.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_StartGame, "textures/play_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Back, "textures/back_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Settings, "textures/settings_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Resume, "textures/resume_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Exit, "textures/exit_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Pause, "textures/pause_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_PlayAgain, "textures/play_again_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_MainMenu, "textures/main_menu_btn_2x.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_Options, "textures/options_title_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_BestScore, "textures/best_score_title_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_YourScore, "textures/your_score_title_2x.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_Sound, "textures/options_sound_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_On, "textures/options_on_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_Off, "textures/options_off_2x.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlackCircle, "textures/black_circle_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlackSquare, "textures/black_square_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_WhiteCircle, "textures/white_circle_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_WhiteSquare, "textures/white_square_2x.png");
	}else{
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Logo_Main, "textures/logo.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Tutorial_Main, "textures/tutorial.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Main, "textures/pause.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Sound, "textures/options_sound_pause.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_On, "textures/options_sound_pause_on.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Off, "textures/options_sound_pause_off.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_StartGame, "textures/play_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Back, "textures/back_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Settings, "textures/settings_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Resume, "textures/resume_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Exit, "textures/exit_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Pause, "textures/pause_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_PlayAgain, "textures/play_again_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_MainMenu, "textures/main_menu_btn.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_Options, "textures/options_title.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_BestScore, "textures/best_score_title.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_YourScore, "textures/your_score_title.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_Sound, "textures/options_sound.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_On, "textures/options_on.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_Off, "textures/options_off.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlackCircle, "textures/black_circle.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlackSquare, "textures/black_square.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_WhiteCircle, "textures/white_circle.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_WhiteSquare, "textures/white_square.png");
	}

	//Fonts
	g_pResourceManager->RegisterFont((uint)kGameFonts_Arial_8, "fonts/arial8.gxfont");

}

void Game::Update(){

	while (!s3eDeviceCheckQuitRequest()){
		uint64 newTime = s3eTimerGetMs();

		g_pInput->Update();
		g_pAudio->Update();
		g_pTweener->Update(FRAME_TIME);
		g_pSceneManager->Update(FRAME_TIME);

		Iw2DSurfaceClear(0xffffffff);
		g_pSceneManager->Render();
		Iw2DSurfaceShow();

		int yield = (int)(FRAME_TIME * 1000 - (s3eTimerGetMs() - newTime));
		if (yield < 0)
			yield = 0;
		s3eDeviceYield(yield);
	}
}

void Game::Cleanup(){
	s3eDeviceUnRegister(S3E_DEVICE_PAUSE, (s3eCallback)PauseCB);

	if (s3eFlurryAvailable())
		s3eFlurryEndSession();

	delete g_pAudio;
	delete g_pInput;
	delete g_pSceneManager;
	delete g_pAdsManager;
	delete g_pSpriteManager;
	delete g_pTweener;
	delete g_pResourceManager;
	delete g_pSaveData;

	Iw2DTerminate();
}

int32 Game::PauseCB(void* pSystemData, void* pUuserData){
	Gameplay::s_paused = true;
	return 1;
}