/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
	"monospace:size=10"
};
static const char dmenufont[]       = "monospace:size=10";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
/* tagging */
static const char *tags[] = { "Eli", "Desmond", "Thea", "Charlie", "Pam", "Harper", "Sierra", "Olly" };
//static const char *tags[] = {"Unum", "Dual", "Tria", "Quad", "Pent", "Hexa", "Sept", "Octi"};
static const unsigned int gappx = 8; // Gap tiled, in pixels

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.75; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "I=",      tile },    /* first entry is default */
	{ "<>",      NULL },    /* no layout function means floating behavior */
	{ "[]",      monocle },
 	{ "I@",      spiral },
 	{ "I&",      dwindle },
	{ "++", gaplessgrid }
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define HYPERKEY Mod5Mask
#define SUPERKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "sakura", NULL };

#include "movestack.c"
#include "shiftview.c"
#define WINCONTROL "/home/dach/bin/wincontrol"

static Key keys[] = {
	/* modifier                     key        function        argument */
//Do not change first entry - it's used to map any key to WINCONTROL
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
{ ALTKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_Tab,    shiftview,           {1} },
{ MODKEY|ShiftMask,                       XK_Tab,    shiftview,           {-1} },
	{ MODKEY,             XK_c,      killclient,     {0} },
{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
{ MODKEY|ShiftMask, XK_f, togglefloating, {0}},
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
{ MODKEY, XK_g, setlayout, {.v = &layouts[5]} }, //grid layout
	{ MODKEY,                       XK_space,  prevlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  prevlayout, {0} }, //What should this do?
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
{ SUPERKEY|ShiftMask,                       XK_l,      spawn,       SHCMD("slock") },
{ HYPERKEY,                       XK_a,      spawn,     SHCMD("/home/dach/bin/wincontrol a") },
{ HYPERKEY,                       XK_b,      spawn,     SHCMD("/home/dach/bin/wincontrol b") },
{ HYPERKEY,                       XK_c,      spawn,     SHCMD("/home/dach/bin/wincontrol c") },
{ HYPERKEY,                       XK_d,      spawn,     SHCMD("/home/dach/bin/wincontrol d") },
{ HYPERKEY,                       XK_e,      spawn,     SHCMD("/home/dach/bin/wincontrol e") },
{ HYPERKEY,                       XK_f,      spawn,     SHCMD("/home/dach/bin/wincontrol f") },
{ HYPERKEY,                       XK_g,      spawn,     SHCMD("/home/dach/bin/wincontrol g") },
{ HYPERKEY,                       XK_h,      spawn,     SHCMD("/home/dach/bin/wincontrol h") },
{ HYPERKEY,                       XK_i,      spawn,     SHCMD("/home/dach/bin/wincontrol i") },
{ HYPERKEY,                       XK_j,      spawn,     SHCMD("/home/dach/bin/wincontrol j") },
{ HYPERKEY,                       XK_k,      spawn,     SHCMD("/home/dach/bin/wincontrol k") },
{ HYPERKEY,                       XK_l,      spawn,     SHCMD("/home/dach/bin/wincontrol l") },
{ HYPERKEY,                       XK_m,      spawn,     SHCMD("/home/dach/bin/wincontrol m") },
{ HYPERKEY,                       XK_n,      spawn,     SHCMD("/home/dach/bin/wincontrol n") },
{ HYPERKEY,                       XK_o,      spawn,     SHCMD("/home/dach/bin/wincontrol o") },
{ HYPERKEY,                       XK_p,      spawn,     SHCMD("/home/dach/bin/wincontrol p") },
{ HYPERKEY,                       XK_q,      spawn,     SHCMD("/home/dach/bin/wincontrol q") },
{ HYPERKEY,                       XK_r,      spawn,     SHCMD("/home/dach/bin/wincontrol r") },
{ HYPERKEY,                       XK_s,      spawn,     SHCMD("/home/dach/bin/wincontrol s") },
{ HYPERKEY,                       XK_t,      spawn,     SHCMD("/home/dach/bin/wincontrol t") },
{ HYPERKEY,                       XK_u,      spawn,     SHCMD("/home/dach/bin/wincontrol u") },
{ HYPERKEY,                       XK_v,      spawn,     SHCMD("/home/dach/bin/wincontrol v") },
{ HYPERKEY,                       XK_w,      spawn,     SHCMD("/home/dach/bin/wincontrol w") },
{ HYPERKEY,                       XK_x,      spawn,     SHCMD("/home/dach/bin/wincontrol x") },
{ HYPERKEY,                       XK_y,      spawn,     SHCMD("/home/dach/bin/wincontrol y") },
{ HYPERKEY,                       XK_z,      spawn,     SHCMD("/home/dach/bin/wincontrol z") },
{ HYPERKEY,                       XK_Up,      spawn,     SHCMD("/home/dach/bin/wincontrol volup") },
{ HYPERKEY,                       XK_Down,      spawn,     SHCMD("/home/dach/bin/wincontrol voldown") },
{ NULL,  XK_F1, spawn, SHCMD("/home/dach/bin/wincontrol F1") },
{ HYPERKEY,  XK_F2, spawn, SHCMD("/home/dach/bin/wincontrol F2") },
{ HYPERKEY,  XK_F3, spawn, SHCMD("/home/dach/bin/wincontrol F3") },
{ NULL,  XK_F4, spawn, SHCMD("/home/dach/bin/wincontrol F4") },
{ HYPERKEY,  XK_F5, spawn, SHCMD("/home/dach/bin/wincontrol F5") },
{ HYPERKEY,  XK_F6, spawn, SHCMD("/home/dach/bin/wincontrol F6") },
{ HYPERKEY,  XK_F7, spawn, SHCMD("/home/dach/bin/wincontrol F7") },
{ HYPERKEY,  XK_F8, spawn, SHCMD("/home/dach/bin/wincontrol F8") },
{ HYPERKEY,  XK_F9, spawn, SHCMD("/home/dach/bin/wincontrol HF9") },
{ HYPERKEY,  XK_F10, spawn, SHCMD("/home/dach/bin/wincontrol HF10") },
{ HYPERKEY,  XK_F11, spawn, SHCMD("/home/dach/bin/wincontrol HF11") },
{ HYPERKEY,  XK_F12, spawn, SHCMD("/home/dach/bin/wincontrol HF12") },
{ HYPERKEY,  XK_F1, spawn, SHCMD("/home/dach/bin/wincontrol HF1") },
{ HYPERKEY,  XK_F4, spawn, SHCMD("/home/dach/bin/wincontrol HF4") },

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
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

