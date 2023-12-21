// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon/Weapon.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "SimpleShooter/DebugMacros.h"

// Sets default values
AWeapon::AWeapon() : MaxFiringRange(1000.f), Damage(10.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	WeaponSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Scene"));
	SetRootComponent(WeaponSceneComponent);
	
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, WeaponMeshComponent, FName("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	OwnerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
	
	UWorld* World = GetWorld();
	if (World)
	{
		FHitResult OutHit;

		const FVector Start = CameraLocation;
		const FVector End = CameraLocation + CameraRotation.Vector() * MaxFiringRange;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		bool bHit = World->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel1, Params);

		if (bHit)
		{
			FVector ImpactEffectDirection = -CameraRotation.Vector();
			if (ImpactEffect)		
				UGameplayStatics::SpawnEmitterAtLocation(World, ImpactEffect, OutHit.ImpactPoint, ImpactEffectDirection.Rotation());

			AActor* HitActor = OutHit.GetActor();
			if (HitActor)
			{
				FPointDamageEvent DamageEvent(Damage, OutHit, ImpactEffectDirection, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}
	}
}

