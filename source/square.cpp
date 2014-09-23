#include "header.h"

//- Square ------------------------------------------------------------
Square::Square(GameObject::EGameObjectColor color) :GameObject(kGameObjectType_Square)
{
	m_color = color;
	Init();
}

Square::~Square()
{
	Cleanup();
}

void Square::Init()
{
	Game::EGameGraphics gameGraphics = Game::kGameGraphics_Entity_BlackSquare;
	if (m_color == kGameObjectColor_White)
		gameGraphics = Game::kGameGraphics_Entity_WhiteSquare;

	GameObject::Init(gameGraphics, 0, 0);

	for (uint i = 0; i < s_kMaxCircles; i++)
		m_circles[i] = new Circle(m_color);
}

void Square::Cleanup()
{
	for (uint i = 0; i < s_kMaxCircles; i++){
		delete m_circles[i]; m_circles[i] = 0;
	}

	GameObject::Cleanup();
}

void Square::Update(float deltaTime)
{
	GameObject::Update();

	Gameplay *pGameplay = (Gameplay *)g_pSceneManager->Find(Scene::kScene_Gameplay);
	if (!pGameplay)
		return;

	for (uint i = 0; i < s_kMaxCircles; i++){
		if (!m_circles[i]->IsActive())
			continue;

		if (m_circles[i]->IsFading()){
			m_circles[i]->AddAlpha(-0.08f);
			if (m_circles[i]->GetAlpha() <= 0.0f){
				m_circles[i]->Reset();
				m_circles[i]->GetSprite()->m_X = m_circleInitialPos;
				m_circles[i]->SetScale(1.0f, 1.0f);
			}
			return;
		}

		if (m_circles[i]->IsTapped()){
			if (m_circles[i]->GetColor() == m_circles[i]->GetReceiver()->GetFrontSquare()->GetColor()){
				EndGame();
				//g_pAudio->PlaySound("audio/explosion.wav");
				g_pTweener->Tween(2.0f, FLOAT, &m_circles[i]->GetSprite()->m_ScaleX, 1.7f,
										FLOAT, &m_circles[i]->GetSprite()->m_ScaleY, 1.7f,
										ONCOMPLETE, Square::OnGameOver, END);
				return;
			}else{
				if (m_circles[i]->GetAlpha() == 1.0f){
					g_pAudio->PlaySound("audio/tap.wav");
					Gameplay::s_correctTaps++;
					
					float fullDistance = floorf(fabsf(GetSprite()->m_X - m_circles[i]->GetReceiver()->GetFrontSquare()->GetSprite()->m_X));
					float circleDistance = floorf(fabsf(m_circles[i]->GetSprite()->m_X - m_circles[i]->GetReceiver()->GetFrontSquare()->GetSprite()->m_X));
					int points = (int)floorf(circleDistance / fullDistance*POINTS_PER_TAP);
					Gameplay::s_actualScore += points;
					if (Gameplay::s_actualScore > MAX_SCORE)
						Gameplay::s_actualScore = MAX_SCORE;
					IwTrace(Square, ("POINTS: %d", Gameplay::s_actualScore));

					pGameplay->CheckNextLevel();
					pGameplay->SetAllCirclesToFade();
				}
				
				m_circles[i]->AddAlpha(-0.08f);
				
				float circleScale = m_circles[i]->GetSprite()->m_ScaleX;
				//m_circles[i]->SetScale(circleScale + 0.05f, circleScale + 0.05f);
				
				if (m_circles[i]->GetAlpha() <= 0.0f){
					m_circles[i]->Reset();
					m_circles[i]->GetSprite()->m_X = m_circleInitialPos;
					m_circles[i]->SetScale(1.0f, 1.0f);
					pGameplay->RandomSwitch();
				}
			}

			continue;
		}

		m_circles[i]->Update(deltaTime);
		bool reachedDestination = false;
		Square *pFrontSquare = m_circles[i]->GetReceiver()->GetFrontSquare();
		if (m_circles[i]->GetSpeed() > 0.0f){
			if (m_circles[i]->GetColor() == pFrontSquare->GetColor()){
				if (m_circles[i]->GetSprite()->m_X >= pFrontSquare->GetSprite()->m_X - pFrontSquare->GetSprite()->m_W * 0.25f)
					reachedDestination = true;
			}
			else{
				if (m_circles[i]->GetSprite()->m_X >= pFrontSquare->GetSprite()->m_X - pFrontSquare->GetWidth(true)){
					EndGame();
					//g_pAudio->PlaySound("audio/explosion.wav");
					g_pTweener->Tween(2.0f, FLOAT, &m_circles[i]->GetSprite()->m_ScaleX, 1.7f,
						FLOAT, &m_circles[i]->GetSprite()->m_ScaleY, 1.7f,
						ONCOMPLETE, Square::OnGameOver, END);
					return;
				}
			}
		}
		else{
			if (m_circles[i]->GetColor() == pFrontSquare->GetColor()){
				if (m_circles[i]->GetSprite()->m_X <= pFrontSquare->GetSprite()->m_X + pFrontSquare->GetSprite()->m_W * 0.25f)
					reachedDestination = true;
			}
			else{
				if (m_circles[i]->GetSprite()->m_X <= pFrontSquare->GetSprite()->m_X + pFrontSquare->GetWidth(true)){
					EndGame();
					//g_pAudio->PlaySound("audio/explosion.wav");
					g_pTweener->Tween(2.0f, FLOAT, &m_circles[i]->GetSprite()->m_ScaleX, 1.7f,
						FLOAT, &m_circles[i]->GetSprite()->m_ScaleY, 1.7f,
						ONCOMPLETE, Square::OnGameOver, END);
					return;
				}
			}
		}

		if (reachedDestination){
			m_circles[i]->Reset();
			m_circles[i]->GetSprite()->m_X = m_circleInitialPos;
			m_circles[i]->SetScale(1.0f, 1.0f);
		}
	}
}

