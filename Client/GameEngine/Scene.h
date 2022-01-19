#pragma once
class Shader;
class Scene
{
public:
	void Initialize();
	void Update();
	void Render();
	virtual void LoadObject();
	void PushLightData();

public:
	void AddGameObject(shared_ptr<class GameObject> gameobject) { mGameObjectVector.push_back(gameobject); }
	vector<shared_ptr<class GameObject>> GetGameObjectVector() { return mGameObjectVector; }


protected:
	vector<shared_ptr<class GameObject>> mGameObjectVector;
	vector<shared_ptr<class GameObject>> mLightVector;


	LightParams lightparams = {};
	shared_ptr<Shader> mlightShader;
};

