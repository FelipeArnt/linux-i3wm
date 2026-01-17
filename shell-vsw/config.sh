#!/usr/bin/env bash

echo "Script para configurar o ambiente linux para a shell e seus comandos."

var out = ~/sw/fun/shell-vsw/out
var build = ~/sw/fun/shell-vsw/script/build.sh
var clean = ~/sw/fun/shell-vsw/script/clean.sh
var router = ~/sw/fun/shell-vsw/script/router.sh
var tvbox = ~/sw/fun/shell-vsw/script/tvbox.sh

configurar_comandos() {
  sudo mv out /usr/local/bin/vsw
  sudo mv build /usr/local/bin/b
  sudo mv clean /usr/local/bin/c
  sudo mv router /usr/local/bin/roteador
  sudo mv tvbox /usr/local/bin/tvbox

}
main() {
  configurar_comandos
}

main "@$"
