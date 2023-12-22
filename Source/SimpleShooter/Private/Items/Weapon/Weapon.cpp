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

bool AWeapon::LineTraceSetup(UWorld* World, AController*& OwnerController, FRotator& CameraRotation, FHitResult& OutHit)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return false;

	OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return false;

	FVector CameraLocation;
	OwnerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	const FVector Start = CameraLocation;
	const FVector End = CameraLocation + CameraRotation.Vector() * MaxFiringRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return World->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel1, Params);
}

void AWeapon::HitActor(UWorld* World, AController* OwnerController, FRotator CameraRotation, FHitResult OutHit)
{
	FVector ImpactEffectDirection = -CameraRotation.Vector();
	AActor* HitActor = OutHit.GetActor();
	if (HitActor)
	{
		FPointDamageEvent DamageEvent(Damage, OutHit, ImpactEffectDirection, nullptr);
		HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
	}
			
	if (ImpactEffect)		
		UGameplayStatics::SpawnEmitterAtLocation(World, ImpactEffect, OutHit.ImpactPoint, ImpactEffectDirection.Rotation());

	if (ImpactSound)
		UGameplayStatics::PlaySoundAtLocation(World, ImpactSound, OutHit.ImpactPoint, ImpactEffectDirection.Rotation());
}

void AWeapon::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, WeaponMeshComponent, FName("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, WeaponMeshComponent, FName("MuzzleFlashSocket"));
	
	UWorld* World = GetWorld();
	if (World)
	{
		AController* OwnerController;
		FRotator CameraRotation;
		FHitResult OutHit;
		if (LineTraceSetup(World, OwnerController, CameraRotation, OutHit))
		{
			HitActor(World, OwnerController, CameraRotation, OutHit);
		}		
	}
}

