#!/bin/zsh

# Set the app name (update this to your actual app's path)
APP_NAME="ADE.app"

# Get the full path of the app
APP_PATH="$(cd "$(dirname "$0")"; pwd)/$APP_NAME"

# Remove the quarantine attribute
echo "Attempting to remove quarantine from $APP_NAME..."
xattr -r -d com.apple.quarantine "$APP_PATH"

# Check if quarantine was successfully removed
if xattr "$APP_PATH" | grep -q "com.apple.quarantine"; then
    echo "Failed to remove quarantine attribute. Please try manually."
else
    echo "Quarantine attribute successfully removed. You can now run the app!"
fi