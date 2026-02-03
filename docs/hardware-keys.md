# Hardware Keys (Volume, Brightness, Media)

This document explains how **hardware keys** (volume, brightness, media) are handled in this dwm setup.

Unlike desktop environments, **dwm does nothing automatically** with hardware keys.
Every action is **explicitly bound** in `config.h`.

This is intentional.

---

## Scope

This setup covers:

* Volume (mute / up / down)
* Screen brightness (up / down)
* Optional media controls (play / next / previous)

All bindings are **X11-native** and WM-agnostic.

---

## How Hardware Keys Work in dwm

1. The keyboard emits a special keysym (e.g. `XF86AudioMute`)
2. X11 receives the event
3. dwm binds the keysym to a command
4. The command adjusts volume / brightness

If step 3 is missing → **nothing happens**

---

## Verifying Hardware Keys (Debugging)

Before binding anything, confirm the keys exist.

### Install debugging tool

```sh
sudo pacman -S xorg-xev
```

### Run `xev`

```sh
xev
```

Press your hardware keys and look for output like:

```
keysym 0x1008ff12, XF86AudioMute
keysym 0x1008ff13, XF86AudioRaiseVolume
keysym 0x1008ff03, XF86MonBrightnessDown
```

If you see these → your keyboard and X11 are working correctly.

---

## Required Dependencies

### Core (required)

| Purpose                  | Package       |
| ------------------------ | ------------- |
| X11 input debugging      | `xorg-xev`    |
| Audio control (PipeWire) | `pipewire`    |
| Audio control CLI        | `wireplumber` |
| Brightness control       | `light`       |

Install:

```sh
sudo pacman -S xorg-xev pipewire wireplumber light
```

---

## dwm Configuration

### Required Include

At the top of `config.h`:

```c
#include <X11/XF86keysym.h>
```

---

### Hardware Key Bindings

Add the following to `static const Key keys[]`:

```c
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
```

Notes:

* No modifier key is used
* These keys are already “special”
* Volume increments are intentionally conservative

---

## Rebuild dwm

After editing `config.h`:

```sh
cd /usr/local/src/dwm
sudo make clean install
```

Restart X:

```sh
exit
startx
```

---

## Optional: Media Keys

If you use a media player supporting `playerctl`:

```sh
sudo pacman -S playerctl
```

Optional bindings:

```c
{ 0, XF86XK_AudioPlay, spawn, SHCMD("playerctl play-pause") },
{ 0, XF86XK_AudioNext, spawn, SHCMD("playerctl next") },
{ 0, XF86XK_AudioPrev, spawn, SHCMD("playerctl previous") },
```

---

## Design Notes

* No background daemons
* No magic key handling
* No desktop environment assumptions
* Everything is visible in `config.h`

This keeps the system:

* predictable
* debuggable
* composable

---

## Related Docs

* `docs/keybindings.md`
* `docs/visuals.md`
