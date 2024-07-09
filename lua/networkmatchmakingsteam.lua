Hooks:PostHook(NetworkMatchMakingSTEAM, "set_attributes", PDTH_RPC:get_hook_id_str("set_attributes"), function(self, settings)
	settings = settings and settings.numbers

	if not settings then
		return
	end

	local heist = settings[1] and tweak_data.levels:get_world_name_from_index(settings[1])
	heist = string.upper(tweak_data.levels:get_localized_level_name_from_world_name(heist))
	local difficulty = settings[2] and tweak_data:index_to_difficulty(settings[2])
	difficulty = string.upper(managers.localization:text("menu_difficulty_" .. difficulty))

    PDTH_RPC:rpc():SetHeist(heist)
    PDTH_RPC:rpc():SetDifficulty(difficulty)
end)