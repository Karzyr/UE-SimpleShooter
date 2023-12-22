// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SIMPLESHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool LineTraceSetup(UWorld* World, AController*& OwnerController, FRotator& CameraRotation, FHitResult& OutHit);
	void HitActor(UWorld* World, AController* OwnerController, FRotator CameraRotation, FHitResult OutHit);
	/**
 * Combat
 */
	// Variables


	// Functions
	void PullTrigger();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
/**
 *	Components
 */
	// Variables
	UPROPERTY(VisibleAnywhere)
	USceneComponent* WeaponSceneComponent;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* WeaponMeshComponent;

/**
 *	Combat
 */
	// Variables
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxFiringRange;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage;
	
	UPROPERTY(EditAnywhere, Category = "Combat Effects")
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category = "Combat Effects")
	UParticleSystem* ImpactEffect;
	UPROPERTY(EditAnywhere, Category = "Combat Effects")
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere, Category = "Combat Effects")
	USoundBase* ImpactSound;
};
