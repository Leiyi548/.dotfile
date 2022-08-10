#include <X11/XF86keysym.h>

static int showsystray = 1;           /* 是否显示托盘栏 */
static const int newclientathead = 0; /* 定义新窗口在栈顶还是栈底 */
static const unsigned int borderpx = 2; /* 窗口边框大小 */
static const unsigned int systraypinning =
    1; /* 托盘跟随的显示器 0代表不指定显示器 */
static const unsigned int systrayspacing = 1; /* 托盘间距 */
static int gappi = 12;                        /* 窗口与窗口 缝隙大小 */
static int gappo = 12;                        /* 窗口与边缘 缝隙大小 */
static const int _gappo =
    12; /* 窗口与窗口 缝隙大小 不可变 用于恢复时的默认值 */
static const int _gappi =
    12; /* 窗口与边缘 缝隙大小 不可变 用于恢复时的默认值 */
static const int overviewgappi = 24; /* overview时 窗口与边缘 缝隙大小 */
static const int overviewgappo = 60; /* overview时 窗口与窗口 缝隙大小 */
static const int showbar = 1;        /* 是否显示状态栏 */
static const int topbar = 1;         /* 指定状态栏位置 0底部 1顶部 */
static const float mfact = 0.6;      /* 主工作区 大小比例 */
static const int nmaster = 1;        /* 主工作区 窗口数量 */
static const unsigned int snap = 10;          /* 边缘依附宽度 */
static const unsigned int baralpha = 0xc0;    /* 状态栏透明度 */
static const unsigned int borderalpha = 0xdd; /* 边框透明度 */
static const char *fonts[] = {"JetBrainsMono Nerd Font:style=medium:size=13",
                              "monospace:size=13"};
static const char *colors[][3] = {
    [SchemeNorm] = {"#bbbbbb", "#333333", "#444444"},
    [SchemeSel] = {"#ffffff", "#37474F", "#42A5F5"},
    [SchemeHid] = {"#dddddd", NULL, NULL},
    [SchemeSystray] = {"#7799AA", "#7799AA", "#7799AA"},
    [SchemeUnderline] = {"#7799AA", "#7799AA", "#7799AA"}};
static const unsigned int alphas[][3] = {
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha}};

/* 自定义tag名称 */
/* 自定义特定实例的显示状态 */
//            ﮸ 
static const char *tags[] = {"", "", "", "", "", "",   "",
                             "", "", "", "", "ﬄ", "﬐", ""};
static const char *overviewtag = "OVERVIEW";
static const Rule rules[] = {
    /* class                 instance              title             tags mask
       isfloating  monitor */
    {"netease-cloud-music", NULL, NULL, 1 << 10, 1, -1},
    {"music", NULL, NULL, 1 << 10, 1, -1},
    {NULL, "tim.exe", NULL, 1 << 11, 0, -1},
    {NULL, "wechat.exe", NULL, 1 << 12, 0, -1},
    {NULL, "wxwork.exe", NULL, 1 << 13, 0, -1},
    {NULL, NULL, "broken", 0, 1, -1},
    {NULL, NULL, "图片查看", 0, 1, -1},
    {NULL, NULL, "图片预览", 0, 1, -1},
    {NULL, NULL, "crx_", 0, 1, -1},
    {"chrome", NULL, NULL, 1 << 9, 0, -1},
    {"Chromium", NULL, NULL, 1 << 9, 0, -1},
    {"float", NULL, NULL, 0, 1, -1},
    {"flameshot", NULL, NULL, 0, 1, -1},
};

/* 自定义布局 */
static const Layout layouts[] = {
    {"﬿", tile},      /* 主次栈 */
    {"﩯", magicgrid}, /* 网格 */
    {"", overview},    /* overview页面用的layout */
};

#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask

#define TAGKEYS(KEY, TAG, cmd1, cmd2)                                          \
  {ALTKEY, KEY, view, {.ui = 1 << TAG, .v = cmd1}},                            \
      {ALTKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG, .v = cmd2}},             \
      {ALTKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},

