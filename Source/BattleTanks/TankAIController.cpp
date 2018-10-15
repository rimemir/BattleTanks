// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetPlayerControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player controlled pawn: %s."), *GetPlayerControlledTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Didn't find player controlled pawn.") );
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Cast<ATank>(GetPawn())->AimAt(GetPlayerControlledTank()->GetActorLocation());
}

ATank* ATankAIController::GetPlayerControlledTank()
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}