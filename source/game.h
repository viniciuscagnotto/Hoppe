#ifndef __GAME_H__
#define __GAME_H__

#define FRAME_TIME  (30.0f / 1000.0f)
#define FLURRY_API_KEY "WQFTM6SVNXKJ7958HXNP"

class Game
{
public:
	enum EGameGraphics{
		//Entities
		kGameGraphics_Entity_Player = 0,

		//Backgrounds
		kGameGraphics_Background_Space,

		//Buttons
		kGameGraphics_Button_StartGame,

		//Atlases
		kGameGraphics_Atlas_FazendeiroRun,
		kGameGraphics_Atlas_Galinha_Run,
		kGameGraphics_Atlas_Galinha_Run_Catarro,
		kGameGraphics_Atlas_Galinha_Damage,
		kGameGraphics_Atlas_Galinha_Apaixonada,

		kGameGraphics_Count
	};

	enum EGameAtlases{
		kGameAtlases_FazendeiroRun = 0,
		kGameAtlases_Galinha_Run,
		kGameAtlases_Galinha_Run_Catarro,
		kGameAtlases_Galinha_Damage,
		kGameAtlases_Galinha_Apaixonada,

		kGameAtlases_Count
	};

	enum EGameFonts{
		kGameFonts_Arial_8 = 0,

		kGameFonts_Count
	};

private:

public:
	Game();
	~Game();

	void Init();
	void LoadResources();
	void Update();
	void Cleanup();
};

#endif  // __GAME_H__

