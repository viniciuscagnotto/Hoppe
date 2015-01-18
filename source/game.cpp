#include "header.h"

float Game::s_scaleFactor = 1.0f;

Game::Game(){
	Init();
}

Game::~Game(){

}

void Game::Init(){
	Iw2DInit();

	s_scaleFactor = (float)Iw2DGetSurfaceWidth() / (float)SCALE_BASE;
	s3eDeviceRegister(S3E_DEVICE_PAUSE, (s3eCallback)PauseCB, NULL);
	
	LoadResources();
	g_pSaveData = new SaveData();
	g_pTweener = new CTweenManager();
	g_pInput = new InputManager();

	g_pAudio = new AudioManager();
	g_pAudio->SetMute(g_pSaveData->m_saveData.mute);

	g_pSpriteManager = new SpriteManager();
	g_pSceneManager = new SceneManager();

	//if (s3eFlurryAvailable())
	//	s3eFlurryStartSession(FLURRY_API_KEY);

	g_pGameCenterManager = new GameCenterManager();
	//g_pGameCenterManager->Init();

	g_pFacebookManager = new FacebookManager();
	if (!g_pFacebookManager->Init()){
		delete g_pFacebookManager;
		g_pFacebookManager = 0;
	}

	g_pAdsManager = new AdsManager();
	if (g_pAdsManager->Init())
		g_pAdsManager->NewAd(0, (Iw2DGetSurfaceHeight() * (TOP_ADS_HEIGHT / 100.0f)), AdsManager::kAdProvider_Leadbolt, AdsManager::kAdType_Banner, "126362352");

	g_pSceneManager->Resume();
}

