// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

class UBehaviorTree;

UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	//Player 0
	UPROPERTY(VisibleAnywhere)
	AActor* Player;

/**
 * AI Attributes
 */
	// Variables
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float AcceptanceRadius = 200.f;
	
/**
 * BehaviorTree
 */
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	bool bRunningAIBehavior;
	
};
