# Repository Setup (Fork + Upstream Workflow)

This document explains how this dwm repository is structured and how upstream
updates are handled.

The goal is:

* keep full control over local customizations
* stay close to upstream dwm
* make rebasing and merging predictable

---

## 📌 Repository Model

This repository is a **fork of upstream dwm** with local changes applied.

Remotes are configured as:

* **`origin`** → personal fork (GitHub)
* **`upstream`** → official dwm repository (suckless)

```text
origin   → https://github.com/slliks4/dwm.git
upstream → https://git.suckless.org/dwm
```

This allows pulling official updates without losing local changes.

---

## 🔧 Initial Setup

If cloning fresh:

```bash
git clone https://github.com/slliks4/dwm.git
cd dwm
```

Add upstream manually (if not already present):

```bash
git remote add upstream https://git.suckless.org/dwm
```

Verify:

```bash
git remote -v
```

Expected output:

```text
origin    https://github.com/slliks4/dwm.git (fetch)
origin    https://github.com/slliks4/dwm.git (push)
upstream  https://git.suckless.org/dwm (fetch)
upstream  https://git.suckless.org/dwm (push)
```

---

## 🌿 Branch Strategy

* `main` → local customized branch
* upstream has no branches (single `master`)

Local development happens directly on `main`.

No patch queue or rebasing strategy is enforced yet — simplicity first.

---

## 🔄 Pulling Upstream Changes

To check for new upstream changes:

```bash
git fetch upstream
```

To merge upstream changes into your fork:

```bash
git merge upstream/master
```

Resolve conflicts (if any), then rebuild:

```bash
sudo make clean install
```

---

## 🧪 Why This Works Well for dwm

* dwm changes slowly
* conflicts are rare and visible
* config lives in `config.h`, not scattered files
* rebuilding is fast and deterministic

This workflow avoids unnecessary complexity (rebase scripts, patch stacks)
until they are actually needed.

---

## 🧠 Notes

* Binary artifacts (`dwm`, `*.o`) should **not** be committed in the future
* All behavioral changes should be explained inline in `config.h`
* Documentation lives next to configuration, not in dotfiles

---

This setup is intentionally boring — and that’s the point.

If dwm ever changes faster or patches grow large, the workflow can evolve.

