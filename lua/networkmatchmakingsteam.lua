Hooks:PostHook(NetworkMatchMakingSTEAM, "set_attributes", PDTH_RPC:get_hook_id_str("set_attributes"), function(self, settings)
	settings = settings and settings.numbers

	if not settings then
		return
	end

    PDTH_RPC:set_attributes(settings[1], settings[2])
end)