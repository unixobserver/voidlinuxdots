/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static unsigned int borderpx  = 0;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    =  20;       /* horiz inner gap between windows */
static unsigned int gappiv    =  20;       /* vert inner gap between windows */
static unsigned int gappoh    =  20;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    =  20;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 0;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char *fonts[]          = { "Spleen:size=14", "Symbola:pixelsize=16:antialias=true:autohint=true"  };
static char normbgcolor[]           = "#000000";
static char normbordercolor[]       = "#222222";
static char normfgcolor[]           = "#D9E0EE";
static char selfgcolor[]            = "#c0c0c0";
static char selbordercolor[]        = "#333333";
static char selbgcolor[]            = "#000000";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "splaunch", "-f", "monospace:size=10", "-g", "50x20", "-e", "launcher",  NULL };
const char *spcmd3[] = {TERMINAL, "-n", "sppower", "-f", "monospace:size=10", "-g", "30x10", "-e", "power",  NULL };
const char *spcmd4[] = {TERMINAL, "-n", "spmount", "-f", "monospace:size=10", "-g", "30x10", "-e", "usbmount",  NULL };
const char *spcmd5[] = {TERMINAL, "-n", "spumount", "-f", "monospace:size=10", "-g", "30x10", "-e", "usbunmount",  NULL };
const char *spcmd6[] = {TERMINAL, "-n", "spvids", "-f", "monospace:size=10", "-g", "50x10", "-e", "vids",  NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"splaunch",    spcmd2},
	{"sppower",     spcmd3},
	{"spmount",     spcmd4},
	{"spumount",    spcmd5},
	{"spvids",      spcmd6},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "QjackCtl", NULL,       NULL,       	    1 << 9,       1,           0,         0,        -1 },
	{ TERMCLASS,  NULL,       NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
	{ NULL,      "spterm",     NULL,       	    SPTAG(0),     1,           1,         0,        -1 },
	{ NULL,      "splaunch",    NULL,           SPTAG(1),     1,           1,         0,        -1 },
	{ NULL,      "sppower",     NULL,           SPTAG(2),     1,           1,         0,        -1 },
	{ NULL,      "spmount",     NULL,           SPTAG(3),     1,           1,         0,        -1 },
	{ NULL,      "spumount",     NULL,          SPTAG(4),     1,           1,         0,        -1 },
	{ NULL,      "spvids",      NULL,           SPTAG(5),     1,           1,         0,        -1 },
};

