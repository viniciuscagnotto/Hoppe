#include "header.h"


Game::Game(){
	Init();
}

Game::~Game(){

}

void Game::Init(){
	Iw2DInit();
	LoadResources();
	g_pSaveDataManager = new SaveDataManager();
	g_pTweener = new CTweenManager();
	g_pInput = new InputManager();
	g_pAudio = new AudioManager();
	g_pSpriteManager = new SpriteManager();
	g_pSceneManager = new SceneManager();

	if (s3eFlurryAvailable())
		s3eFlurryStartSession(FLURRY_API_KEY);

	g_pSceneManager->Resume();
}

void Game::LoadResources(){
	g_pResourceManager = new ResourceManager();
	
	//Graphics
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Button_StartGame, "textures/start_game.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlackCircle, "textures/black_circle.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_BlackSquare, "textures/black_square.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_WhiteCircle, "textures/white_circle.png");
	g_pResourceManager->RegisterGraphic((uint)kGameGraphics_Entity_WhiteSquare, "textures/white_square.png");

	//Atlases
	

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

		Iw2DSurfaceClear(0xff666666);
		g_pSceneManager->Render();
		Iw2DSurfaceShow();

		int yield = (int)(FRAME_TIME * 1000 - (s3eTimerGetMs() - newTime));
		if (yield < 0)
			yield = 0;
		s3eDeviceYield(yield);
	}
}

void Game::Cleanup(){
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
}