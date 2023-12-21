// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ShooterCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/Weapon/Weapon.h"
#include "Particles/ParticleSystem.h"

void AShooterCharacter::InitializeCamera()
{
	ShooterSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Shooter Spring Arm"));
	ShooterSpringArm->SetupAttachment(GetRootComponent());
	ShooterSpringArm->bUsePawnControlRotation = true;
	ShooterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Shooter Camera"));
	ShooterCamera->SetupAttachment(ShooterSpringArm);
}

// Sets default values
AShooterCharacter::AShooterCharacter() 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera Settings
	InitializeCamera();
}

void AShooterCharacter::SetupPlayerController()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(ShooterContext, 0);
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupPlayerController();

	UWorld* World = GetWorld();
	if (World)
		Rifle = World->SpawnActor<AWeapon>(WeaponClass);

	GetMesh()->HideBoneByName(FName("weapon_r"), PBO_None);
	Rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponSocket"));
	Rifle->SetOwner(this);

	Health = MaxHealth;

}

void AShooterCharacter::Move(const FInputActionValue& Value)
{
	const FVector MovementVector = Value.Get<FVector>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AShooterCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void AShooterCharacter::Aim()
{
	bAiming = !bAiming;
}

void AShooterCharacter::Shoot()
{
	Rifle->PullTrigger();
}

void AShooterCharacter::Jump()
{
	Super::Jump();
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move
		if (MoveAction)
			PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Move);
		
		// Look
		if (LookAction)
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Look);

		// Jump
		if (JumpAction)
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AShooterCharacter::Jump);
		
		// Aim
		if (AimAction)
			PlayerEnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AShooterCharacter::Aim);

		// Shoot
		if (ShootAction)
			PlayerEnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Shoot);
	}	
}

void AShooterCharacter::Die()
{
	bIsDead = true;
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(5.f);
}

void AShooterCharacter::HandleDamage(float DamageApplied)
{
	Health = FMath::Clamp(Health - DamageApplied, 0.f, 100.f);
	if (Health == 0.f)
		Die();	
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                    AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HandleDamage(DamageApplied);

	return DamageAmount;
}

