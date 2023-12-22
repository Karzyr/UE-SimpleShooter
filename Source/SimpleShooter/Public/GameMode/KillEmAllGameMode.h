// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/SimpleShooterGameMode.h"
#include "KillEmAllGameMode.generated.h"

class AShooterCharacter;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameMode : public ASimpleShooterGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	virtual void PawnKilled(APawn* PawnKilled) override;

	UFUNCTION(BlueprintPure)
	int32 GetEnemiesLeft() const;

private:
	void EndGame(bool bIsPlayerWinner);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AShooterCharacter> ShooterClass;
	UPROPERTY()
	TArray<AActor*> Enemies;

	int32 EnemiesLeft;
};
