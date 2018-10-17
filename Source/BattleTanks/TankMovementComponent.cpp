// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(3*Throw);
		RightTrack->SetThrottle(-3*Throw);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	

	FVector IntendedMoveDirection = MoveVelocity.GetSafeNormal();
	FVector TankFacingDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	float MoveIntensity = FVector::DotProduct(IntendedMoveDirection, TankFacingDirection);
	IntendMoveForward(MoveIntensity);
	
	float RotateIntensity = FVector::CrossProduct(TankFacingDirection, IntendedMoveDirection).Z;
	UE_LOG(LogTemp, Warning, TEXT("Rotating with intensity %f"), RotateIntensity)
	IntendTurnRight(RotateIntensity);

}

void UTankMovementComponent::InitialiseTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
