#!/bin/bash

# Define the target directory and the zip file name
TARGET_DIR="mac_build"
ZIP_FILE="mac_build.zip"

# Step 1: Create the mac_build directory
mkdir -p "$TARGET_DIR"

# Step 2: Copy all .cpp, .h, the icon/ folder, and Makefile_mac to mac_build and include an example data folder
cp *.cpp *.h "$TARGET_DIR"/
cp Makefile_mac "$TARGET_DIR"/Makefile
cp -r icon "$TARGET_DIR"/
cp icon/icon.png "$TARGET_DIR"/
cp -r data "$TARGET_DIR"/
cp Readme.md "$TARGET_DIR"/

# Step 3: Zip the mac_build directory
zip -r "$ZIP_FILE" "$TARGET_DIR"

# Step 4: Remove the mac_build directory
rm -rf "$TARGET_DIR"

# Success message
echo "Files successfully copied to $ZIP_FILE and mac_build folder removed."
