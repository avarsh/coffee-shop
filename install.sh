#!/bin/bash

echo "Creating directory in /usr/share/..."
sudo rm -r /usr/share/coffee-shop/
sudo mkdir /usr/share/coffee-shop/

echo "Copying binaries..."
sudo cp -r ./bin/coffee-shop /usr/bin/
echo "Copying sounds..."
sudo cp -r ./data/sounds /usr/share/coffee-shop/ 
echo "Copying images..."
sudo cp -r ./data/images /usr/share/coffee-shop/
echo "Copying everything else..."
sudo cp ./data/coffee-shop.desktop /usr/share/applications/
sudo cp ./data/icons/coffee-shop.svg /usr/share/icons/hicolor/scalable/apps/
gtk-update-icon-cache
