#pragma once


#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }


#define DECLARE_SINGLE(type)		\
private:							\
	type() {}						\
	~type() {}						\
public:								\
	static type* GetInstance()		\
	{								\
		static type instance;		\
		return &instance;	}		