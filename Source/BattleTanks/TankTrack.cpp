// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceVector = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(ForceVector, GetComponentLocation());
}
