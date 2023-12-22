// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AWeapon;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	void InitializeCamera();
	AShooterCharacter();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Die();
	void HandleDamage(float DamageApplied);
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

/**
 * Combat
 */
	// Functions
	void Shoot();

/**
 * Attributes
 */
	//Variables 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	bool bIsDead = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

/**
 * Combat
 */
	// Variables
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY(VisibleInstanceOnly)
	AWeapon* Rifle;
	
private:
/**
 * Input
 */
	// Variables
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* ShooterContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AimAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ShootAction;
	
	// Functions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Aim();
	virtual void Jump() override;
	
	void SetupPlayerController();
	
/**
 * Camera
 */
	//Variables	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* ShooterCamera;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* ShooterSpringArm;

/**
 * Combat
 */
	//Variables	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Combat", meta=(AllowPrivateAccess = "true"))
	bool bAiming = false;

/**
 * Attributes
 */
	// Variables
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Health;
	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float MaxHealth = 100.f;

public:
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;
};
