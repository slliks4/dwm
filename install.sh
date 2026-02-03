#!/bin/sh

set -e

echo "==> Installing dwm build & runtime dependencies"

# --------------------------
# Required system packages
# --------------------------
# - X11 base
# - build tools
# - terminal
# - hardware key support
# --------------------------

PKGS="
xorg-server
xorg-xinit
xorg-xev
base-devel
pkgconf
alacritty
pipewire
wireplumber
light
fontconfig
ttf-dejavu
terminus-font
"

sudo pacman -S --needed $PKGS

echo ""
echo "✅ Dependencies installed"
echo ""
echo "Next steps:"
echo "  1. Review config.h"
echo "  2. Build dwm manually:"
echo ""
echo "     sudo make clean install"
echo ""
