// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//float TankZPosition = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->GetComponentLocation().Z;
	//TankZPosition = FMath::Clamp(TankZPosition, 0.f, 100.f);

	FVector ForceVector = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(ForceVector, GetComponentLocation());
	UE_LOG(LogTemp, Warning, TEXT("Adding force %s to %s"), *ForceVector.ToString(), *Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->GetName());
}

