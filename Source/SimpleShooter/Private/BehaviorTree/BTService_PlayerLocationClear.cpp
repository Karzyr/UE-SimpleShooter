// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTService_PlayerLocationClear.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocationClear::UBTService_PlayerLocationClear()
{
	NodeName = TEXT("Set/Clear Player Location");
}

void UBTService_PlayerLocationClear::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		AActor* Player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		if (AIController->LineOfSightTo(Player))
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), Player);
		else
			OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
