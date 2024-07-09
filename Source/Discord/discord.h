#pragma once

#include "discord_register.h"
#include "discord_rpc.h"
#include <Windows.h>
#include <string>

class Discord {
public:
    void Initialize();
    void Update();
    void IncrementPlayers();
    void DecrementPlayers();
    void InMenu();
    void InLoadout();
    void Intro();
    void Playing();
    void SetPlayerCount(int amount);
    void SetHeist(const char* heist_char);
    void SetDifficulty(const char* difficulty_char);
    void SetMultiplayer(bool multiplayer);
    void SetLoading(bool is_loading);
    void InLobby(bool lobby);
};