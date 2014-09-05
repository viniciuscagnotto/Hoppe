#ifndef __GAME_H__
#define __GAME_H__

#define FRAME_TIME  (30.0f / 1000.0f)
#define FLURRY_API_KEY "WQFTM6SVNXKJ7958HXNP"

class Game
{
public:
	enum EGameGraphics{
		//Atlases - ALWAYS FIRST
		
		//Entities
		
		//Backgrounds
		
		//Buttons
		kGameGraphics_Button_StartGame = 0,

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

