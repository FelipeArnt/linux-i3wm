#!/bin/zsh

#@Author: FelipeArnt - LABELO / VSW
# Script de instalação de ferramentas para ensaios funcionais de metrologia legal e segurança cibernética.

set -e

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${GREEN}=== Instalação de Ferramentas para Metrologia Legal ===${NC}"
echo -e "${GREEN}=== Verificação de Código e Ensaios Funcionais de Segurança ===${NC}\n"

# Função para verificar se comando existe
command_exists() {
  command -v "$1" >/dev/null 2>&1
}

# Atualizar sistema
echo -e "${YELLOW}[1/6] Atualizando sistema...${NC}"
sudo pacman -Syu --noconfirm

# Ferramentas de análise de binários e código
echo -e "${YELLOW}[2/6] Instalando ferramentas de análise de binários...${NC}"
sudo pacman -S --needed --noconfirm \
  binwalk \
  radare2 \
  ghidra \
  rizin \
  hexedit \
  xxd \
  checksec \
  strace \
  ltrace \
  gdb \
  python-pwntools \
  elfutils \
  binutils \
  file \
  strings

# Ferramentas de penetration testing e segurança de rede
echo -e "${YELLOW}[3/6] Instalando ferramentas de teste de penetração...${NC}"
sudo pacman -S --needed --noconfirm \
  nmap \
  wireshark-qt \
  tcpdump \
  aircrack-ng \
  hashcat \
  john \
  nikto \
  sqlmap \
  metasploit \
  burpsuite \
  hydra \
  netcat \
  socat \
  ettercap \
  dsniff

# Scanner de vulnerabilidades
echo -e "${YELLOW}[4/6] Instalando scanners de vulnerabilidade...${NC}"
if command_exists yay; then
  yay -S --needed --noconfirm openvas nessus
elif command_exists paru; then
  paru -S --needed --noconfirm openvas nessus
else
  echo -e "${RED}AUR helper não encontrado. Instale yay ou paru para OpenVAS/Nessus${NC}"
fi

# Ferramentas específicas para roteadores e dispositivos embarcados
echo -e "${YELLOW}[5/6] Instalando ferramentas para análise de firmware...${NC}"
sudo pacman -S --needed --noconfirm \
  firmware-mod-kit \
  squashfs-tools \
  cramfs \
  mtd-utils \
  ubi_reader

# Ferramentas Python adicionais
echo -e "${YELLOW}[6/6] Instalando ferramentas Python...${NC}"
sudo pacman -S --needed --noconfirm python-pip python-virtualenv

pip install --user --break-system-packages \
  frida \
  frida-tools \
  binwalk \
  ropper \
  angr \
  pwntools \
  capstone \
  keystone-engine \
  unicorn

# Configurações adicionais
echo -e "${YELLOW}Configurando permissões do Wireshark...${NC}"
sudo usermod -aG wireshark $USER
sudo setcap cap_net_raw,cap_net_admin=eip /usr/bin/dumpcap

# Criação de diretórios de trabalho
echo -e "${YELLOW}Criando estrutura de diretórios...${NC}"
mkdir -p ~/lab/{firmware,binarios,relatorios,scripts,capturas}

# Verificação final
echo -e "\n${GREEN}=== Instalação Concluída ===${NC}"
echo -e "${GREEN}Ferramentas instaladas:${NC}"
echo "  - Análise de binários: binwalk, radare2, ghidra, checksec"
echo "  - Penetration testing: nmap, wireshark, metasploit, burpsuite"
echo "  - Análise de firmware: binwalk, squashfs-tools, firmware-mod-kit"
echo "  - Python tools: frida, pwntools, angr, ropper"
echo -e "\n${YELLOW}Observações:${NC}"
echo "  - Faça logout/login para aplicar grupo wireshark"
echo "  - Configure OpenVAS: sudo gvm-setup (se instalado)"
echo "  - Diretórios criados em ~/lab/"
echo -e "\n${GREEN}Script finalizado!${NC}"
