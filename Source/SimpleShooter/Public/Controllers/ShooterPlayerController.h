// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY()
	UUserWidget* HUD;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreenClass;
	
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	FTimerHandle RestartTimer;
};
