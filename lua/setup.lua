Hooks:PostHook(Setup, "set_main_thread_loading_screen_visible", PDTH_RPC:get_hook_id_str("set_main_thread_loading_screen_visible"), function(self, visible)
    PDTH_RPC:rpc():Loading(visible)
end)