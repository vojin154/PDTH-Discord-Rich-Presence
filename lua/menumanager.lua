Hooks:PostHook(MenuManager, "open_menu", PDTH_RPC:get_hook_id_str("open_menu"), function(self, menu_name, ...)
    if self:is_active() then
        if menu_name == "lobby_menu"then
            PDTH_RPC:rpc():InLobby()
        elseif menu_name == "menu_main" then
            PDTH_RPC:in_menu()
        end
    end
end)

Hooks:PostHook(MenuCallbackHandler, "lobby_start_the_game", PDTH_RPC:get_hook_id_str("lobby_start_the_game"), function(self)
    local id = Global.game_settings.level_id
	local name = id and tweak_data.levels[id].world_name
    local heist = string.upper(tweak_data.levels:get_localized_level_name_from_world_name(name))
    local difficulty = string.upper(managers.localization:text("menu_difficulty_" .. Global.game_settings.difficulty))

    PDTH_RPC:rpc():SetHeist(heist)
    PDTH_RPC:rpc():SetDifficulty(difficulty)
end)


Hooks:PostHook(MenuCallbackHandler, "play_single_player", PDTH_RPC:get_hook_id_str("play_single_player"), function(self)
    PDTH_RPC:rpc():InLobby()
end)
