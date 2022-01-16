#pragma once
class Scene
{
public:
	void Initialize();
	void Update();
	void Render();
	virtual void LoadObject();

public:
	void AddGameObject(shared_ptr<class GameObject> gameobject) { mGameObjectVector.push_back(gameobject); }

protected:
	vector<shared_ptr<class GameObject>> mGameObjectVector;
};

