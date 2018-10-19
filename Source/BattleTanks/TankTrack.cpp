// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp(CurrentThrottle + Throttle, -2.f, 2.f);
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentThrottle < 0)
	{
		CurrentThrottle = FMath::Clamp(CurrentThrottle + 0.1f, -2.f, 0.f);
	}
	else
	{
		CurrentThrottle = FMath::Clamp(CurrentThrottle - 0.1f, 0.f, 2.f);
	}
	
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::DriveTrack()
{
	//set track forces
	FVector ForceVector = GetForwardVector()*CurrentThrottle*TrackMaxDrivingForce;
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForceAtLocation(ForceVector, GetComponentLocation());
	//UE_LOG(LogTemp, Warning, TEXT("%s Adding force to track %s"), *GetOwner()->GetName(), *ForceVector.ToString())
	UE_LOG(LogTemp, Warning, TEXT("%s current throttle is %f"), *GetOwner()->GetName(), CurrentThrottle);

	//add sideways friction
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	FVector CorrectionAcceleration = -SlippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();
	FVector CorrectionForce = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->GetMass() * CorrectionAcceleration / 2;
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
}
