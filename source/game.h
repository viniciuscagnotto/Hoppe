#ifndef __GAME_H__
#define __GAME_H__

#define TOP_ADS_HEIGHT 13
#define FRAME_TIME  (30.0f / 1000.0f)
#define SCALE_BASE 640
//#define FLURRY_API_KEY "WQFTM6SVNXKJ7958HXNP"

class Game
{
public:
	static float s_scaleFactor;
	
	enum EGameGraphics{
		//Atlases - ALWAYS FIRST
		
		//Backgrounds
		kGameGraphics_Background_Main = 0,

		//Logo
		kGameGraphics_Logo_Main,
		
		//Tutorial
		kGameGraphics_Tutorial_Main,
		kGameGraphics_Tutorial_Arrow,

		//Pause
		kGameGraphics_Pause_Main,
		kGameGraphics_Pause_Sound,
		kGameGraphics_Pause_On,
		kGameGraphics_Pause_Off,
		kGameGraphics_Pause_Off_Text,
		kGameGraphics_Pause_On_Text,


		//Buttons
		kGameGraphics_Button_StartGame,
		kGameGraphics_Button_Back,
		kGameGraphics_Button_Settings,
		kGameGraphics_Button_Exit,
		kGameGraphics_Button_Resume,
		kGameGraphics_Button_Pause,
		kGameGraphics_Button_MainMenu,
		kGameGraphics_Button_PlayAgain,
		kGameGraphics_Button_Facebook,

		//Titles
		kGameGraphics_Title_Options,
		kGameGraphics_Title_BestScore,
		kGameGraphics_Title_YourScore,

		//Options
		kGameGraphics_Options_Sound,
		kGameGraphics_Options_Tutorial,
		kGameGraphics_Options_On,
		kGameGraphics_Options_Off,

		//Reds
		kGameGraphics_Entity_RedStrokeRed,
		kGameGraphics_Entity_RedStrokeBlue,
		kGameGraphics_Entity_RedStrokeGreen,
		kGameGraphics_Entity_RedStrokeIndigo,
		kGameGraphics_Entity_RedStrokeOrange,
		kGameGraphics_Entity_RedStrokeYellow,
		kGameGraphics_Entity_RedStrokeViolet,
		kGameGraphics_Entity_RedFilledRed,
		kGameGraphics_Entity_RedFilledBlue,
		kGameGraphics_Entity_RedFilledGreen,
		kGameGraphics_Entity_RedFilledIndigo,
		kGameGraphics_Entity_RedFilledOrange,
		kGameGraphics_Entity_RedFilledYellow,
		kGameGraphics_Entity_RedFilledViolet,

		//Blues
		kGameGraphics_Entity_BlueStrokeRed,
		kGameGraphics_Entity_BlueStrokeBlue,
		kGameGraphics_Entity_BlueStrokeGreen,
		kGameGraphics_Entity_BlueStrokeIndigo,
		kGameGraphics_Entity_BlueStrokeOrange,
		kGameGraphics_Entity_BlueStrokeYellow,
		kGameGraphics_Entity_BlueStrokeViolet,
		kGameGraphics_Entity_BlueFilledRed,
		kGameGraphics_Entity_BlueFilledBlue,
		kGameGraphics_Entity_BlueFilledGreen,
		kGameGraphics_Entity_BlueFilledIndigo,
		kGameGraphics_Entity_BlueFilledOrange,
		kGameGraphics_Entity_BlueFilledYellow,
		kGameGraphics_Entity_BlueFilledViolet,

		//Greens
		kGameGraphics_Entity_GreenStrokeRed,
		kGameGraphics_Entity_GreenStrokeBlue,
		kGameGraphics_Entity_GreenStrokeGreen,
		kGameGraphics_Entity_GreenStrokeIndigo,
		kGameGraphics_Entity_GreenStrokeOrange,
		kGameGraphics_Entity_GreenStrokeYellow,
		kGameGraphics_Entity_GreenStrokeViolet,
		kGameGraphics_Entity_GreenFilledRed,
		kGameGraphics_Entity_GreenFilledBlue,
		kGameGraphics_Entity_GreenFilledGreen,
		kGameGraphics_Entity_GreenFilledIndigo,
		kGameGraphics_Entity_GreenFilledOrange,
		kGameGraphics_Entity_GreenFilledYellow,
		kGameGraphics_Entity_GreenFilledViolet,

