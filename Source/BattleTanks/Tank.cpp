// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

class UTankTurret;

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::AimAt(FVector AimLocation)
{
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();


}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (!(TankAimingComponent->FiringState == EFiringState::OutOfAmmo))
	{
		if (!bIsReloaded)
		{
			TankAimingComponent->FiringState = EFiringState::Reloading;
		}
		else if (TankAimingComponent->TurretIsLocked())
		{
			TankAimingComponent->FiringState = EFiringState::Locked;
		}
		else
		{
			TankAimingComponent->FiringState = EFiringState::Aiming;
		}
	}
	
}

UTankAimingComponent* ATank::GetTankAimingComponent() const
{
	return TankAimingComponent;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	if (TankAimingComponent->FiringState != EFiringState::Reloading && TankAimingComponent->FiringState != EFiringState::OutOfAmmo)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		if (--TankAimingComponent->AmmoCount <= 0)
		{
			TankAimingComponent->FiringState = EFiringState::OutOfAmmo;
		}
	}


}
