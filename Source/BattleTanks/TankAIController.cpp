// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
	PlayerControlledTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player controlled pawn: %s."), *PlayerControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Didn't find player controlled pawn.") );
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ControlledTank)
	{
		ControlledTank->AimAt(PlayerControlledTank->GetActorLocation());
		ControlledTank->Fire();
	}

	
}
