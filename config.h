/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int attachbelow        = 1;        /* 1 means attach after the currently active window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "JetBrainsMono NF:size=12" };
static const char dmenufont[]       = "JetBrainsMono NF:size=12";
static const char col_gray1[]       = "#2a2b2e";
static const char col_gray2[]       = "#5a5a66";
static const char col_gray3[]       = "#d2d6e8";
static const char col_gray4[]       = "#eceff4";
static const char col_cyan[]        = "#04471c";

static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1},
	[SchemeSel]  = { col_gray4, col_gray2,  col_gray2  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

	/* class		instance  	title           tags mask  isfloating  isterminal  noswallow  monitor */
  { "Gimp",         	NULL,     	NULL,		        0,          1,          0,           0,        -1 },
	{ "LibreWolf",    	NULL,     	NULL,           0,          0,          0,           0,        -1 },
  { "KeePassXC",	  	NULL,		    NULL,       	  0,	        0,	        0,           0,        -1 },
  { "discord",	  	  NULL,		    NULL,       	  1 << 8,	    0,	        0,           0,         0 },
	{ "st",           	NULL,     	NULL,           0,          0,          1,           0,        -1 },
  { "Pentablet",    	NULL,     	NULL,           0,          1,          0,           0,        -1 },
	{ NULL,           	NULL,     	"Event Tester", 0,          0,          0,           1,        -1 }, /* xev */
	{ NULL, NULL,     	"XBindKey: Hit a key",    	0,          0,          0,           1,        -1 }, 
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
/* OG */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

/* Custom*/
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[]  = { "librewolf", NULL };


#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
  /* Custom shortcuts */  
	{ 0,                            XK_Print,   spawn,          SHCMD ("flameshot gui --clipboard")},
  { MODKEY,                       XK_Print,   spawn,          SHCMD ("flameshot full -p $HOME/Pictures/Screenshots/")},
  { MODKEY|ControlMask,           XK_Print,   spawn,          SHCMD ("flameshot gui -p $HOME/Pictures/Screenshots/")},
  { ShiftMask,             XK_Print,   spawn,          SHCMD ("flameshot gui")},
  { MODKEY,                       XK_b,       spawn,          {.v = browsercmd } },
  { MODKEY|ControlMask,           XK_l,       spawn,          SHCMD ("slock")},
  { MODKEY,                       XK_o,       spawn,          SHCMD ("rofi -show run") },
  { Mod1Mask,                     XK_Tab,     spawn,          SHCMD ("rofi -show window") },
  { MODKEY,                       XK_y,       spawn,          SHCMD ("youtube-music")},
  { MODKEY,                       XK_q,       spawn,          SHCMD ("thunar")},
  
  /* Custom multimedia*/
  { 0, XF86XK_AudioMute,          spawn,  SHCMD ("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; pkill -RTMIN+8 dwmblocks") },
  { 0, XF86XK_AudioRaiseVolume,   spawn,  SHCMD ("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; pkill -RTMIN+8 dwmblocks") },
  { 0, XF86XK_AudioLowerVolume,   spawn,  SHCMD ("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; pkill -RTMIN+8 dwmblocks") },
  { 0, XF86XK_AudioMicMute,       spawn,  SHCMD ("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
  { 0, XF86XK_AudioNext,          spawn,  SHCMD ("playerctl next") },
  { 0, XF86XK_AudioPrev,          spawn,  SHCMD ("playerctl prev") },
  { 0, XF86XK_AudioPlay,          spawn,  SHCMD ("playerctl play-pause") },
  { 0, XF86XK_MonBrightnessUp,    spawn,  SHCMD ("light -A 5; pkill -RTMIN+12 dwmblocks") },
  { 0, XF86XK_MonBrightnessDown,  spawn,  SHCMD ("light -U 5; pkill  -RTMIN+12 dwmblocks") },
  { 0, XF86XK_Sleep,              spawn,  {.v = (const char*[]){ "sysact", NULL } } },
  { 0, XK_s,                      spawn,  {.v = (const char*[]){ "sysact", NULL } } },

  /* OG */
  { MODKEY,                       XK_p,      spawn,          SHCMD ("rofi -show drun") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	/*{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },*/
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	/*{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },*/
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

