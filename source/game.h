#ifndef __GAME_H__
#define __GAME_H__

#define TOP_ADS_HEIGHT 13
#define FRAME_TIME  (30.0f / 1000.0f)
#define FLURRY_API_KEY "WQFTM6SVNXKJ7958HXNP"

class Game
{
public:
	static int s_gameSpacement;
	static bool s_is2X;
	static bool s_isIphone5;
	
	enum EGameGraphics{
		//Atlases - ALWAYS FIRST
		
		//Backgrounds
		kGameGraphics_Background_Main = 0,

		//Logo
		kGameGraphics_Logo_Main,
		
		//Tutorial
		kGameGraphics_Tutorial_Main,

		//Pause
		kGameGraphics_Pause_Main,
		kGameGraphics_Pause_Sound,
		kGameGraphics_Pause_On,
		kGameGraphics_Pause_Off,


		//Buttons
		kGameGraphics_Button_StartGame,
		kGameGraphics_Button_Back,
		kGameGraphics_Button_Settings,
		kGameGraphics_Button_Exit,
		kGameGraphics_Button_Resume,
		kGameGraphics_Button_Pause,
		kGameGraphics_Button_MainMenu,
		kGameGraphics_Button_PlayAgain,

		//Titles
		kGameGraphics_Title_Options,
		kGameGraphics_Title_BestScore,
		kGameGraphics_Title_YourScore,

		//Options
		kGameGraphics_Options_Sound,
		kGameGraphics_Options_On,
		kGameGraphics_Options_Off,

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

	static int32 PauseCB(void* pSystemData, void* pUuserData);
};

#endif  // __GAME_H__


