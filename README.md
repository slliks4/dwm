# dwm — System Integration & Configuration

This repository contains the **authoritative dwm configuration** for this system.

It is the single source of truth for:

* keybindings
* visual settings (borders, colors)
* layout decisions
* patch history (when applicable)

System-level setup (X11, display, keyboard, etc.) lives in the dotfiles repo.
This repo focuses **only on dwm itself**.

---

## 📦 Installation

dwm is installed from source and lives outside dotfiles.

### Clone

```bash
sudo mkdir -p /usr/local/src
sudo chown -R "$USER:$USER" /usr/local/src

cd /usr/local/src
git clone https://github.com/slliks4/dwm.git
cd dwm
```

### Build & Install

```bash
sudo make clean install
```

After installation, `dwm` is available system-wide.

---

## ⚙️ Configuration Model

dwm is configured by editing `config.h` and recompiling.

All changes are **explicit and intentional** — no runtime config, no hidden state.

```bash
cd /usr/local/src/dwm
sudo nvim config.h
sudo make clean install
```

---

## 🔑 Core Configuration (Practical Defaults)

These are the **minimum changes** applied early to make dwm usable day-to-day.

### Modifier Key (Super / Windows)

Default dwm uses `Alt`.
This setup uses the **Super (Windows) key**.

```c
#define MODKEY Mod4Mask
```

---

### Default Terminal

Change the default terminal to **Alacritty**.

```c
static const char *termcmd[] = { "alacritty", NULL };
```

---

### Terminal Keybinding (Mod + Enter)

Default dwm uses `Mod + Shift + Enter`.
This setup simplifies it to `Mod + Enter`.

```c
{ MODKEY, XK_Return, spawn, {.v = termcmd } },
```

---

## 📚 Documentation

Detailed behavior and rationale live alongside the code.

### Keybindings

Intent, removed defaults, and workflow decisions:

* 📄 [`docs/keybindings.md`](docs/keybindings.md)

### Visuals

Borders, colors, and minimal cosmetic changes:

* 📄 [`docs/visual.md`](docs/visual.md)

Inline comments in `config.h` remain the **authoritative reference**.

---

## 🧠 Philosophy

* configuration lives next to code
* rebuilds are explicit
* defaults are reduced, not replaced
* features are added only when proven necessary

If something feels missing, it should be discovered through use — not guessed in advance.
