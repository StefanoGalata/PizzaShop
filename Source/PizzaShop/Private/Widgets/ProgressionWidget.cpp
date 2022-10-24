// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ProgressionWidget.h"
#include "Components/ProgressBar.h"

void UProgressionWidget::SetWidgetProgression(float Value)
{
	ProgressBar->SetPercent(Value);
}
