#ifndef __GAME_H__
#define __GAME_H__

#define FRAME_TIME  (30.0f / 1000.0f)
#define FLURRY_API_KEY "WQFTM6SVNXKJ7958HXNP"

class Game
{
public:
	enum EGameGraphics{
		//Atlases - ALWAYS FIRST
		kGameGraphics_Atlas_FazendeiroRun = 0,
		kGameGraphics_Atlas_Galinha_Run,
		kGameGraphics_Atlas_Galinha_Run_Catarro,
		kGameGraphics_Atlas_Galinha_Damage,
		kGameGraphics_Atlas_Galinha_Apaixonada,

		//Entities
		kGameGraphics_Entity_Player,

		//Backgrounds
		kGameGraphics_Background_Space,

		//Buttons
		kGameGraphics_Button_StartGame,

		kGameGraphics_Count
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

