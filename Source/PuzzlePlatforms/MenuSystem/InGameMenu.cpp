// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize() {

	bool Succes = Super::Initialize();

	if (!Succes) return false;

	if (!ensure(ReturnButton != nullptr)) return false;
	ReturnButton->OnClicked.AddDynamic(this, &UInGameMenu::ReturnPressed);

	if (!ensure(MainMenuButton != nullptr)) return false;
	MainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::MainMenuPressed);

	return true;
}

void UInGameMenu::ReturnPressed() {
	
	Teardown();
}

void UInGameMenu::MainMenuPressed() {

	if (MenuInterface != nullptr) {
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}