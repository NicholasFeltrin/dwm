/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 1; 	/*1 means swallow floating windows by default*/
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "monospace:size=10";
static char dmenufont[]       = "monospace:size=10";
static const char *fonts[]          = { font };
static const char col_gray1[]       = "#1d2021";
static const char col_gray2[]       = "#ebdbb2";
static const char col_gray3[]       = "#928374";
static const char col_gray4[]       = "#8ec07c";
static const char col_cyan[]        = "#fabd2f";	//selected and top bar
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	//[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	//[SchemeSel]  = { col_gray1, col_gray3, col_gray3  },
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_gray1, col_gray3  },
 };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */

	/**/
	/*Graphical Environment*/
	/**/
	TAGKEYS(                        XK_1,                     	0)
	TAGKEYS(                        XK_2,                     	1)
	TAGKEYS(                        XK_3,                     	2)
	TAGKEYS(                        XK_4,                     	3)
	TAGKEYS(                        XK_5,                     	4)
	TAGKEYS(                        XK_6,                     	5)
	TAGKEYS(                        XK_7,                     	6)
	TAGKEYS(                        XK_8,                     	7)
	TAGKEYS(                        XK_9,                     	8)
	{ MODKEY,			XK_0,		togglesticky,	{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		view,		{.ui = ~0 } },
	{ MODKEY,                       XK_j,     	focusstack,    	{.i = +1 } },
	{ MODKEY,                       XK_k,     	focusstack,    	{.i = -1 } },
	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY,			XK_q,	  	killclient,	{0} },
	{ MODKEY|ControlMask|ShiftMask, XK_Escape,     	quit,          	{0} },

	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} }, /* tile */
	/* { MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} },*/ /* bstack */
	/* { MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} },*/ /* spiral */
	/* { MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} },*/ /* dwindle */
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[5]} }, /* monocle */
	/*{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[6]} },*/ /* centeredmaster */
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	/* { MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[8]} },*/

	{ MODKEY,			XK_s,		togglefloating,	{0} },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	/* { MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} }, */

	{ MODKEY,			XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,     {.i = -1 } },

	{ MODKEY,			XK_a,		togglegaps,	{0} },
	{ MODKEY|ShiftMask,		XK_a,		defaultgaps,	{0} },
	{ MODKEY,			XK_z,		incrgaps,	{.i = +3 } },
	{ MODKEY,			XK_x,		incrgaps,	{.i = -3 } },

	{ MODKEY,			XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY,			XK_l,		setmfact,      	{.f = +0.05} },

	{ MODKEY,			XK_d,		spawn,      	SHCMD("dmenurun") },
	{ MODKEY|ShiftMask,		XK_semicolon,	spawn,      	SHCMD("dmenuunicode") },
	{ MODKEY,			XK_F1,		spawn,      	SHCMD("dmenumount") },
	{ MODKEY|ShiftMask,		XK_F1,		spawn,      	SHCMD("dmenuumount") },

	/**/
	/*Media and System*/
	/**/
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("amixer -c 2 set 'Master' toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XK_F9,           		spawn,		SHCMD("amixer -c 2 set 'Master' toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("amixer -c 2 set 'Master' 5%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XK_F11,	spawn,		SHCMD("amixer -c 2 set 'Master' 5%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("amixer -c 2 set 'Master' 5%-; kill -44 $(pidof dwmblocks)") },
	{ 0, XK_F10,	spawn,		SHCMD("amixer -c 2 set 'Master' 5%-; kill -44 $(pidof dwmblocks)") },
  
	{ 0, XK_F2,	spawn,		SHCMD("xbacklight -dec 5") },
	{ 0, XK_F3,	spawn,		SHCMD("xbacklight -inc 5") },

	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ MODKEY, XK_F5,		spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
	{ MODKEY, XK_F6,		spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc toggle") },
	{ MODKEY, XK_F7,		spawn,		SHCMD("mpc toggle") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc repeat") },
	{ MODKEY, XK_F8,		spawn,		SHCMD("mpc repeat") },
	{ MODKEY,			XK_comma,	spawn,		SHCMD("mpc prev") },
	{ MODKEY,			XK_period,	spawn,		SHCMD("mpc next") },
	{ MODKEY,			XK_p,			spawn,		SHCMD("mpc toggle") },
	{ MODKEY,			XK_Left,		spawn,		SHCMD("mpc seek -10") },
	{ MODKEY|ShiftMask,		XK_Left,		spawn,		SHCMD("mpc seek -60") },
	{ MODKEY,			XK_Right,		spawn,		SHCMD("mpc seek +10") },
	{ MODKEY|ShiftMask,		XK_Right,		spawn,		SHCMD("mpc seek +60") },

	{ 0, 	  XK_Print,	spawn,	SHCMD("maim $HOME/media/pictures/screenshots/screenshot_$(date '+%y%m%d_%H%M_%S').png") },
	{ MODKEY, XK_Print,	spawn,	SHCMD("maim -s $HOME/media/pictures/screenshots/screenshot_$(date '+%y%m%d_%H%M_%S').png") },

	{ ControlMask,			XK_y,			spawn,		SHCMD("xclip -o | xclip -sel clip") },
	//{ ControlMask,			XK_p,			spawn,		SHCMD("xdotool type '$(xclip -o -sel clip)'") },

	/**/
	/*Application*/
	/**/
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY,			XK_w,		spawn,		SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,		XK_w,		spawn,		SHCMD("tor-browser") },
	{ MODKEY,			XK_e,		spawn,		SHCMD("$EMAIL") },
	{ MODKEY,			XK_v,		spawn,		SHCMD("virt-manager") },
	{ MODKEY,			XK_r,		spawn,		SHCMD(TERMINAL " -e htop") },
	{ MODKEY,			XK_m,		spawn,		SHCMD(TERMINAL " -e ncmpcpp") },
	{ MODKEY|ShiftMask,		XK_m,		spawn,		SHCMD(TERMINAL " -e alsamixer") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

