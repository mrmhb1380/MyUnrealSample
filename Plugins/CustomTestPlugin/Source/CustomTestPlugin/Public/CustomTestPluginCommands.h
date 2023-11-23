// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CustomTestPluginStyle.h"

class FCustomTestPluginCommands : public TCommands<FCustomTestPluginCommands>
{
public:

	FCustomTestPluginCommands()
		: TCommands<FCustomTestPluginCommands>(TEXT("CustomTestPlugin"), NSLOCTEXT("Contexts", "CustomTestPlugin", "CustomTestPlugin Plugin"), NAME_None, FCustomTestPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};