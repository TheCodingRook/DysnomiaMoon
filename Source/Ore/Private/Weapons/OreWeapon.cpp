// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/OreWeapon.h"

// Sets default values
AOreWeapon::AOreWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponMesh->SetRelativeLocation(FVector(200.f, 150.f, 0.f));

}

// Called when the game starts or when spawned
void AOreWeapon::BeginPlay()
{
	Super::BeginPlay();

	if(nullptr == BulletClass)
	{
		UE_LOG(LogTemp, Error, TEXT("You have not defined a bullet class for weapon type: %s"), *GetClass()->GetName());
	}
	
}

// Called every frame
void AOreWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* AOreWeapon::GetWeaponMesh() const
{
	return WeaponMesh;
}

