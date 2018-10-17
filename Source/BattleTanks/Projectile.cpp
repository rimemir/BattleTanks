// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovementComponent->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float ProjectileSpeed)
{
	float TimeStamp = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Boom!"), TimeStamp);
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector*ProjectileSpeed);
	ProjectileMovementComponent->Activate();

	

	FVector ForceVector = GetRootComponent()->GetForwardVector()*ProjectileSpeed*ForceOfLaunch;
	Cast<UPrimitiveComponent>(GetRootComponent())->AddForceAtLocation(ForceVector, GetRootComponent()->GetComponentLocation());
}
