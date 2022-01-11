#pragma once
class Game
{
public:
	void Initialize(const WindowInfo& winfo);
	void Update();
	void Render();
	void CallScreenResize(const WindowInfo& wInfo);
};