		//Indigos
		kGameGraphics_Entity_IndigoStrokeRed,
		kGameGraphics_Entity_IndigoStrokeBlue,
		kGameGraphics_Entity_IndigoStrokeGreen,
		kGameGraphics_Entity_IndigoStrokeIndigo,
		kGameGraphics_Entity_IndigoStrokeOrange,
		kGameGraphics_Entity_IndigoStrokeYellow,
		kGameGraphics_Entity_IndigoStrokeViolet,
		kGameGraphics_Entity_IndigoFilledRed,
		kGameGraphics_Entity_IndigoFilledBlue,
		kGameGraphics_Entity_IndigoFilledGreen,
		kGameGraphics_Entity_IndigoFilledIndigo,
		kGameGraphics_Entity_IndigoFilledOrange,
		kGameGraphics_Entity_IndigoFilledYellow,
		kGameGraphics_Entity_IndigoFilledViolet,

		//Oranges
		kGameGraphics_Entity_OrangeStrokeRed,
		kGameGraphics_Entity_OrangeStrokeBlue,
		kGameGraphics_Entity_OrangeStrokeGreen,
		kGameGraphics_Entity_OrangeStrokeIndigo,
		kGameGraphics_Entity_OrangeStrokeOrange,
		kGameGraphics_Entity_OrangeStrokeYellow,
		kGameGraphics_Entity_OrangeStrokeViolet,
		kGameGraphics_Entity_OrangeFilledRed,
		kGameGraphics_Entity_OrangeFilledBlue,
		kGameGraphics_Entity_OrangeFilledGreen,
		kGameGraphics_Entity_OrangeFilledIndigo,
		kGameGraphics_Entity_OrangeFilledOrange,
		kGameGraphics_Entity_OrangeFilledYellow,
		kGameGraphics_Entity_OrangeFilledViolet,

		//Yellows
		kGameGraphics_Entity_YellowStrokeRed,
		kGameGraphics_Entity_YellowStrokeBlue,
		kGameGraphics_Entity_YellowStrokeGreen,
		kGameGraphics_Entity_YellowStrokeIndigo,
		kGameGraphics_Entity_YellowStrokeOrange,
		kGameGraphics_Entity_YellowStrokeYellow,
		kGameGraphics_Entity_YellowStrokeViolet,
		kGameGraphics_Entity_YellowFilledRed,
		kGameGraphics_Entity_YellowFilledBlue,
		kGameGraphics_Entity_YellowFilledGreen,
		kGameGraphics_Entity_YellowFilledIndigo,
		kGameGraphics_Entity_YellowFilledOrange,
		kGameGraphics_Entity_YellowFilledYellow,
		kGameGraphics_Entity_YellowFilledViolet,

		//Violets
		kGameGraphics_Entity_VioletStrokeRed,
		kGameGraphics_Entity_VioletStrokeBlue,
		kGameGraphics_Entity_VioletStrokeGreen,
		kGameGraphics_Entity_VioletStrokeIndigo,
		kGameGraphics_Entity_VioletStrokeOrange,
		kGameGraphics_Entity_VioletStrokeYellow,
		kGameGraphics_Entity_VioletStrokeViolet,
		kGameGraphics_Entity_VioletFilledRed,
		kGameGraphics_Entity_VioletFilledBlue,
		kGameGraphics_Entity_VioletFilledGreen,
		kGameGraphics_Entity_VioletFilledIndigo,
		kGameGraphics_Entity_VioletFilledOrange,
		kGameGraphics_Entity_VioletFilledYellow,
		kGameGraphics_Entity_VioletFilledViolet,

		//Paints
		kGameGraphics_Entity_PaintRed_1,
		kGameGraphics_Entity_PaintRed_2,
		kGameGraphics_Entity_PaintBlue_1,
		kGameGraphics_Entity_PaintBlue_2,
		kGameGraphics_Entity_PaintGreen_1,
		kGameGraphics_Entity_PaintGreen_2,
		kGameGraphics_Entity_PaintIndigo_1,
		kGameGraphics_Entity_PaintIndigo_2,
		kGameGraphics_Entity_PaintOrange_1,
		kGameGraphics_Entity_PaintOrange_2,
		kGameGraphics_Entity_PaintYellow_1,
		kGameGraphics_Entity_PaintYellow_2,
		kGameGraphics_Entity_PaintViolet_1,
		kGameGraphics_Entity_PaintViolet_2,

		kGameGraphics_Count
	};

	enum EGameFonts{
		kGameFonts_BestScore = 0,

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