static Key keys[] = {
    /* modifier            key              function          argument */
    {MODKEY,
     XK_equal,
     togglesystray,
     {0}}, /* super +            |  切换 托盘栏显示状态 */

    {ALTKEY,
     XK_Tab,
     focusstack,
     {.i = +1}}, /* super tab          |  本tag内切换聚焦窗口 */
    {MODKEY,
     XK_k,
     focusstack,
     {.i = -1}}, /* super k           |  本tag内切换聚焦窗口 */
    {MODKEY,
     XK_j,
     focusstack,
     {.i = +1}}, /* super j         |  本tag内切换聚焦窗口 */

    {MODKEY,
     XK_bracketleft,
     viewtoleft,
     {0}}, /* super bracketleft         |  聚焦到左边的tag */
    {MODKEY,
     XK_bracketright,
     viewtoright,
     {0}}, /* super bracketright        |  聚焦到右边的tag */
    {MODKEY | ShiftMask,
     XK_bracketleft,
     tagtoleft,
     {0}}, /* super shift bracketleft   |  将本窗口移动到左边tag */
    {MODKEY | ShiftMask,
     XK_bracketright,
     tagtoright,
     {0}}, /* super shift bracketright  |  将本窗口移动到右边tag */

    {MODKEY, XK_Tab, toggleoverview, {0}}, /* super t            |  显示所有tag 或
                                      点击可以快速跳转到聚焦窗口的tag */

    {MODKEY,
     // XK_comma,
     XK_h,
     setmfact,
     {.f = -0.05}}, /* super h            |  缩小主工作区 */
    {MODKEY,
     // XK_period,
     XK_l,
     setmfact,
     {.f = +0.05}}, /* super l            |  放大主工作区 */

    {MODKEY, XK_m, hidewin, {0}}, /* super m            |  隐藏 窗口 */
    {MODKEY | ShiftMask,
     XK_m,
     restorewin,
     {0}}, /* super shift m      |  取消隐藏 窗口 */

    {MODKEY | ShiftMask,
     XK_Return,
     zoom,
     {0}}, /* super shift enter  |  将当前聚焦窗口置为主窗口 */

    {MODKEY,
     XK_f,
     togglefloating,
     {0}}, /* super f            |  开启/关闭 聚焦目标的float模式 */
    {MODKEY | ShiftMask,
     XK_f,
     toggleallfloating,
     {0}}, /* super shift f      |  开启/关闭 全部目标的float模式 */
    {ALTKEY, XK_f, fullscreen, {0}}, /* super f            |  开启/关闭 全屏 */
    {MODKEY | ShiftMask,
     XK_b,
     togglebar,
     {0}}, /* super shift b      |  开启/关闭 状态栏 */
    {MODKEY,
     XK_e,
     incnmaster,
     {.i = +1}}, /* super e            |  改变主工作区窗口数量 (1 2中切换) */

    // 目前还没有这个需求
    // {MODKEY,
    //  XK_b,
    //  focusmon,
    //  {.i = +1}}, /* super b            |  光标移动到另一个显示器 */
    // {MODKEY | ShiftMask,
    //  XK_b,
    //  tagmon,
    //  {.i = +1}}, /* super shift b      |  将聚焦窗口移动到另一个显示器 */

    {MODKEY, XK_q, killclient, {0}}, /* super q            |  关闭窗口 */
    {MODKEY | ControlMask,
     XK_F12,
     quit,
     {0}}, /* super ctrl f12     |  退出dwm */

    {MODKEY | ShiftMask,
     XK_space,
     selectlayout,
     {.v = &layouts[1]}}, /* super shift space  |  切换到网格布局 */
    {MODKEY,
     XK_o,
     showonlyorall,
     {0}}, /* super o            |  切换 只显示一个窗口 / 全部显示 */

    {MODKEY | ControlMask,
     XK_equal,
     setgap,
     {.i = -6}}, /* super ctrl =      |  窗口增大 */
    {MODKEY | ControlMask,
     XK_minus,
     setgap,
     {.i = +6}}, /* super ctrl -      |  窗口减小 */
    {MODKEY | ControlMask,
     XK_space,
     setgap,
     {.i = 0}}, /* super ctrl space   |  窗口重置 */

    {MODKEY | ControlMask,
     XK_k,
     movewin,
     {.ui = UP}}, /* super ctrl k      |  移动窗口 */
    {MODKEY | ControlMask,
     XK_j,
     movewin,
     {.ui = DOWN}}, /* super ctrl j    |  移动窗口 */
    {MODKEY | ControlMask,
     XK_h,
     movewin,
     {.ui = LEFT}}, /* super ctrl h    |  移动窗口 */
    {MODKEY | ControlMask,
     XK_l,
     movewin,
     {.ui = RIGHT}}, /* super ctrl l   |  移动窗口 */

    {MODKEY | Mod1Mask,
     XK_k,
     resizewin,
     {.ui = V_REDUCE}}, /* super alt k      |  调整窗口 */
    {MODKEY | Mod1Mask,
     XK_j,
     resizewin,
     {.ui = V_EXPAND}}, /* super alt j    |  调整窗口 */
    {MODKEY | Mod1Mask,
     XK_h,
     resizewin,
     {.ui = H_REDUCE}}, /* super alt h    |  调整窗口 */
    {MODKEY | Mod1Mask,
     XK_l,
     resizewin,
     {.ui = H_EXPAND}}, /* super alt l   |  调整窗口 */

    /* spawn + SHCMD 执行对应命令 */
    {MODKEY, XK_Return, spawn, SHCMD("kitty")},
    {MODKEY | ShiftMask, XK_a, spawn, SHCMD("flameshot")},
    {MODKEY, XK_space, spawn,
     SHCMD("rofi -no-config -no-lazy-grab -show drun -modi drun -theme "
           "~/.config/awesome/rofi/launcher.rasi")},
    {MODKEY, XK_p, spawn,
     SHCMD("rofi -no-config -no-lazy-grab -show window -modi drun -theme "
           "~/.config/awesome/rofi/launcher.rasi")},
    {MODKEY, XK_u, spawn, SHCMD("~/.config/polybar/script/sysmenu")},
    /* set volume sound  supre shift up/down */
    {MODKEY | ShiftMask, XK_Up, spawn,
     SHCMD("amixer -q set Master 5%+ unmute")},
    {MODKEY | ShiftMask, XK_Down, spawn,
     SHCMD("amixer -q set Master 5%- unmute")},
    /* set light super ctrl up/down */
    {MODKEY | ControlMask, XK_Up, spawn, SHCMD("light -A 10")},
    {MODKEY | ControlMask, XK_Down, spawn, SHCMD("light -U 10")},
    {ShiftMask | ControlMask, XK_c, spawn,
     SHCMD("xclip -o | xclip -selection c")},

    /* super key : 跳转到对应tag */
    /* super shift key : 将聚焦窗口移动到对应tag */
    /* 若跳转后的tag无窗口且附加了cmd1或者cmd2就执行对应的cmd */
    /* key tag cmd1 cmd2 */
    TAGKEYS(XK_1, 0, 0, 0) TAGKEYS(XK_2, 1, 0, 0) TAGKEYS(XK_3, 2, 0, 0)
    TAGKEYS(XK_4, 3, 0, 0) TAGKEYS(XK_5, 4, 0, 0) TAGKEYS(XK_6, 5, 0, 0)
    TAGKEYS(XK_7, 6, 0, 0) TAGKEYS(XK_8, 7, 0, 0) TAGKEYS(XK_9, 8, 0, 0)
    TAGKEYS(XK_c, 9, "google-chrome-stable", "google-chrome-stable")
    TAGKEYS(XK_m, 10, "music", "music")
    TAGKEYS(XK_0, 11, "tim", "tim")
    TAGKEYS(XK_w, 12, "wechat", "wechat")
    TAGKEYS(XK_o, 13, "obsidian", "obsidian")};

