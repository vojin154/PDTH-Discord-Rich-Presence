PDTH_RPC = PDTH_RPC or class()
PDTH_RPC._mod_path = ModPath
PDTH_RPC._save_path = SavePath .. "PDTH_RPC_RECENT_PLAYERS.txt"
PDTH_RPC._dll_name = "PDTH Discord Rich Presence.dll"
PDTH_RPC._dll_location = "./" .. PDTH_RPC._dll_name
PDTH_RPC._game_id = "24240"
PDTH_RPC._join_link = "steam://joinlobby/"
PDTH_RPC._players = {}

function PDTH_RPC:dll_exists()
	if not io.file_is_readable(self._dll_location) then
		return
	end
	return true
end

if not PDTH_RPC:dll_exists() then
	error(".DLL WASN'T FOUND, MAKE SURE YOU'VE DRAGGED YOUR .DLL TO THE ROOT FOLDER. MORE INFO ON MODS PAGE.")
	return
end

_, PDTH_RPC._rich_presence = blt.load_native(PDTH_RPC._dll_location)

local hook_id = "PDTH_RPC"
function PDTH_RPC:get_hook_id_str(str)
	return str .. "_" .. hook_id
end

function PDTH_RPC:Load()
	local file = io.open(self._save_path, "r")
	if file then
		self._players = json.decode(file:read("*all"))
		file:close()
	end
end

function PDTH_RPC:Save()
	local file = io.open(self._save_path, "w+")
	if file then
		file:write(json.encode(self._players))
		file:close()
	end
end

function PDTH_RPC:in_menu()
	self._players = {}
	self:Save()
	self:rpc():InMenu()
end

--[[
	Broken, don't use.
	Keeping for future incase, I get to fix it somehow.
	function PDTH_RPC:set_time_stamp()
		PDTH_RPC:rpc():SetTimestamp(os.time())
	end
]]

function PDTH_RPC:get_player(user_id)
	for i = 1, #self._players do
		if self._players[i] == user_id then
			return self._players[i], i
		end
	end
end

function PDTH_RPC:player_added(user_id)
	if self:get_player(user_id) then
		return
	end
	table.insert(self._players, user_id)
	self:Save()
	self:rpc():IncrementPlayers()
end

function PDTH_RPC:player_removed(user_id)
	local player, i = self:get_player(user_id)
	if not player then
		return
	end
	table.remove(self._players, i)
	self:Save()
	self:rpc():DecrementPlayers()
end

function PDTH_RPC:get_join_link(lobby_id, host_id)
	return self._join_link .. self._game_id .. "/" .. tostring(lobby_id) .. "/" .. tostring(host_id)
end

function PDTH_RPC:rpc()
	return self._rich_presence
end

PDTH_RPC:Load()

local required = {}
if RequiredScript and not required[RequiredScript] then
	local fname = PDTH_RPC._mod_path .. RequiredScript:gsub(".+/(.+)", "lua/%1.lua")
	if io.file_is_readable(fname) then
		dofile(fname)
	end

	required[RequiredScript] = true
end