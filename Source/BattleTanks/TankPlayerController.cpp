// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() const
{
	

	FVector HitLocation;

	GetSightRayHitLocation(HitLocation);

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PosessedTank = GetTank();
	if (PosessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possesing %s"), *PosessedTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Possesing nothing"));
	}



}

void ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(1.0);

	int32 ViewportX = 0;
	int32 ViewportY = 0;
	GetViewportSize(ViewportX, ViewportY);

	FVector2D ScreenLocation = FVector2D(CrossHairXLocation*ViewportX, CrossHairYLocation*ViewportY);

	FVector WorldLocation;
	FVector WorldDirection;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);
	GetLookVectorHitLocation(WorldDirection, HitLocation);
	Cast<ATank>(GetPawn())->AimAt(HitLocation);


}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		PlayerCameraManager->GetCameraLocation(),
		LookDirection*LineTraceRange,
		ECollisionChannel::ECC_Visibility
	))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}
