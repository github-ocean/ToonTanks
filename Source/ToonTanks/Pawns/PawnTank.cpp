// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}	

void APawnTank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotationUpdate();
	Move();
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotationInput);
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDircation = FVector(Value * MoveSpeed * GetWorld()->GetDeltaSeconds(), 0, 0);
}

void APawnTank::CalculateRotationInput(float Value)
{
	float RotatAmount = Value * RotationSpeed * GetWorld()->GetDeltaSeconds();
	FRotator Rotation = FRotator(0, RotatAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDircation, true);
}

void APawnTank::RotationUpdate()
{
	AddActorLocalRotation(RotationDirection, true);
}