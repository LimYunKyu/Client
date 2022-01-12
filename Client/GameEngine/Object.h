#pragma once

enum class OBJECT_TYPE
{
	GAMEOBJECT,
	COMPONENT,
	MATERIAL,
	MESH,
	SHADER,
	TEXTURE,
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
	virtual void Initialize() = 0;
	virtual void LateInitialize() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
public:
	OBJECT_TYPE GetObjectType() { return mObjectType; }

protected:
	OBJECT_TYPE mObjectType;



};

