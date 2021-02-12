/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 35;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "SFMono Nerd Font:size=13","Noto Color Emoji:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "SFMono Nerd Font:size=13";
static const char searchsymbol[]    = " ";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#0a6cf5";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     switchtotag    isfloating   monitor */
	{ "Galculator",       NULL,               NULL,         0,                    0,                  1,           -1 },
	{ "Pavucontrol",      NULL,               NULL,         0,                    0,                  1,           -1 },
	{ "LibreWolf",        NULL,               NULL,         1 ,                   1,                  0,           -1 },
//	{ "firefox",          NULL,               NULL,         1 ,                   1,                  0,           -1 },
	{ "mpv",              NULL,               NULL,         1 << 2,               3,                  0,           -1 },
	{ "vlc",              NULL,               NULL,         1 << 2,               3,                  0,           -1 },
	{ "WebApp-AnimeSeries3352",  NULL,        NULL,         1 << 2,               3,                  0,           -1 },
	{ "Transmission-gtk",  NULL,      	  NULL,         1 << 7,      	      8,                  0,           -1 },
	{ "pacman-packages",   NULL,      	  NULL,         1 << 8,      	      9,                  0,           -1 },
	{ "Gnomecast",         NULL,      	  NULL,         0,      	      0,                  1,           -1 }
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

#include <X11/XF86keysym.h>

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ Mod1Mask|ControlMask,         KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Mod1Mask,		        KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,		KEY,      tag, 	          {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,		KEY,      view,		  {.ui = 1 << TAG} }, \
	{ Mod1Mask|ControlMask|ShiftMask, KEY,    toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-p", searchsymbol, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
//	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
//	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
//	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
//	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
//	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
//	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
//	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
//	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,		        XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
//	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
//	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
//	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },


/*apps launch with superkey*/	
	{ MODKEY,			XK_d,      spawn,          {.v = dmenucmd } },
//	{ MODKEY,			XK_d,      spawn,          SHCMD("rofi -show drun -theme ~/.config/rofi/themes/rmenu.rasi") },
//	{ MODKEY,			XK_d,      spawn,          SHCMD("j4-dmenu") },
	{ MODKEY,			XK_w,      spawn,          SHCMD("librewolf") },
//	{ MODKEY,			XK_w,      spawn,          SHCMD("firefox") },
	{ MODKEY,			XK_c,      spawn,          SHCMD("chromium") },
	{ MODKEY,			XK_e,      spawn,          SHCMD("dmenuemoji") },
	{ MODKEY,		     	XK_g,      spawn,          SHCMD("galculator") },
	{ MODKEY,			XK_n,      spawn,          SHCMD("pcmanfm") },
	{ MODKEY,			XK_x,      spawn,          SHCMD("clipmenu -i -p ' '") },
	{ MODKEY,			XK_slash,      spawn,      SHCMD("dunst-music-notification") },


//apps launch with super+shift
	{ MODKEY|ShiftMask,     	XK_w,      spawn,          SHCMD("networkmanager_dmenu") },
	{ MODKEY|ShiftMask,     	XK_p,      spawn,          SHCMD("alacritty --class Alacritty,pacman-packages -e sudo pacman -Syu") },
	{ MODKEY|ShiftMask,		XK_e,      spawn,          SHCMD("dmenuprompt 'Restart dwm?' 'killall dwm'") },

//apps launch with ctrl+alt
	{ Mod1Mask|ControlMask,		XK_w,      spawn,          SHCMD("/usr/lib/firefox/firefox --private-window") },
	{ Mod1Mask|ControlMask,		XK_c,      spawn,          SHCMD("/usr/bin/chromium --incognito") },
	{ Mod1Mask|ControlMask,		XK_l,      spawn,          SHCMD("slock") },
	{ Mod1Mask|ControlMask,		XK_o,      spawn,          SHCMD("dmenuprompt 'Reboot computer?' 'systemctl reboot'") },
	{ Mod1Mask|ControlMask,		XK_s,      spawn,          SHCMD("dmenuprompt 'Suspend computer?' 'systemctl suspend'") },
	{ Mod1Mask|ControlMask,		XK_p,      spawn,          SHCMD("dmenuprompt 'Shutdown computer?' 'systemctl poweroff'") },
	{ Mod1Mask|ControlMask,		XK_e,      spawn,          SHCMD("dmenuprompt 'Logout?' 'killall xinit'") },

// function buttons
	{ 0, XF86XK_AudioMute,		           spawn,     	   SHCMD("/usr/bin/pulseaudio-ctl mute && sound-notification && kill -39 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	           spawn,	   SHCMD("/usr/bin/pulseaudio-ctl up && sound-notification && kill -39 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,		   spawn,	   SHCMD("/usr/bin/pulseaudio-ctl down && sound-notification && kill -39 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		           spawn,	   SHCMD("playerctl --player=playerctld previous && dunst-music-notification") },
	{ 0, XF86XK_AudioNext,		           spawn,	   SHCMD("playerctl --player=playerctld next && dunst-music-notification") },
	{ 0, XF86XK_AudioPlay,        	           spawn,	   SHCMD("playerctl --player=playerctld play-pause && dunst-music-notification") },
	{ 0, XF86XK_MonBrightnessUp,	           spawn,	   SHCMD("xbacklight -inc 15 && brightness") },
	{ 0, XF86XK_MonBrightnessDown,	           spawn,	   SHCMD("xbacklight -dec 15 && brightness") },
	{ 0, XK_Print,			           spawn,          SHCMD("flameshot full -p ~/Pictures/screenshots/") },
	{ ShiftMask, XK_Print,			   spawn,          SHCMD("flameshot gui") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
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

