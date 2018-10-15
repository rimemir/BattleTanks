// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	float ElevationChange = RelativeSpeed*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float RotationChange = RelativeRotation.Pitch + ElevationChange;
	SetRelativeRotation(FRotator(FMath::ClampAngle(RotationChange, MinElevationDegrees, MaxElevationDegrees), 0, 0));
}
