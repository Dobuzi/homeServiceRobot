#!/bin/sh
echo 'deb http://download.opensuse.org/repositories/openSUSE:/Tools/xUbuntu_16.04/ /' | sudo tee /etc/apt/sources.list.d/openSUSE:Tools.list
curl -fsSL https://download.opensuse.org/repositories/openSUSE:Tools/xUbuntu_16.04/Release.key | gpg --dearmor | sudo tee /etc/apt/trusted.gpg.d/openSUSE_Tools.gpg > /dev/null
sudo apt update
sudo apt install osc