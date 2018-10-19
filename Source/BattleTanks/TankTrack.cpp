// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceVector = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(ForceVector, GetComponentLocation());
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	FVector CorrectionForce = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->GetMass() * CorrectionAcceleration / 2;
	AddForce(CorrectionForce);
}