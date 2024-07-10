Hooks:PostHook(ClientNetworkSession, "on_join_request_reply", PDTH_RPC:get_hook_id_str("on_join_request_reply"), function(self, reply, my_peer_id, level_index, difficulty_index, state_index, mask_set, user_id, sender)
    PDTH_RPC:set_attributes(level_index, difficulty_index)
end)