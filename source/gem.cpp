#include "include.h"

int Gem::gemFallSpeed = 500;
int Gem::gemDestroyedScore = 10;

Gem::~Gem()
{
}

void Gem::setType(int type)
{
    Type = type;
    SetAtlas(g_pResources->getGemAtlas(type));
    SetAnimRepeat(1);
}

void Gem::init(float x, float y, CAtlas* atlas)
{
    m_X = x;
    m_Y = y;
    SetAtlas(atlas);
    SetAnimDuration(2);
    SetAnimRepeat(1);
}

// Explode gem
void Gem::explode()
{
    // Fade the gem out
    Game* game = (Game*)g_pSceneManager->Find("game");
    game->GetTweener().Tween(0.2f,
                                FLOAT, &m_Alpha, 0.0f,
                                EASING, Ease::sineIn,
                                END);

    // Remove the gem from play
    game->removeGem(this);

    // Update round score
    game->addToRoundScore(gemDestroyedScore, Type);

    // Create an explosion
    g_pExplosionManager->Create(m_X + (m_W / 2) * game->getGraphicsScale(), m_Y + (m_W / 2) * game->getGraphicsScale());
}



