#ifndef __CUSTOM_ATLAS_H__
#define __CUSTOM_ATLAS_H__

class CustomAtlas : public CAtlas{
public:
	CustomAtlas() {};
	CustomAtlas(CIw2DImage* spritesheet){ SetImage(spritesheet); };

	void SetImage(CIw2DImage* spritesheet) {m_Image = spritesheet; };
	void SetFrameSize(int width, int height) { m_FrameWidth = width; m_FrameHeight = height; };
	void AddFrame(int16 x, int16 y, int16 width, int16 height) { m_Frames.push_back(CIwRect(x, y, width, height)); };
};

#endif //__CUSTOM_ATLAS_H__