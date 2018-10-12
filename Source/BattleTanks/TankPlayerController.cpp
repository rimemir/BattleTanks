// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank * ATankPlayerController::GetTank()
{
	return Cast<ATank>(GetPawn());
}
