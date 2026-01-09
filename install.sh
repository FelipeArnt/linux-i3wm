sudo pacman -S lightdm lightdm-gtk-greeter --noconfirm
sudo systemctl enable lightdm
sudo reboot

sudo pacman -S xorg-server xorg-xinit xorg-xwayland --noconfirm
sudo systemctl enable lightdm
sudo reboot
