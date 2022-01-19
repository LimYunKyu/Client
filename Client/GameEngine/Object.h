#pragma once

enum class OBJECT_TYPE
{
	GAMEOBJECT,
	COMPONENT,
	MATERIAL,
	MESH,
	SHADER,
	TEXTURE,
	NONE,
	END
};

enum
{
	OBJECT_TYPE_COUNT = OBJECT_TYPE::END,

};
class Object
{
public:
	Object(OBJECT_TYPE Type) { mObjectType = Type; }

public:
	virtual void Initialize();
	virtual void LateInitialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();
	virtual void Render();
public:
	OBJECT_TYPE GetObjectType() { return mObjectType; }
	virtual void Load(const wstring& path) {}
	virtual void Save(const wstring& path) {}


	void SetName(const wstring& name) { _name = name; }
	const wstring& GetName() { return _name; }

protected:
	OBJECT_TYPE mObjectType;

	wstring _name;

};

