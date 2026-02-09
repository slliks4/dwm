/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
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
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

/* Screen Shot Key Binds */
static const char *screenshot_copy[]      = { "screenshot", NULL };
static const char *screenshot_http[]      = { "screenshot", "http", NULL };
static const char *screenshot_save[]      = { "screenshot", "save", NULL };
static const char *screenshot_http_save[] = { "screenshot", "http-save", NULL };
static const char *screenshot_full[]      = { "screenshot", "full", NULL };


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
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *dictcmd[] = { "dict", NULL };

static const Key keys[] = {

    /* =====================
     * Hardware keys
     * ===================== */

    /* Volume (PipeWire) */
    { 0, XF86XK_AudioMute,        spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") },
    { 0, XF86XK_AudioLowerVolume, spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-") },
    { 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+") },

    /* Brightness */
    { 0, XF86XK_MonBrightnessDown, spawn, SHCMD("light -U 10") },
    { 0, XF86XK_MonBrightnessUp,   spawn, SHCMD("light -A 10") },

    /* Music Player */
    { 0, XF86XK_AudioPlay, spawn, SHCMD("playerctl play-pause") },
    { 0, XF86XK_AudioNext, spawn, SHCMD("playerctl next") },
    { 0, XF86XK_AudioPrev, spawn, SHCMD("playerctl previous") },

    /* modifier                     key              function        argument */

    /* --- Application launching --- */
    { MODKEY,                       XK_space,        spawn,          {.v = dmenucmd } }, // Application menu (dmenu)
    { MODKEY,                       XK_Return,       spawn,          {.v = termcmd } },  // Launch terminal
                                                                                         
    /* --- Dictionary word selection search --- */
    { MODKEY,                       XK_slash,        spawn,          {.v = dictcmd } },

    /* --- UI toggles --- */
    { MODKEY,                       XK_b,            togglebar,      {0} },              // Toggle status bar visibility

    /* --- Window focus navigation --- */
    { MODKEY,                       XK_j,            focusstack,     {.i = +1 } },        // Focus next window in stack
    { MODKEY,                       XK_k,            focusstack,     {.i = -1 } },        // Focus previous window in stack

    /* --- Master area sizing --- */
    { MODKEY|ShiftMask,             XK_j,            setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask,             XK_k,            setmfact,       {.f = +0.05} },

    /* --- Window promotion --- */
    { MODKEY,                       XK_m,            zoom,           {0} },               // Promote focused window to master

    /* --- Tag navigation --- */
    { MODKEY,                       XK_Tab,          view,           {0} },               // Toggle between current and previous tag

    /* --- Window control --- */
    { MODKEY,             		    XK_BackSpace,    killclient,     {0} },               // Close focused window

    /* --- Layout selection (explicit) --- */
    { MODKEY,             		    XK_d,            setlayout,      {.v = &layouts[0]} }, // Tiled layout
    { MODKEY,             		    XK_f,            setlayout,      {.v = &layouts[2]} }, // Monocle (fullscreen) layout

    /* --- View / tag all windows --- */
    { MODKEY|ShiftMask,             XK_9,            view,           {.ui = ~0 } },  // View all tags
    { MODKEY|ShiftMask,             XK_0,            tag,            {.ui = ~0 } },  // Assign window to all tags

    /* --- Multi-monitor navigation --- */
    { MODKEY,                       XK_h,            focusmon,       {.i = -1 } },  // left monitor
    { MODKEY,                       XK_l,            focusmon,       {.i = +1 } },  // right monitor

    /* Send window to monitor */
    { MODKEY|ShiftMask,             XK_h,            tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_l,            tagmon,         {.i = +1 } },

    /* Screenshots */
    { MODKEY,                       XK_bracketleft,  spawn,          { .v = screenshot_http } },
    { MODKEY,                       XK_bracketright, spawn,          { .v = screenshot_copy } },
    { MODKEY|ShiftMask,             XK_bracketleft,  spawn,          { .v = screenshot_http_save } },
    { MODKEY|ShiftMask,             XK_bracketright, spawn,          { .v = screenshot_save } },
    { MODKEY|ShiftMask,             XK_p,            spawn,          { .v = screenshot_full } },


    /* --- Tag keys (1–9) --- */
    TAGKEYS(                        XK_0,                              0)
    TAGKEYS(                        XK_9,                              1)
    TAGKEYS(                        XK_8,                              2)
    TAGKEYS(                        XK_7,                              3)
    TAGKEYS(                        XK_4,                              4)
    TAGKEYS(                        XK_5,                              5)
    TAGKEYS(                        XK_1,                              6)
    TAGKEYS(                        XK_2,                              7)
    TAGKEYS(                        XK_3,                              8)

    /* --- WM control --- */
    { MODKEY|ShiftMask,             XK_q,    	quit,            {0} },               // Exit dwm
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

