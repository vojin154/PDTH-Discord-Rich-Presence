Hooks:PostHook(BaseNetworkSession, "init", PDTH_RPC:get_hook_id_str("init"), function(self)
    local is_singleplayer = Global.game_settings.single_player
    if is_singleplayer then
		PDTH_RPC:rpc():IsMultiplayer(false)
        return
    end
	PDTH_RPC:rpc():IsMultiplayer(true)
end)