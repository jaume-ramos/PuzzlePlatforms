// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UOBject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer) {

	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/W_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuBPClass.Class->GetName());

	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/W_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *InGameMenuBPClass.Class->GetName());

	InGameMenuClass = InGameMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init() {

	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu() {

	if (!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);

	if (!ensure(Menu != nullptr)) return;


	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::InGameLoadMenu() {

	if (!ensure(MenuClass != nullptr)) return;
	UMenuWidget *InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

	if (!ensure(InGameMenu != nullptr)) return;


	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host() {

	if (Menu != nullptr) {
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	//Server travelling
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address) {


	if (Menu != nullptr) {
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();

	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu() {

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}