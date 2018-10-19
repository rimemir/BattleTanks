// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 3000.f;

private:

	ATank* ControlledTank = nullptr;
	ATank* PlayerControlledTank = nullptr;



};