void Square::SetReceiver(SquareObject* pReceiver){
	for (uint i = 0; i < s_kMaxCircles; i++){
		m_circles[i]->SetReceiver(pReceiver);
	}
}

void Square::AddCirclesTo(CNode *pContainer, float posX){
	m_circleInitialPos = posX;
	for (uint i = 0; i < s_kMaxCircles; i++){
		m_circles[i]->SetPosition(posX, GetSprite()->m_Y);
		m_circles[i]->SetScale(1.0f, 1.0f);
		m_circles[i]->Reset();
		m_circles[i]->AddTo(pContainer);
	}
}

void Square::RemoveCirclesFromParent(){
	for (uint i = 0; i < s_kMaxCircles; i++){
		m_circles[i]->Reset();
		m_circles[i]->RemoveFromParent();
	}
}

void Square::SetAllCirclesToFade(){
	for (uint i = 0; i < s_kMaxCircles; i++){
		if (m_circles[i]->IsActive() && !m_circles[i]->IsTapped())
			m_circles[i]->SetFading(true);
	}
}

void Square::Shoot(float speed){	
	for (uint i = 0; i < s_kMaxCircles; i++){
		if (!m_circles[i]->IsActive()){
			g_pAudio->PlaySound("audio/shoot.wav");
			m_circles[i]->SetSpeed(speed);
			m_circles[i]->SetIsActive(true);
			m_circles[i]->SetTapped(false);
			return;
		}
	}
}

void Square::CheckTap(float x, float y){
	float extraWidth = IwGxGetDeviceWidth();//20.0f;
	float extraHeight = 15.0f;
	if (Game::s_is2X){
		//extraWidth = 40.0f;
		extraHeight = 30.0f;
	}	

	for (uint i = 0; i < s_kMaxCircles; i++){
		if (m_circles[i]->IsActive() && !m_circles[i]->IsTapped()){
			if (m_circles[i]->GetSprite()->HitTest(x, y, extraWidth, extraHeight)){
				m_circles[i]->SetTapped(true);
				return;
			}
		}
	}
}