void Game::LoadResources(){
	g_pResourceManager = new ResourceManager();
	
	//Atlases

	//Graphics
	//if (s_is2X){
	/*	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Tutorial_Main, "textures/tutorial_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Tutorial_Arrow, "textures/arrow_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Main, "textures/pause_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Sound, "textures/options_sound_pause_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_On, "textures/options_sound_pause_on_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Off, "textures/options_sound_pause_off_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_On_Text, "textures/options_sound_pause_on_text_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Off_Text, "textures/options_sound_pause_off_text_2x.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_StartGame, "textures/play_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Back, "textures/back_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Settings, "textures/settings_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Resume, "textures/resume_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Exit, "textures/exit_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Pause, "textures/pause_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_PlayAgain, "textures/play_again_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_MainMenu, "textures/main_menu_btn_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Facebook, "textures/facebook_icon_2x.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_Options, "textures/options_title_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_BestScore, "textures/best_score_title_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_YourScore, "textures/your_score_title_2x.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_Sound, "textures/options_sound_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_Tutorial, "textures/options_tutorial_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_On, "textures/options_on_2x.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_Off, "textures/options_off_2x.png");
	*/
	//}else{
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Tutorial_Main, "textures/tutorial.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Tutorial_Arrow, "textures/arrow.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Main, "textures/pause.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Sound, "textures/options_sound_pause.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_On, "textures/options_sound_pause_on.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Off, "textures/options_sound_pause_off.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_On_Text, "textures/options_sound_pause_on_text.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Pause_Off_Text, "textures/options_sound_pause_off_text.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_StartGame, "textures/play_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Back, "textures/back_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Settings, "textures/settings_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Resume, "textures/resume_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Exit, "textures/exit_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Pause, "textures/pause_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_PlayAgain, "textures/play_again_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_MainMenu, "textures/main_menu_btn.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_Facebook, "textures/facebook_icon.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_Options, "textures/options_title.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_BestScore, "textures/best_score_title.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Title_YourScore, "textures/your_score_title.png");

		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_Sound, "textures/options_sound.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_Tutorial, "textures/options_tutorial.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_On, "textures/options_on.png");
		g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Options_Off, "textures/options_off.png");
	//}

	//Logo
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Logo_Main, "textures/logo.png");

	//Reds
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedStrokeRed, "textures/red_stroke_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedStrokeBlue, "textures/red_stroke_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedStrokeGreen, "textures/red_stroke_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedStrokeIndigo, "textures/red_stroke_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedStrokeOrange, "textures/red_stroke_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedStrokeYellow, "textures/red_stroke_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedStrokeViolet, "textures/red_stroke_violet.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedFilledRed, "textures/red_filled_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedFilledBlue, "textures/red_filled_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedFilledGreen, "textures/red_filled_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedFilledIndigo, "textures/red_filled_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedFilledOrange, "textures/red_filled_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedFilledYellow, "textures/red_filled_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_RedFilledViolet, "textures/red_filled_violet.png");

	//Blues
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueStrokeRed, "textures/blue_stroke_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueStrokeBlue, "textures/blue_stroke_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueStrokeGreen, "textures/blue_stroke_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueStrokeIndigo, "textures/blue_stroke_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueStrokeOrange, "textures/blue_stroke_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueStrokeYellow, "textures/blue_stroke_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueStrokeViolet, "textures/blue_stroke_violet.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueFilledRed, "textures/blue_filled_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueFilledBlue, "textures/blue_filled_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueFilledGreen, "textures/blue_filled_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueFilledIndigo, "textures/blue_filled_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueFilledOrange, "textures/blue_filled_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueFilledYellow, "textures/blue_filled_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlueFilledViolet, "textures/blue_filled_violet.png");

	//Greens
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenStrokeRed, "textures/green_stroke_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenStrokeBlue, "textures/green_stroke_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenStrokeGreen, "textures/green_stroke_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenStrokeIndigo, "textures/green_stroke_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenStrokeOrange, "textures/green_stroke_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenStrokeYellow, "textures/green_stroke_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenStrokeViolet, "textures/green_stroke_violet.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenFilledRed, "textures/green_filled_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenFilledBlue, "textures/green_filled_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenFilledGreen, "textures/green_filled_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenFilledIndigo, "textures/green_filled_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenFilledOrange, "textures/green_filled_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenFilledYellow, "textures/green_filled_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_GreenFilledViolet, "textures/green_filled_violet.png");

	//Indigos
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoStrokeRed, "textures/indigo_stroke_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoStrokeBlue, "textures/indigo_stroke_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoStrokeGreen, "textures/indigo_stroke_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoStrokeIndigo, "textures/indigo_stroke_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoStrokeOrange, "textures/indigo_stroke_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoStrokeYellow, "textures/indigo_stroke_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoStrokeViolet, "textures/indigo_stroke_violet.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoFilledRed, "textures/indigo_filled_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoFilledBlue, "textures/indigo_filled_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoFilledGreen, "textures/indigo_filled_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoFilledIndigo, "textures/indigo_filled_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoFilledOrange, "textures/indigo_filled_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoFilledYellow, "textures/indigo_filled_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_IndigoFilledViolet, "textures/indigo_filled_violet.png");
		
	//Oranges
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeStrokeRed, "textures/orange_stroke_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeStrokeBlue, "textures/orange_stroke_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeStrokeGreen, "textures/orange_stroke_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeStrokeIndigo, "textures/orange_stroke_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeStrokeOrange, "textures/orange_stroke_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeStrokeYellow, "textures/orange_stroke_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeStrokeViolet, "textures/orange_stroke_violet.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeFilledRed, "textures/orange_filled_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeFilledBlue, "textures/orange_filled_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeFilledGreen, "textures/orange_filled_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeFilledIndigo, "textures/orange_filled_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeFilledOrange, "textures/orange_filled_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeFilledYellow, "textures/orange_filled_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_OrangeFilledViolet, "textures/orange_filled_violet.png");

	//Yellows
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowStrokeRed, "textures/yellow_stroke_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowStrokeBlue, "textures/yellow_stroke_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowStrokeGreen, "textures/yellow_stroke_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowStrokeIndigo, "textures/yellow_stroke_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowStrokeOrange, "textures/yellow_stroke_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowStrokeYellow, "textures/yellow_stroke_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowStrokeViolet, "textures/yellow_stroke_violet.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowFilledRed, "textures/yellow_filled_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowFilledBlue, "textures/yellow_filled_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowFilledGreen, "textures/yellow_filled_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowFilledIndigo, "textures/yellow_filled_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowFilledOrange, "textures/yellow_filled_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowFilledYellow, "textures/yellow_filled_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_YellowFilledViolet, "textures/yellow_filled_violet.png");

	//Violets
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletStrokeRed, "textures/violet_stroke_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletStrokeBlue, "textures/violet_stroke_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletStrokeGreen, "textures/violet_stroke_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletStrokeIndigo, "textures/violet_stroke_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletStrokeOrange, "textures/violet_stroke_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletStrokeYellow, "textures/violet_stroke_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletStrokeViolet, "textures/violet_stroke_violet.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletFilledRed, "textures/violet_filled_red.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletFilledBlue, "textures/violet_filled_blue.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletFilledGreen, "textures/violet_filled_green.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletFilledIndigo, "textures/violet_filled_indigo.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletFilledOrange, "textures/violet_filled_orange.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletFilledYellow, "textures/violet_filled_yellow.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_VioletFilledViolet, "textures/violet_filled_violet.png");
		
	//Paints
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintRed_1, "textures/paint_red_1.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintRed_2, "textures/paint_red_2.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintBlue_1, "textures/paint_blue_1.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintBlue_2, "textures/paint_blue_2.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintGreen_1, "textures/paint_green_1.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintGreen_2, "textures/paint_green_2.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintIndigo_1, "textures/paint_indigo_1.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintIndigo_2, "textures/paint_indigo_2.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintOrange_1, "textures/paint_orange_1.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintOrange_2, "textures/paint_orange_2.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintYellow_1, "textures/paint_yellow_1.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintYellow_2, "textures/paint_yellow_2.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintViolet_1, "textures/paint_violet_1.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_PaintViolet_2, "textures/paint_violet_2.png");

	//Fonts
	g_pResourceManager->RegisterFont((uint)kGameFonts_BestScore, "fonts/impact18.gxfont");

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

	//if (s3eFlurryAvailable())
	//	s3eFlurryEndSession();

	if (g_pFacebookManager != 0)
		delete g_pFacebookManager;

	delete g_pGameCenterManager;
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
	if (Gameplay::s_isShowingTutorial)
		return 1;

	Gameplay::s_paused = true;
	return 1;
}