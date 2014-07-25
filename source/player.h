#if !defined(__PLAYER_H__)
#define __PLAYER_H__


class Player : public GameObject
{
public:


private:


public:
	Player();
	~Player();

	void Init();
	void Cleanup();
	void Update();
	void Interact(GameObject* go);
};

#endif  // __PLAYER_H__

