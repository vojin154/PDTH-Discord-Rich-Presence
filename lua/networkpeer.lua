Hooks:PostHook(NetworkPeer, "init", PDTH_RPC:get_hook_id_str("init"), function(self, name, rpc, id, loading, synced, in_lobby, mask_set, user_id)
	PDTH_RPC:player_added(user_id)
end)

Hooks:PostHook(NetworkPeer, "destroy", PDTH_RPC:get_hook_id_str("destroy"), function(self)
	PDTH_RPC:player_removed(self._user_id)
end)