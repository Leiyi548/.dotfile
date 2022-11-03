-- more information please see https://wezfurlong.org/wezterm/index.html
local wt = require("wezterm")

local function get_theme()
	-- more color_scheme please see https://wezfurlong.org/wezterm/colorschemes/index.html
	local _time = os.date("*t")
	if _time.hour >= 8 and _time.hour < 16 then
		-- return "tokyonight_night"
		return "Catppuccin Latte" -- light theme
	else
		-- return "Catppuccin Frappe" -- Macchiato Frappe Mocha
		return "tokyonight_night"
		-- return "Catppuccin Latte" -- light theme
		-- return "kanagawabones"
		-- return "Rosé Pine (base16)"
	end
end

return {
	window_padding = {
		left = 0,
		right = 0,
		top = 0,
		bottom = 0,
	},
	enable_tab_bar = false,
	font = wt.font("JetBrainsMono Nerd Font", { weight = 325 }),
	font_size = 15,
	bold_brightens_ansi_colors = true,
	color_scheme = get_theme(),
	custom_block_glyphs = true,
	window_decorations = "RESIZE",
	window_close_confirmation = "NeverPrompt",
	default_cursor_style = "SteadyBar",
	cursor_blink_ease_in = "Constant",
	cursor_blink_ease_out = "Constant",
	enable_csi_u_key_encoding = false,
	window_background_opacity = 0.9,
}
