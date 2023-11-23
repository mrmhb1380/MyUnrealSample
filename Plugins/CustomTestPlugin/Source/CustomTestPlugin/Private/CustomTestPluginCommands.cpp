// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomTestPluginCommands.h"

#define LOCTEXT_NAMESPACE "FCustomTestPluginModule"

void FCustomTestPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "CustomTestPlugin", "Bring up CustomTestPlugin window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
