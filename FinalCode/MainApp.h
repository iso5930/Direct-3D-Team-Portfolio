#pragma once

class CMainApp
{
public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	CMainApp();
	~CMainApp();
};
