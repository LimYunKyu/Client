#pragma once


class SceneManager
{

	DECLARE_SINGLE(SceneManager)



public:
	void Update();
	void Render();
	void SetScene(shared_ptr<class Scene> scene);
	shared_ptr<class Scene> GetCurrentScene() { return mCurrentScene; }
private:
	shared_ptr<class Scene> mCurrentScene;
};

