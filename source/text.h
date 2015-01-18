#ifndef __TEXT_H__
#define __TEXT_H__

class Text : public GameObject
{
public:


private:


public:
	Text(ETextType textType, EColor textColor, EColor color);
	~Text();

	void Init();
	void Cleanup();
	void Update(float deltaTime);

	Game::EGameGraphics GetStrokeText();
	Game::EGameGraphics GetFilledText();
};

#endif  // __TEXT_H__

