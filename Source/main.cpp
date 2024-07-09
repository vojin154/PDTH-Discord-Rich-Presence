/*
	FOR THE LOVE OF THE ACTUAL GOD, DON'T READ THE CODE.
	I DON'T KNOW C++ AND THIS IS JUST PAINFUL TO LOOK AT.
*/


#include "SuperBLT/superblt.h"
#include "Discord/discord.h"

Discord* discord;

void Plugin_Init()
{
	discord->Initialize();
}

void Plugin_Update()
{
	discord->Update();
}

void Plugin_Setup_Lua(lua_State* lua)
{
	// Deprecated, see this function's documentation (in superblt_flat.h) for more detail
}

static int InLoadout(lua_State* L) {
	discord->InLoadout();

	return 0;
}

static int Intro(lua_State* L) {
	discord->Intro();

	return 0;
}

static int InLobby(lua_State* L) {
	discord->InLobby(true);

	return 0;
}

static int IncrementPlayers(lua_State* L) {
	discord->IncrementPlayers();

	return 0;
}

static int DecrementPlayers(lua_State* L) {
	discord->DecrementPlayers();

	return 0;
}

static int InGame(lua_State* L) {
	discord->Playing();

	return 0;
}

static int InMenu(lua_State* L) {
	discord->InMenu();

	return 0;
}

static int SetPlayerCount(lua_State* L) {
	int amount = lua_tointeger(L, -1);
	discord->SetPlayerCount(amount);

	return 0;
}

static int SetHeist(lua_State* L) {
	const char* heist = lua_tostring(L, -1);
	discord->SetHeist(heist);

	return 0;
}

static int SetDifficulty(lua_State* L) {
	const char* difficulty = lua_tostring(L, -1);
	discord->SetDifficulty(difficulty);

	return 0;
}

static int IsMultiplayer(lua_State* L) {
	bool multiplayer = lua_toboolean(L, -1);
	discord->SetMultiplayer(multiplayer);

	return 0;
}

static int Loading(lua_State* L) {
	bool is_loading = lua_toboolean(L, -1);
	discord->SetLoading(is_loading);

	return 0;
}

int Plugin_PushLua(lua_State* L)
{
	lua_newtable(L);

	lua_pushcfunction(L, SetPlayerCount);
	lua_setfield(L, -2, "SetPlayerCount");

	lua_pushcfunction(L, IncrementPlayers);
	lua_setfield(L, -2, "IncrementPlayers");

	lua_pushcfunction(L, DecrementPlayers);
	lua_setfield(L, -2, "DecrementPlayers");

	lua_pushcfunction(L, InGame);
	lua_setfield(L, -2, "InGame");

	lua_pushcfunction(L, InMenu);
	lua_setfield(L, -2, "InMenu");

	lua_pushcfunction(L, SetHeist);
	lua_setfield(L, -2, "SetHeist");

	lua_pushcfunction(L, SetDifficulty);
	lua_setfield(L, -2, "SetDifficulty");

	lua_pushcfunction(L, Loading);
	lua_setfield(L, -2, "Loading");

	lua_pushcfunction(L, InLoadout);
	lua_setfield(L, -2, "InLoadout");

	lua_pushcfunction(L, Intro);
	lua_setfield(L, -2, "Intro");

	lua_pushcfunction(L, InLobby);
	lua_setfield(L, -2, "InLobby");

	lua_pushcfunction(L, IsMultiplayer);
	lua_setfield(L, -2, "IsMultiplayer");

	return 1;
}