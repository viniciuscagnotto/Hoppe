#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#define MAX_GEM_TYPES   5

class Resources
{
protected:
    CIw2DImage*     Gems[MAX_GEM_TYPES];
    CIw2DImage*     Grid;
    CIw2DImage*     MenuBG;
    CIw2DImage*     GameBG;
    CIw2DImage*     MenuButton;
    CIw2DImage*     InfoPanel;
    CIw2DImage*     Placard;
    CIw2DImage*     PauseIcon;
    CIw2DImage*     PlayButton;
    CIw2DImage*     Selector;
    CIw2DImage*     Explosion;
    CIw2DImage*     Facebook;
    CIw2DFont*      Font;
    CAtlas*         GemAtlases[MAX_GEM_TYPES];
    CAtlas*         ExplosionAtlas;

public:
    CIw2DImage*     getGem(int index)           { return Gems[index]; }
    CIw2DImage*     getGrid()                   { return Grid; }
    CIw2DImage*     getMenuBG()                 { return MenuBG; }
    CIw2DImage*     getGameBG()                 { return GameBG; }
    CIw2DImage*     getMenuButton()             { return MenuButton; }
    CIw2DImage*     getInfoPanel()              { return InfoPanel; }
    CIw2DImage*     getPlacard()                { return Placard; }
    CIw2DImage*     getPauseIcon()              { return PauseIcon; }
    CIw2DImage*     getPlayButton()             { return PlayButton; }
    CIw2DImage*     getSelector()               { return Selector; }
    CIw2DImage*     getExplosion()              { return Explosion; }
    CIw2DImage*     getFacebook()               { return Facebook; }
    CIw2DFont*      getFont()                   { return Font; }
    CAtlas*         getGemAtlas(int index)      { return GemAtlases[index]; }
    CAtlas*         getExplosionAtlas()         { return ExplosionAtlas; }

public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;

#endif  // __RESOURCES_H__
