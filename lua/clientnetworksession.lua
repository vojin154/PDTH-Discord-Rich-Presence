Hooks:PostHook(ClientNetworkSession, "on_join_request_reply", PDTH_RPC:get_hook_id_str("on_join_request_reply"), function(self, reply, my_peer_id, level_index, difficulty_index, state_index, mask_set, user_id, sender)
    local heist = tweak_data.levels:get_world_name_from_index(level_index)
	heist = string.upper(tweak_data.levels:get_localized_level_name_from_world_name(heist))

    local difficulty = string.upper(tweak_data:index_to_difficulty(difficulty_index))

    PDTH_RPC:rpc():SetHeist(heist)
    PDTH_RPC:rpc():SetDifficulty(difficulty)
end)