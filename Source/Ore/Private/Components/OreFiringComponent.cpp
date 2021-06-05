// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OreFiringComponent.h"


#include "Core/OreGameplayStatics.h"
#include "Weapons/OreWeapon.h"

// Sets default values for this component's properties
UOreFiringComponent::UOreFiringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOreFiringComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOreFiringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AOreWeapon* UOreFiringComponent::GetEquippedWeapon() const
{
	return EquippedWeapon;
}

void UOreFiringComponent::FireWeapon()
{
	if(EquippedWeapon)
	{
		FActorSpawnParameters ProjectileSpawnParams;
		ProjectileSpawnParams.Owner = GetOwner();
		//ProjectileSpawnParams.Instigator = UOreGameplayStatics::GetOrePlayerController(this);
		//ProjectileSpawnParams.
		FTransform SpawnTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName(TEXT("Muzzle"),ERelativeTransformSpace::RTS_World));
		GetWorld()->SpawnActor(EquippedWeapon->BulletClass,&SpawnTransform, ProjectileSpawnParams);
		UOreGameplayStatics::PlaySoundAtLocation(this, EquippedWeapon->FireSound,SpawnTransform.GetLocation());
	}
}

