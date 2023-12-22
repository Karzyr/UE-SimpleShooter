// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "Characters/ShooterCharacter.h"
#include "Controllers/ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AKillEmAllGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ShooterClass, Enemies);

	EnemiesLeft = Enemies.Num()-1;
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	if (APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController()))
	{
		if (PlayerController)
			EndGame(false);
	}
	else
	{
		EnemiesLeft -= 1;
		// for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
		// {
		// 	if (!Controller->IsDead()) return;
		// }
		if (EnemiesLeft == 0)
			EndGame(true);
	}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

int32 AKillEmAllGameMode::GetEnemiesLeft() const
{
	return EnemiesLeft;
}
