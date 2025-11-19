#!/bin/bash

# If any command errors, stop the script
set -e

# Set up freetype library symlink for ARM64
FOREIGN_ARM64="../non-source/foreign/arm64"
mkdir -p "$FOREIGN_ARM64"

# Create symlink to Homebrew's freetype library
# Find the homebrew lib directory (handles both Intel and Apple Silicon paths)
if [ -d "/opt/homebrew/lib" ]; then
    FREETYPE_LIB="/opt/homebrew/lib/libfreetype.a"
elif [ -d "/usr/local/lib" ]; then
    FREETYPE_LIB="/usr/local/lib/libfreetype.a"
else
    echo "Error: Cannot find Homebrew installation"
    exit 1
fi

if [ ! -f "$FREETYPE_LIB" ]; then
    echo "Error: libfreetype.a not found at $FREETYPE_LIB"
    echo "Please install freetype: brew install freetype"
    exit 1
fi

ln -sf "$FREETYPE_LIB" "$FOREIGN_ARM64/libfreetype-mac.a"

chmod +x bin/build-mac.sh
bin/build-mac.sh "-DPACKAGE_SUPER_ARM64"