/* layout(s) */
static float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "[D]",	deck },			/* Master on left, slaves in monocle-like mode on right */
	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define HOLDKEY 0xffeb // replace 0 with the keysym to activate holdbar
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_Down,  ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_Up,    ACTION##stack,	{.i = INC(-1) } }, \
        { MOD,	XK_Left,  ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_Right, ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
/*	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \ */
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,			XK_grave,	spawn,	SHCMD("scrot 'void_%d-%m-%Y_$wx$h.png'") },
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,			XK_BackSpace,	spawn,		SHCMD("slock") },
	{ MODKEY|ShiftMask,		XK_BackSpace,	spawn,		SHCMD(TERMINAL " -e orca") },
	{ 0,                            HOLDKEY,  	holdbar,        {0} },
	{ MODKEY,			XK_Tab,		view,		{0} },
	{ MODKEY,			XK_v,		spawn,		SHCMD("vibe ") },
	{ MODKEY|ShiftMask,		XK_v,		spawn,		SHCMD("vibe") },
       { MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY|ShiftMask,		XK_q,		spawn, 	        SHCMD("power")},
	{ MODKEY,			XK_w,		spawn,		SHCMD("google-chrome-stable") },
	{ MODKEY,			XK_e,		spawn,		SHCMD("st -e fff") },
	{ MODKEY|ShiftMask,		XK_e,		spawn,		SHCMD("pcmanfm") },
	{ MODKEY,			XK_i,		spawn,		SHCMD("st -e htop") },
	{ MODKEY|ShiftMask,		XK_i,		spawn,		SHCMD(TERMINAL " -e btop") },
	{ MODKEY,			XK_o,		spawn,		SHCMD(TERMINAL " -e orca") },
	{ MODKEY|ShiftMask,		XK_o,		spawn,		SHCMD("lmms") },
        { MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,		setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_r,		setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_r,		setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,			XK_Print,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Print,		incnmaster,     {.i = -1 } }, 
	{ MODKEY,			XK_bracketleft,		spawn,		SHCMD("voldown") },
	{ MODKEY|ShiftMask,		XK_bracketleft,		spawn,		SHCMD("execscripts") },
	{ MODKEY,			XK_bracketright,	spawn,		SHCMD("volup") },
	{ MODKEY|ShiftMask,		XK_bracketright,	spawn,		SHCMD("wall-select") },
	{ MODKEY,			XK_backslash,		view,		{0} },
	{ MODKEY,			XK_p,		spawn,		SHCMD("nsxiv -b -t ~/Pictures/* ") },
	{ MODKEY|ShiftMask,		XK_p,		spawn,		SHCMD("st -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_a,		togglegaps,	{0} },
	{ MODKEY|ShiftMask,		XK_a,		defaultgaps,	{0} },
	{ MODKEY,			XK_s,		togglesticky,	{0} },
	{ MODKEY,			XK_d,	        spawn,      SHCMD("dmenu_run") },
	{ MODKEY|ShiftMask,	XK_d,			spawn,		SHCMD("st -e ncdu") },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	{ MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[8]} },
	{ MODKEY,			XK_g,		shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_g,		shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY,			XK_l,		setmfact,      	{.f = +0.05} },
	{ MODKEY,			XK_semicolon,	shiftview,	{ .i = 1 } },
	{ MODKEY|ShiftMask,		XK_semicolon,	shifttag,	{ .i = 1 } },
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return,	togglescratch,	{.ui = 0} },

	{ MODKEY,			XK_z,		incrgaps,	{.i = +3 } },
	{ MODKEY,			XK_x,		incrgaps,	{.i = -3 } },
	{ MODKEY,			XK_b,		togglebar,	{0} },
	{ MODKEY|ShiftMask,		XK_m,		spawn,		SHCMD("movies") }, 
	{ MODKEY|ShiftMask,		XK_n,		spawn,		SHCMD(TERMINAL " -e vim ~/Documents/notes/notes.md") },
	{ MODKEY,			XK_n,		spawn,		SHCMD(TERMINAL " -e newsboat; pkill -RTMIN+6 dwmblocks") },
	{ MODKEY,			XK_m,		spawn,		SHCMD("st -e ncmpcpp -S visualizer") },
	{ MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_Page_Up,	shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_Page_Down,	shiftview,	{ .i = +1 } },
	{ MODKEY|ShiftMask,		XK_Page_Down,	shifttag,	{ .i = +1 } },
	{ MODKEY,			XK_F1,		spawn,		SHCMD("mpv  ~/Videos/movies") },
	{ MODKEY,			XK_F5,		spawn,          SHCMD("doas mount /dev/sdb1 ~/.usb & st -e fff ~/.usb & notify-send 'usb mount' ") },
	{ MODKEY|ShiftMask,		XK_F5,		spawn,          SHCMD("doas umount ~/.usb  && notify-send 'usb unmount' ") },
	{ MODKEY,			XK_F6,		spawn,		SHCMD("st -e rec") },
	{ MODKEY,			XK_F7,		spawn,		SHCMD("st -e killrec") },
	{ MODKEY,			XK_F8,		spawn,		SHCMD("") },
	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },
        { MODKEY|ShiftMask,		XK_F12,	tagmon,		{.i = +1 } },
        { MODKEY,		        XK_F12,	focusmon,	{.i = +1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e vim ~/.local/suckless/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};
