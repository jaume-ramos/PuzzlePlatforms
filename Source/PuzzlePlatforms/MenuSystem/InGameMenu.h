// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuWidget.h"

#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

	UFUNCTION()
	void ReturnPressed();

	UFUNCTION()
	void MainMenuPressed();


protected:
	virtual bool Initialize();
};