static Button buttons[] = {
    /* click               event mask       button            function argument
     */
    {ClkStatusText, 0, Button1, spawn,
     SHCMD("~/scripts/app-starter.sh fkitty")}, // 左键        |  点击状态栏   |
                                             // 打开float st
    {ClkWinTitle,
     0,
     Button1,
     hideotherwins,
     {0}}, // 左键        |  点击标题     |  隐藏其他窗口仅保留该窗口
    {ClkWinTitle,
     0,
     Button3,
     togglewin,
     {0}}, // 右键        |  点击标题     |  切换窗口显示状态
    {ClkTagBar, 0, Button1, view, {0}}, // 左键        |  点击tag      | 切换tag
    {ClkTagBar,
     0,
     Button3,
     toggleview,
     {0}}, // 右键        |  点击tag      |  切换是否显示tag
    {ClkClientWin,
     MODKEY,
     Button1,
     movemouse,
     {0}}, // super+左键  |  拖拽窗口     |  拖拽窗口
    {ClkClientWin,
     MODKEY,
     Button3,
     resizemouse,
     {0}}, // super+右键  |  拖拽窗口     |  改变窗口大小
    {ClkTagBar,
     MODKEY,
     Button1,
     tag,
     {0}}, // super+左键  |  点击tag      |  将窗口移动到对应tag
};