bool Square::HasIncomingCircle(bool isLeft){
	for (uint i = 0; i < s_kMaxCircles; i++){
		if (m_circles[i]->IsActive() && !m_circles[i]->IsTapped()){
			if (isLeft){
				if (m_circles[i]->GetSprite()->m_X > IwGxGetScreenWidth() * 0.5f)
					return true;
			}else{
				if (m_circles[i]->GetSprite()->m_X < IwGxGetScreenWidth() * 0.5f)
					return true;
			}
		}
	}

	return false;
}

void Square::EndGame(){
	if (Gameplay::s_actualScore > g_pSaveData->m_saveData.topScore){
		g_pSaveData->m_saveData.topScore = Gameplay::s_actualScore;
		g_pSaveData->Save();

		//Send to Game Center

	}

	Gameplay::s_paused = false;
	Gameplay::s_gameOver = true;
}

void Square::OnGameOver(CTween *pTween){
	((Gameplay *)g_pSceneManager->Find(Scene::kScene_Gameplay))->SwitchTo(Scene::kScene_GameOver);
}

//- Square Object ------------------------------------------------------------
SquareObject::SquareObject(bool leftSide):m_front(GameObject::kGameObjectColor_Black),
m_isShooter(false),
m_isSwitching(false),
m_isSlidingIn(false),
m_frontPosX(0.0f),
m_backPosX(0.0f),
m_switchSpeed(0.0f),
m_shootSpeed(0.0f)
{
	m_pWhite = new Square(GameObject::kGameObjectColor_White);
	m_pBlack = new Square(GameObject::kGameObjectColor_Black);
	m_left = leftSide;
}

SquareObject::~SquareObject(){
	delete m_pWhite; m_pWhite = 0;
	delete m_pBlack; m_pBlack = 0;
}

void SquareObject::SetReceiver(SquareObject *pReceiver){
	m_pWhite->SetReceiver(pReceiver);
	m_pBlack->SetReceiver(pReceiver);
}

void SquareObject::AddTo(CNode *pParent){
	if (!m_pWhite || !m_pBlack)
		return;

	m_pWhite->AddTo(pParent);
	m_pBlack->AddTo(pParent);
}

void SquareObject::RemoveFromParent(){
	if (!m_pWhite || !m_pBlack)
		return;

	m_pWhite->RemoveCirclesFromParent();
	m_pWhite->RemoveFromParent();
	
	m_pBlack->RemoveCirclesFromParent();
	m_pBlack->RemoveFromParent();
}

void SquareObject::SetScale(float scaleX, float scaleY){
	m_pBlack->SetScale(scaleX, scaleY);
	m_pWhite->SetScale(scaleX, scaleY);
}

void SquareObject::SetPosition(float posX, float posY, bool hidden){
	m_frontPosX = posX;
	m_backPosX = posX - m_pBlack->GetWidth();
	if (!m_left)
		m_backPosX = posX + m_pBlack->GetWidth();

	if (hidden){
		m_pWhite->SetPosition(m_backPosX, posY);
		m_pBlack->SetPosition(m_backPosX, posY);
	}else{
		m_pWhite->SetPosition(m_frontPosX, posY);
		if (m_front == GameObject::kGameObjectColor_Black){
			m_pBlack->SetPosition(m_frontPosX, posY);
		}
		else{
			m_pBlack->SetPosition(m_backPosX, posY);
		}
	}
}

float SquareObject::GetWidth(bool half){
	return m_pBlack->GetWidth(half);
}

float SquareObject::GetHeight(bool half){
	return m_pBlack->GetHeight(half);
}

void SquareObject::SetInitialParams(bool defineFront, GameObject::EGameObjectColor front){
	m_front = front;
	if (!defineFront)
		m_front = (GameObject::EGameObjectColor)L_RandomInt(0, 1);
	
	m_switchSpeed = (Game::s_is2X ? 20.0f : 10.0f);
	m_isSwitching = false;
	m_isSlidingIn = false;
}

