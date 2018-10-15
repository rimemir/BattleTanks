// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Math/UnrealMathUtility.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	float DirectionChange = RelativeSpeed*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float RotationChange = RelativeRotation.Yaw + DirectionChange;
	SetRelativeRotation(FRotator(0, RotationChange, 0));
}
