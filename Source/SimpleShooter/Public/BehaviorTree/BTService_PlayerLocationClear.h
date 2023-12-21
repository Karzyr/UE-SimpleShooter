// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocationClear.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTService_PlayerLocationClear : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UBTService_PlayerLocationClear();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
