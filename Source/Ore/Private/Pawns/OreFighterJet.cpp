// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/OreFighterJet.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Pawns/OreCharacter.h"
#include "Components/BoardSpacecraft.h"
#include "Components/OreBombingComponent.h"
#include "Core/OreGameplayStatics.h"
#include "UI/OreHUD.h"

// Sets default values
AOreFighterJet::AOreFighterJet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("MeshCollision"));
	SetRootComponent(MeshCollision);
	
	BoardSpacecraft = CreateDefaultSubobject<UBoardSpacecraft>(TEXT("BoardSpacecraftComponent"));
	BoardSpacecraft->SetupAttachment(MeshCollision);
	
	FighterJetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FighterJetMesh"));
	FighterJetMesh->SetupAttachment(MeshCollision);

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(MeshCollision);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create the Firing component
	FiringComponent = CreateDefaultSubobject<UOreFiringComponent>(TEXT("FiringComponent"));

	// Create the Bombing component
	BombingComponent = CreateDefaultSubobject<UOreBombingComponent>(TEXT("BombingComponent"));
}

void AOreFighterJet::GetPossessedByPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*
	if (AOreCharacter* InteractingCharacter = Cast<AOreCharacter>(OtherActor))
	{
		if (InteractingCharacter->GetOrePlayerController()->PlayerMovementMode != EOreMovementMode::Piloting)
		{
			InteractingCharacter->GetOrePlayerController()->Possess(this);
			InteractingCharacter->HideCharacter();
		}
	}*/
}

void AOreFighterJet::OnSpacecraftDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(InstigatedBy != UOreGameplayStatics::GetOrePlayerController(this))
	{
		CurrentHealth -= Damage;
		//UE_LOG(LogTemp, Warning, TEXT("FigherJet was attacked! [Damage: %f]"), Damage);
		UOreGameplayStatics::GetOreGameMode(this)->MainHUD->UpdateSpacecraftHealth(CurrentHealth/Health);		
	}
	if(CurrentHealth <= 0)
	{
		if(OrePlayerController)
		{
			OrePlayerController->OnSpacecraftDestroyed();			
		}
		else
		{
			UOreGameplayStatics::GetOrePlayerController(this)->OnSpacecraftDestroyed();
		}
	}
}

UOreFiringComponent* AOreFighterJet::GetFiringComponent() const
{
	return FiringComponent;
}

UOreBombingComponent* AOreFighterJet::GetBombingComponent() const
{
	return BombingComponent;
}

// Called when the game starts or when spawned
void AOreFighterJet::BeginPlay()
{
	Super::BeginPlay();

	// Bind the interaction delegate
	//InteractionTrigger->OnComponentBeginOverlap.AddDynamic(this, &AOreFighterJet::GetPossessedByPlayer);

	OnTakeAnyDamage.AddDynamic(this, &AOreFighterJet::OnSpacecraftDamaged);
	CurrentHealth = Health;
	
}

// Called every frame
void AOreFighterJet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* AOreFighterJet::GetFighterJetMesh() const
{
	return FighterJetMesh;
}

// Called to bind functionality to input
void AOreFighterJet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AOreFighterJet::SetupPlayerControllerRef(AOrePlayerController* InPlayerController)
{
	OrePlayerController = InPlayerController;
}

