# dwm — System Integration & Configuration

This repository contains the **authoritative dwm configuration** for this system.

It is the single source of truth for:

* keybindings
* visual settings (borders, colors)
* layout decisions
* hardware key behavior
* patch history (when applicable)

System-level setup (X11, display, keyboard, notifications, etc.) lives in the **dotfiles repository**.
This repo focuses **only on dwm itself**.

---

## 📦 Installation

dwm is installed from source and lives outside dotfiles.

### 1️⃣ Install dependencies

Before building dwm, run:

```sh
./install.sh
```

This installs:

* X11 base
* build tools
* terminal (Alacritty)
* audio + brightness support
* required fonts
* hardware key tooling (`xev`)

Nothing is configured automatically.

---

### 2️⃣ Clone dwm

```sh
sudo mkdir -p /usr/local/src
sudo chown -R "$USER:$USER" /usr/local/src

cd /usr/local/src
git clone https://github.com/slliks4/dwm.git
cd dwm
```

---

### 3️⃣ Build & install

```sh
sudo make clean install
```

After installation, `dwm` is available system-wide.

---

## ⚙️ Configuration Model

dwm is configured by editing `config.h` and recompiling.

There is:

* no runtime configuration
* no IPC
* no hidden state

Every change is explicit.

```sh
sudo nvim config.h
sudo make clean install
```

---

## 📚 Documentation

Detailed behavior and rationale live alongside the code.

* 🔑 **Keybindings**
  📄 [`docs/keybindings.md`](docs/keybindings.md)

* 🎨 **Visuals (borders, colors)**
  📄 [`docs/visual.md`](docs/visual.md)

* 🎛 **Hardware keys (volume, brightness, media)**
  📄 [`docs/hardware-keys.md`](docs/hardware-keys.md)

Inline comments in `config.h` remain the **authoritative reference**.

---

## 🧠 Philosophy

* configuration lives next to code
* rebuilds are explicit
* defaults are reduced, not replaced
* features are added only after real usage proves they’re needed

If something feels missing, it should be discovered through use — not guessed in advance.