void SquareObject::Update(float deltaTime){
	if (m_isSlidingIn){
		SlideIn();
	}

	if (m_isSwitching){
		Switch();
	}

	m_pBlack->Update(deltaTime);
	m_pWhite->Update(deltaTime);
}

void SquareObject::SetupCircles(CNode *pContainer){
	float circlePositionX = m_frontPosX; //+ m_pBlack->GetWidth() * 0.25f;
	if (!m_left)
		circlePositionX = m_frontPosX; // - m_pBlack->GetWidth() * 0.25f;

	m_pWhite->AddCirclesTo(pContainer, circlePositionX);
	m_pBlack->AddCirclesTo(pContainer, circlePositionX);
}

void SquareObject::SetAllCirclesToFade(){
	m_pWhite->SetAllCirclesToFade();
	m_pBlack->SetAllCirclesToFade();
}

void SquareObject::SlideIn(){
	if (m_pWhite->GetSprite()->m_X != m_frontPosX){
		if (m_left){
			m_pWhite->GetSprite()->m_X += m_switchSpeed;
			if (m_pWhite->GetSprite()->m_X >= m_frontPosX)
				m_pWhite->GetSprite()->m_X = m_frontPosX;
		}
		else{
			m_pWhite->GetSprite()->m_X -= m_switchSpeed;
			if (m_pWhite->GetSprite()->m_X <= m_frontPosX)
				m_pWhite->GetSprite()->m_X = m_frontPosX;
		}

		return;
	}

	m_isSlidingIn = false;
}

void SquareObject::Switch(){
	if (m_front == GameObject::kGameObjectColor_Black){
		if (m_pBlack->GetSprite()->m_X != m_backPosX){
			if (m_left){
				m_pBlack->GetSprite()->m_X -= m_switchSpeed;
				if (m_pBlack->GetSprite()->m_X <= m_backPosX)
					m_pBlack->GetSprite()->m_X = m_backPosX;
			}
			else{
				m_pBlack->GetSprite()->m_X += m_switchSpeed;
				if (m_pBlack->GetSprite()->m_X >= m_backPosX)
					m_pBlack->GetSprite()->m_X = m_backPosX;
			}

			return;
		}
	}else{
		if (m_pBlack->GetSprite()->m_X != m_frontPosX){
			if (m_left){
				m_pBlack->GetSprite()->m_X += m_switchSpeed;
				if (m_pBlack->GetSprite()->m_X >= m_frontPosX)
					m_pBlack->GetSprite()->m_X = m_frontPosX;
			}
			else{
				m_pBlack->GetSprite()->m_X -= m_switchSpeed;
				if (m_pBlack->GetSprite()->m_X <= m_frontPosX)
					m_pBlack->GetSprite()->m_X = m_frontPosX;
			}

			return;
		}
	}

	m_isSwitching = false;
	m_front = (m_front == GameObject::kGameObjectColor_Black ? GameObject::kGameObjectColor_White : GameObject::kGameObjectColor_Black);
}

void SquareObject::Shoot(float speed, bool front){
	if (front){
		GetFrontSquare()->Shoot(speed);
	}else{
		GetBackSquare()->Shoot(speed);
	}
}

Square *SquareObject::GetFrontSquare(){
	if (m_front == GameObject::kGameObjectColor_Black)
		return m_pBlack;
	return m_pWhite;
}

Square *SquareObject::GetBackSquare(){
	if (m_front == GameObject::kGameObjectColor_Black)
		return m_pWhite;
	return m_pBlack;
}

void SquareObject::CheckTap(float x, float y){
	m_pBlack->CheckTap(x, y);
	m_pWhite->CheckTap(x, y);
}

void SquareObject::SwitchFront(){
	m_front = m_front == GameObject::kGameObjectColor_Black ? GameObject::kGameObjectColor_White : GameObject::kGameObjectColor_Black;
}

bool SquareObject::CanSwitch(SquareObject *pShooter){
	if (pShooter->GetFrontSquare()->HasIncomingCircle(pShooter->IsLeft()))
		return false;

	return true;
}