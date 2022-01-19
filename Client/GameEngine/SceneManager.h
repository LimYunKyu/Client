#pragma once


enum
{
	MAX_LAYER = 32
};
class SceneManager
{

	DECLARE_SINGLE(SceneManager)



public:
	void Update();
	void Render();
	void SetScene(shared_ptr<class Scene> scene);
	shared_ptr<class Scene> GetCurrentScene() { return mCurrentScene; }

	void SetLayerName(UINT8 index, const wstring& name);
	const wstring& IndexToLayerName(UINT8 index) { return _layerNames[index]; }
	UINT8 LayerNameToIndex(const wstring& name);

private:
	shared_ptr<class Scene> mCurrentScene;

	array<wstring, MAX_LAYER> _layerNames;
	map<wstring, UINT8> _layerIndex;

};

