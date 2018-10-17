// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION(BlueprintCallable)
	ATank* GetTank() const;
	
	void AimTowardsCrosshair() const;
	void GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};
