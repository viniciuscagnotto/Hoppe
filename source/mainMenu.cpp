#include "header.h"

MainMenu::MainMenu() : Scene(kScene_MainMenu),
m_pStartGame(0),
m_pFazendeiroRun(0),
m_pGalinha(0)
{

}


MainMenu::~MainMenu()
{
	Cleanup();
}

void MainMenu::Init()
{
	Scene::Init();

	//Start Game Button
	m_pStartGame = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_StartGame);
	m_pStartGame->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pStartGame->m_Y = IwGxGetScreenHeight() * 0.5f;
	AddChild(m_pStartGame);

	/////////- ANIMATION TEST----------------------
	//Fazendeiro Run 
	m_pFazendeiroRun = g_pSpriteManager->CreateSpriteObject();
	m_pFazendeiroRun->m_X = IwGxGetScreenWidth() * 0.2f;
	m_pFazendeiroRun->m_Y = IwGxGetScreenHeight() * 0.2f;

	m_pFazendeiroRun->AddAnimation(0, Game::kGameAtlases_FazendeiroRun, 0.4f, 99);
	m_pFazendeiroRun->RunAnimation(0);
	AddChild(m_pFazendeiroRun);

	//Galinha
	m_pGalinha = new Galinha();
	m_pGalinha->AddTo(this);
}

void MainMenu::Cleanup()
{
	SafeDeleteObject(m_pStartGame);
	m_pStartGame = 0;

	SafeDeleteObject(m_pFazendeiroRun);
	m_pFazendeiroRun = 0;

	delete m_pGalinha;
	m_pGalinha = 0;

	Scene::Cleanup();
}

void MainMenu::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

    Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();
	
}

void MainMenu::Render()
{
    Scene::Render();
	if (!CheckCurrent())
		return;
}

void MainMenu::HandleTouch()
{
	Scene::HandleTouch();

	if (m_pStartGame){
		if (m_pStartGame->HitTest(g_pInput->m_x, g_pInput->m_y)){
			g_pAudio->PlaySound("audio/button.wav");
			SwitchTo(kScene_Gameplay);
		}
	}
}