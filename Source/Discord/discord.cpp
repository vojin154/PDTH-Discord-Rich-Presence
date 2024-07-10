/*
    ARE YOUR EYES BLEEDING YET?
    NO?
    THEN THEY SURELY WILL AFTER THIS
*/

/*
TO-DO:
    - FIGURE OUT THE NAME OF THE ICON OVK USED SINCE DISCORD DOESNT WANT TO TELL ME / OR MAKE MY OWN APPLICATION / MANAGE TO RESIZE THE IMAGE TAKEN STRAIGHT FROM DISCORD
      https://cdn.discordapp.com/app-icons/451546040382914567/0b5a98a56a970a8c62e497bf2b9063c7.webp - FOR SOME REASON DISCORD RESIZES THE IMAGES WHEN USING LINK??
      ADDING ?size=40 CHANGES RESOLUTION
      TRIED ALSO ADDING keep_aspect_ratio=false BUT DISCORD SEEMS TO IGNORE IT
      EVEN THOUGH THEY USE https://cdn.discordapp.com/app-icons/451546040382914567/0b5a98a56a970a8c62e497bf2b9063c7.webp?size=40&keep_aspect_ratio=false IT DOESN'T WORK WHEN USING FROM HERE

    - ADD SUPPORT FOR CUSTOM MESSAGES

    - IF THAT EVER HAPPENS ADD SUPPORT FOR MAX PLAYERS AMOUNT

    - IMPROVE CODE
*/

#include "discord.h"
#include "../SuperBLT/superblt.h"

const char* rpcID = "451546040382914567";
const char* name = "PAYDAY: The Heist";
const char* gameId = "24240";
const char* icon = "https://cdn.discordapp.com/app-icons/451546040382914567/0b5a98a56a970a8c62e497bf2b9063c7.webp";
std::string mod = "[PDTH - DISCORD RPC]";

DiscordRichPresence discordPresence;
DiscordEventHandlers Handle;

int playerCount = 0;
int maxPlayerAmount = 4;
std::string heist = "";
std::string difficulty = "";
bool loading = false;
bool inLobby = false;
bool multiplayer = false;

/*
void handleDiscordJoinGame(const char* joinSecret) {
    PD2HOOK_LOG_LOG("handleDiscordJoinGame");
    PD2HOOK_LOG_LOG(joinSecret);
}

void handleDiscordJoinRequest(const DiscordUser* user) {
    PD2HOOK_LOG_LOG("handleDiscordJoinRequest");
    PD2HOOK_LOG_LOG(user->username);
    Discord_Respond(user->userId, DISCORD_REPLY_YES);
}
*/

static void handleDiscordReady(const DiscordUser* user) {
    std::string username = user->username;
    std::string message = mod + " Logged in as: " + username;
    PD2HOOK_LOG_LOG(message.c_str());
}

static void handleDiscordError(int errorCode, const char* message) {
    std::string reason = message;
    std::string error = mod + " " + reason;
    PD2HOOK_LOG_ERROR(error.c_str());
}

static void handleDiscordDisconnected(int errorCode, const char* message) {
    std::string reason = message;
    std::string warn = mod + " " + reason;
    PD2HOOK_LOG_WARN(warn.c_str());
}

void Discord::Initialize() {
    std::string initializeString = mod + " DISCORD RICH PRESENCE INITIALIZED!";
    PD2HOOK_LOG_LOG(initializeString.c_str());

    memset(&Handle, 0, sizeof(Handle));

    Handle.ready = handleDiscordReady;
    Handle.errored = handleDiscordError;
    Handle.disconnected = handleDiscordDisconnected;
    //Handle.joinGame = handleDiscordJoinGame;
    //Handle.joinRequest = handleDiscordJoinRequest;

    Discord_Initialize(rpcID, &Handle, 1, gameId);
}

void Discord::Update() {
    Discord_RunCallbacks();
}

static std::string HeistWithDifficulty() {
    return heist + " (" + difficulty + ")";
}

//It's to set stuff (example icon), which isn't supposed to change, as Discord_UpdatePresence, changes them, to default if not provided differently.
static void SetStatic() {
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.largeImageKey = icon;
}

const char* discState;
static void SetStatus(bool update, const char* state) {
    SetStatic();

    if (update) {
        discState = state;
    }
    discordPresence.state = discState;

    if (inLobby) {
        if (multiplayer) {
            discordPresence.partySize = playerCount;
            discordPresence.partyMax = maxPlayerAmount;
        }
        std::string text = HeistWithDifficulty();
        discordPresence.details = text.c_str();
    }

    Discord_UpdatePresence(&discordPresence);
}

void Discord::IncrementPlayers() {
    Discord::SetPlayerCount(playerCount + 1);
}

void Discord::DecrementPlayers() {
    Discord::SetPlayerCount(playerCount - 1);
}

void Discord::InMenu() {
    Discord::SetPlayerCount(0);
    Discord::SetMultiplayer(false);
    Discord::InLobby(false);
    SetStatus(true, "In Menu!");
}

void Discord::InLoadout() {
    SetStatus(true, "Choosing A Loadout!");
}

void Discord::Intro() {
    SetStatus(true, "Listening To Bains Plan!");
}

void Discord::Playing() {
    if (multiplayer) {
        SetStatus(true, "Heist In Progress!");
    }
    else SetStatus(true, "Heist In Progress! (OFFLINE)");
}

void Discord::SetPlayerCount(int amount) {
    playerCount = amount;
    SetStatus(false, "");
}

void Discord::SetHeist(const char* heist_char) {
    std::string heist_string = heist_char;
    heist = heist_string;
    SetStatus(false, "");
}

void Discord::SetDifficulty(const char* difficulty_char) {
    std::string difficulty_string = difficulty_char;
    difficulty = difficulty_string;
    SetStatus(false, "");
}

void Discord::SetMultiplayer(bool isMultiplayer) {
    if (isMultiplayer) {
        multiplayer = true;
    }
    else multiplayer = false;
    SetStatus(false, "");
}

void Discord::SetLoading(bool is_loading) {
    loading = is_loading;
    SetStatus(true, "Loading!");
}

void Discord::InLobby(bool lobby) {
    inLobby = lobby;
    SetStatus(true, "In Lobby!");
}