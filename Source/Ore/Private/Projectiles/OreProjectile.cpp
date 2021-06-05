// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/OreProjectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Core/OreGameplayStatics.h"
#include "Interfaces/VulnerableToBullets.h"

// Sets default values
AOreProjectile::AOreProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);
	
	BulletCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BulletCollision"));
	BulletCollision->SetupAttachment(DefaultRoot);

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(BulletCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

// Called when the game starts or when spawned
void AOreProjectile::BeginPlay()
{
	Super::BeginPlay();
	BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &AOreProjectile::OnProjectileImpact);

	FTimerHandle EndOfLifeTimerHandle;
	GetWorldTimerManager().SetTimer(EndOfLifeTimerHandle, this, &AOreProjectile::EndProjectileLife, LifeSpan, true);
}

// Called every frame
void AOreProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOreProjectile::OnProjectileImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// What happens when projectiles hit
	// Remove delegate
	
	OtherActor->TakeDamage(DamageDealt, FDamageEvent(),UOreGameplayStatics::GetOrePlayerController(this), UOreGameplayStatics::GetOreCharacter3P(this));

	if(OtherActor->Implements<UVulnerableToBullets>())
	{
			EndProjectileLife();	
	}

	
}

void AOreProjectile::EndProjectileLife()
{
	BulletCollision->OnComponentBeginOverlap.RemoveAll(this);
	Destroy();
}

