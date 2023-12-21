// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTask_Shoot.h"

#include "AIController.h"
#include "Characters/ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AShooterCharacter* Shooter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Shooter)
		Shooter->Shoot();
	else
		return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}
