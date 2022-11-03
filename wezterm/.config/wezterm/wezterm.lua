-- more information please see https://wezfurlong.org/wezterm/index.html
local wt = require("wezterm")

local scheme = wt.get_builtin_color_schemes()["Andromeda"]
scheme.cursor_bg = "#52ad70"
scheme.cursor_fg = "black"

return {
	window_padding = {
		left = 2,
		right = 0,
		top = 0,
		bottom = 0,
	},
	enable_tab_bar = false,
	font = wt.font("Operator Mono Lig", { weight = 325 }),
	font_size = 16,
	color_schemes = {
		["Andromeda"] = scheme,
	},
	color_scheme = "Andromeda",
	custom_block_glyphs = true,
	window_decorations = "RESIZE",
	window_close_confirmation = "NeverPrompt",
	default_cursor_style = "SteadyBar",
	cursor_blink_ease_in = "Constant",
	cursor_blink_ease_out = "Constant",
	enable_csi_u_key_encoding = true,
	window_background_opacity = 0.8,
}
