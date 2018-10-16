// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"

void UTankTrack::SetThrottle(float Throttle)
{
	float TankZPosition = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->GetComponentLocation().Z;
	constexpr float MAX_HOVER_HEIGHT = 300.f;
	TankZPosition = FMath::Clamp(TankZPosition, 0.f, MAX_HOVER_HEIGHT);
	FVector ForceVector = GetUpVector()*Throttle*TrackMaxDrivingForce*(1.f - TankZPosition/MAX_HOVER_HEIGHT);
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(ForceVector, GetComponentLocation() - FVector(200.f, 0.f, 0.f));
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(ForceVector, GetComponentLocation() + FVector(200.f, 0.f, 0.f));
	UE_LOG(LogTemp, Warning, TEXT("Adding force %s to %s with Z position %f"), *ForceVector.ToString(), *Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->GetName(), TankZPosition);
}
