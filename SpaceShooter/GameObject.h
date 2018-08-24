#pragma once


class GameObject
{



public:
	GameObject();
	~GameObject() {};

	virtual void Update(float dt) {};

};

class PlayerObject : public GameObject
{

	PlayerObject();
	~PlayerObject

};