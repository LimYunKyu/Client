#pragma once
class Scene
{
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0 ;


public:
	void AddGameObject(shared_ptr<class GameObject> gameobject) { mGameObjectVector.push_back(gameobject); }

protected:
	vector<shared_ptr<class GameObject>> mGameObjectVector;
};

