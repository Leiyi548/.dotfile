-- more information please see https://wezfurlong.org/wezterm/index.html
local wt = require("wezterm")

local function get_theme()
	local _time = os.date("*t")
	if _time.hour >= 1 and _time.hour < 9 then
		return "Rosé Pine (base16)"
	elseif _time.hour >= 9 and _time.hour < 17 then
		return "tokyonight_night"
	elseif _time.hour >= 17 and _time.hour < 21 then
		return "Catppuccin Mocha"
	elseif _time.hour >= 21 and _time.hour < 24 or _time.hour >= 0 and _time.hour < 1 then
		return "kanagawabones"
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
	font = wt.font("Operator Mono Lig", { weight = 325 }),
	font_size = 16,
	bold_brightens_ansi_colors = true,
	color_scheme = get_theme(),
	custom_block_glyphs = true,
	window_decorations = "RESIZE",
	window_close_confirmation = "NeverPrompt",
	default_cursor_style = "SteadyBar",
	cursor_blink_ease_in = "Constant",
	cursor_blink_ease_out = "Constant",
	enable_csi_u_key_encoding = true,
	window_background_opacity = 0.8,
}
