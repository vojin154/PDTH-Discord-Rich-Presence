Hooks:PostHook(IngameWaitingForPlayersState, "at_enter", PDTH_RPC:get_hook_id_str("at_enter"), function(self)
	PDTH_RPC:rpc():InLoadout()
end)

Hooks:PostHook(IngameWaitingForPlayersState, "start_game_intro", PDTH_RPC:get_hook_id_str("start_game_intro"), function(self)
	PDTH_RPC:rpc():Intro()
end)

Hooks:PostHook(IngameWaitingForPlayersState, "at_exit", PDTH_RPC:get_hook_id_str("at_exit"), function(self)
	PDTH_RPC:rpc():InGame()
end)