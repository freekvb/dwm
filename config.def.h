/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "Hack:pixelsize=14";

#define wal "/home/fvb/.cache/wal/colors-wal-dwm.h"

#if __has_include(wal)
#include wal
#else
static const char col_gray1[]       = "#1c1b1b";
static const char col_gray2[]       = "#323131";
static const char col_gray3[]       = "#ebe5d9";
static const char col_gray4[]       = "#1c1b1b";
static const char col_gray5[]       = "#728B99";
static const char col_cyan[]        = "#E4CEAB";
static const char *colors[][3]      = {

    /*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray5 },
	[SchemeSel]  = { col_gray4, col_gray2, col_cyan  },
};
#endif

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class    instance    title               tags mask   isfloating  isterminal  noswallow   monitor */
	{ "St",     NULL,       NULL,               0,          0,          1,          0,          -1 },
    { NULL,     NULL,       "scratchpad",       0,          1,          1,          0,          -1,},
	{ NULL,     NULL,       "Event Tester",     0,          0,          0,          1,          -1 },  /* xev */
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0;    /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },           /* first entry is default */
	{ "><>",      NULL },           /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[]  = "scratchpad";
static const char *scratchpadcmd[]  = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include "movestack.c"

static const Key keys[] = {

 /* modifier                        key             function            argument */

	{ MODKEY,                       XK_space,       spawn,              {.v = termcmd } },
	{ Mod4Mask,                     XK_Return,      spawn,              {.v = dmenucmd } },
	{ MODKEY,                       XK_d,           togglescratch,      {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,           togglebar,          {0} },
	{ MODKEY,                       XK_j,           focusstack,         {.i = +1 } },
	{ MODKEY,                       XK_k,           focusstack,         {.i = -1 } },
	{ MODKEY,                       XK_i,           incnmaster,         {.i = +1 } },
	{ MODKEY,                       XK_o,           incnmaster,         {.i = -1 } },
	{ Mod4Mask,                     XK_h,           setmfact,           {.f = -0.05} },
	{ Mod4Mask,                     XK_l,           setmfact,           {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,           movestack,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,           movestack,          {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return,      zoom,               {0} },
	{ MODKEY,                       XK_Tab,         view,               {0} },
	{ MODKEY,                       XK_l,           shiftviewclients,   { .i = +1 } },
	{ MODKEY,                       XK_h,           shiftviewclients,   { .i = -1 } },
	{ Mod4Mask,                     XK_w,           killclient,         {0} },
	{ MODKEY|ControlMask,           XK_t,           setlayout,          {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_f,           setlayout,          {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_m,           setlayout,          {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_space,       setlayout,          {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_space,       togglefloating,     {0} },
	{ MODKEY,                       XK_0,           view,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,           tag,                {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_comma,       focusmon,           {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,      focusmon,           {.i = +1 } },
	{ MODKEY|ControlMask,           XK_comma,       tagmon,             {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,      tagmon,             {.i = +1 } },

    { Mod4Mask,                     XK_q,           spawn,              SHCMD("qutebrowser") },
    { Mod4Mask,                     XK_c,           spawn,              SHCMD("chromium --kiosk") },
    { Mod4Mask,                     XK_f,           spawn,              SHCMD("firefox_fs") },
    { MODKEY,                       XK_p,           spawn,              SHCMD("clipmenu -i") },
    { Mod4Mask,                     XK_comma,       spawn,              SHCMD("pamixer --allow-boost -d 5 && notify-send --hint=string:x-dunst-stack-tag:volume: $(vol)") },
    { Mod4Mask,                     XK_period,      spawn,              SHCMD("pamixer --allow-boost -i 5 && notify-send --hint=string:x-dunst-stack-tag:volume: $(vol)") },
    { Mod4Mask,                     XK_slash,       spawn,              SHCMD("pamixer --allow-boost --set-volume 30") },
    { Mod4Mask,                     XK_m,           spawn,              SHCMD("pamixer -t") },
    { MODKEY,                       XK_x,           spawn,              SHCMD("mocp -M $XDG_CONFIG_HOME/moc -G") },
    { MODKEY,                       XK_z,           spawn,              SHCMD("pamixer --allow-boost --set-volume 30 && xset dpms force off") },
    { Mod4Mask,                     XK_e,           spawn,              SHCMD("dmenu-emoji") },
    { Mod4Mask,                     XK_p,           spawn,              SHCMD("passmenu") },
    { Mod4Mask,                     XK_r,           spawn,              SHCMD("rofi -show calc -modi calc -no-show-match -no-sort &") },
    { MODKEY,                       XK_v,           spawn,              SHCMD("yt_mpv") },
    { MODKEY,                       XK_y,           spawn,              SHCMD("ytfzf -Dlm") },
    { MODKEY|ShiftMask,             XK_y,           spawn,              SHCMD("playerctl play-pause") },
    { Mod4Mask,                     XK_x,           spawn,              SHCMD("scrot -F 'MNQZ2024_%Y-%m-%d_%H-%M-%S.png' -e 'mv $f ~/Notes/trades/tp/' && dunstify 'screenshot  >>  tp'") },

	TAGKEYS(                        XK_1,                               0)
	TAGKEYS(                        XK_2,                               1)
	TAGKEYS(                        XK_3,                               2)
	TAGKEYS(                        XK_4,                               3)
	TAGKEYS(                        XK_5,                               4)
	TAGKEYS(                        XK_6,                               5)
	TAGKEYS(                        XK_7,                               6)
	TAGKEYS(                        XK_8,                               7)
	TAGKEYS(                        XK_9,                               8)

	{ Mod4Mask|ShiftMask,           XK_q,           quit,               {0} },
};

/* mouse button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */

static const Button buttons[] = {

 /* click                   event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

