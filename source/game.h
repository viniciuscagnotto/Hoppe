#ifndef __GAME_H__
#define __GAME_H__

#define FRAME_TIME  (30.0f / 1000.0f)
#define FLURRY_API_KEY "WQFTM6SVNXKJ7958HXNP"

class Game
{
public:
	enum EGameGraphics{
		//Atlases - ALWAYS FIRST
		
		//Backgrounds
		
		//Buttons
		kGameGraphics_Button_StartGame = 0,

		//Entities
		kGameGraphics_Entity_BlackCircle,
		kGameGraphics_Entity_BlackSquare,
		kGameGraphics_Entity_WhiteSquare,
		kGameGraphics_Entity_WhiteCircle,

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

