#pragma once

class CLoadMgr
{
public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	// ForBase
	void LoadForBase();
	void UnloadForBase();

	// ForTitleScene
	void LoadForTitleScene();
	void UnloadForTitleScene();

	// ForLobbyScene
	void LoadForLobbyScene();
	void UnloadForLobbyScene();

	// ForPlayScene
	void LoadForPlayScene();
	void UnloadForPlayScene();

	// ForBarbarianMale
	void LoadForBarbarianMale();
	void UnloadForBarbarianMale();

	// ForBarbarianFemale
	void LoadForBarbarianFemale();
	void UnloadForBarbarianFemale();

	// ForDemonHunterMale
	void LoadForDemonHunterMale();
	void UnloadForDemonHunterMale();

	// ForDemonHunterFemale
	void LoadForDemonHunterFemale();
	void UnloadForDemonHunterFemale();

	// ForMonkMale
	void LoadForMonkMale();
	void UnloadForMonkMale();

	// ForMonkFemale
	void LoadForMonkFemale();
	void UnloadForMonkFemale();

	// ForWitchDoctorMale
	void LoadForWitchDoctorMale();
	void UnloadForWitchDoctorMale();

	// ForWitchDoctorFemale
	void LoadForWitchDoctorFemale();
	void UnloadForWitchDoctorFemale();

	// ForWizardMale
	void LoadForWizardMale();
	void UnloadForWizardMale();

	// ForWizardFemale
	void LoadForWizardFemale();
	void UnloadForWizardFemale();

private:
	// Barbarian
	void LoadForBarbarian();
	void UnloadForBarbarian();

	// DemonHunter
	void LoadForDemonHunter();
	void UnloadForDemonHunter();

	// Monk
	void LoadForMonk();
	void UnloadForMonk();
	
	// WitchDoctor
	void LoadForWitchDoctor();
	void UnloadForWitchDoctor();

	// Wizard
	void LoadForWizard();
	void UnloadForWizard();

private:
	DECLARE_SINGLETON(CLoadMgr)

public:
	explicit CLoadMgr();
	~CLoadMgr();
};
