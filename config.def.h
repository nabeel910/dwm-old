/* See LICENSE file for copyright and license details. */

#define TERMINAL "alacritty"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "RobotoMono Nerd Font Mono:size=11","Noto Color Emoji:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "RobotoMono Nerd Font Mono:size=11";
static const char searchsymbol[]    = " ";
static const char highpriority[]    = "chromium,librewolf,animeseries,whatsapp,nitrogen,lxappearance,lxtask,pcmanfm,thunar,bitwarden,writer,impress,transmission-gtk";
static const char col_gray1[]       = "#191724";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#ABB2BF";
static const char col_gray4[]       = "#e0def4";
static const char col_cyan[]        = "#31748f";

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
	/* class      			instance    title       tags mask     	     switchtotag          isfloating   monitor */
	{ "Pavucontrol",      		NULL,        NULL,         0,                    0,                  1,           -1 },
	{ "Blueman-manager",      	NULL,        NULL,         0,                    0,                  1,           -1 },
	{ "LibreWolf",        		NULL,        NULL,         1 ,                   1,                  0,           -1 },
	{ "mpv",              		NULL,        NULL,         1 << 2,               1,                  0,           -1 },
	{ "WebApp-AnimeSeries3352",     NULL,        NULL,         1 << 2,               1,                  0,           -1 },
	{ "WebApp-Whatsapp6569", 	NULL,        NULL,         1 << 5,               1,                  0,           -1 },
	{ "Transmission-gtk",  		NULL,        NULL,         1 << 7,      	 1,                  0,           -1 },
	{ "tremc",  			NULL,        NULL,         1 << 7,      	 1,                  0,           -1 },
	{ "pacman-packages",   		NULL,        NULL,         1 << 8,      	 1,                  0,           -1 },
	{ "Gnomecast",         		NULL,        NULL,         0,      	      	 0,                  1,           -1 }
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
	{ MODKEY,                       	KEY,      view,           {.ui = 1 << TAG} }, \
	{ Mod1Mask|ControlMask,         	KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Mod1Mask,		        	KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,			KEY,      tag, 	          {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,			KEY,      view,		  {.ui = 1 << TAG} }, \
	{ Mod1Mask|ControlMask|ShiftMask, 	KEY,    toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-p", searchsymbol, "-hp", highpriority, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

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
//	{ MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,             		XK_f,      fullscreen,     {0} },
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


/*apps launch with superkey*/	
	{ MODKEY,			XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,			XK_p,      spawn,          SHCMD("keepmenu") },
	{ MODKEY,			XK_w,      spawn,          SHCMD("librewolf") },
	{ MODKEY,			XK_c,      spawn,          SHCMD("chromium") },
	{ MODKEY,			XK_e,      spawn,          SHCMD("dmenuemoji") },
	{ MODKEY,		     	XK_g,      spawn,          SHCMD("= --dmenu='dmenu -i -l 3'") },
	{ MODKEY,     			XK_t,      spawn,          SHCMD(TERMINAL " --class tremc -t tremc  -e tremc") },
	{ MODKEY,			XK_n,      spawn,          SHCMD("TERMINAL " -e lf") },
	{ MODKEY,			XK_r,      spawn,          SHCMD(TERMINAL " -e newsboat") },
	{ MODKEY,			XK_a,      spawn,          SHCMD("animeseries") },
	{ MODKEY,			XK_m,      spawn,          SHCMD(TERMINAL " -e cmus") },
	{ MODKEY,			XK_x,      spawn,          SHCMD("clipmenu -i -p ' '") },
	{ MODKEY,			XK_slash,  spawn,          SHCMD("dunst-music-notification") },


//apps launch with super+shift
	{ MODKEY|ShiftMask,     	XK_w,      spawn,          SHCMD("networkmanager_dmenu") },
	{ MODKEY|ShiftMask,     	XK_n,      spawn,          SHCMD("pmcmanfm") },
	{ MODKEY|ShiftMask,     	XK_r,      spawn,          SHCMD("randomwall") },
	{ MODKEY|ShiftMask,     	XK_p,      spawn,          SHCMD(TERMINAL " --class pacman-packages,pacman-packages -t update  -e paru -Syu") },
	{ MODKEY|ShiftMask,     	XK_v,      spawn,          SHCMD(TERMINAL " --class set-bg -t set-bg  -e viewwalls") },
	{ MODKEY|ShiftMask,		XK_k,      spawn,          SHCMD("pirokit") },

//apps launch with ctrl+alt
	{ Mod1Mask|ControlMask,		XK_w,      spawn,          SHCMD("librewolf --private-window") },
	{ Mod1Mask|ControlMask,		XK_c,      spawn,          SHCMD("chromium --incognito") },
	{ Mod1Mask|ControlMask,		XK_l,      spawn,          SHCMD("slock") },
	{ Mod1Mask|ControlMask,		XK_e,      spawn,          SHCMD("dsession") },

// function buttons
	{ 0, XF86XK_AudioMute,		           spawn,     	   SHCMD("pamixer -t && sound-notification && kill -39 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	           spawn,	   SHCMD("pamixer --allow-boost -i 10 && sound-notification && kill -39 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,		   spawn,	   SHCMD("pamixer --allow-boost -d 10 && sound-notification && kill -39 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		           spawn,	   SHCMD("playerctl --player=playerctld previous && dunst-music-notification") },
	{ 0, XF86XK_AudioNext,		           spawn,	   SHCMD("playerctl --player=playerctld next && dunst-music-notification") },
	{ 0, XF86XK_AudioPlay,        	           spawn,	   SHCMD("playerctl --player=playerctld play-pause && dunst-music-notification") },
	{ 0, XF86XK_MonBrightnessUp,	           spawn,	   SHCMD("xbacklight -inc 15 && brightness") },
	{ 0, XF86XK_MonBrightnessDown,	           spawn,	   SHCMD("xbacklight -dec 15 && brightness") },
	{ 0, XK_Print,			           spawn,          SHCMD("dmenu-screenshot") },
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

