// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (AIBehavior)
	{
		bRunningAIBehavior = RunBehaviorTree(AIBehavior);

		GetBlackboardComponent()->SetValueAsVector(FName("AIStart"), GetPawn()->GetActorLocation());		
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}
