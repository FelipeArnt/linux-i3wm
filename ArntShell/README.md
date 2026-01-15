#!/usr/env/c

/*-=-ArntShell-=-*/

# Arnt Shell

 A implementação da shell é dividida em três partes: Parser, Executor e Subsistema da Shell



 ### Parser:

 O Parser é o componente de software que faz a leitura da linha de comandos, por exemplo "pwd" e coloca em uma estrutura de dados chamada Command Table que armazena os comandos que serão executados.



### Executor:

 O Executor vai pegar a Command Table criada pelo parser e, para todo SimpleCommand no array será criado um novo processo. Se necessário, também criará pipes para comunicar o output de um dos processos para o input do próximo. Adicionalmente, irá redirecionar o standard input, standard output, e standard error se houver qualquer redirecionamento. 

 A trama abaixo exibe uma linha de comando "A | B | C | D". Se existe um redirecionamento como "< infile" detectado pelo Parser, o input do primeiro SimpleCommand(A) é redirecionado do infile. Se existe um redirecionamento de output como "> outfile", é redirecionado o output do ultimo SimpleCommand(D) para o outfile.

 `A | B | C | D > outfile < infile 2 > errfile`

Se existe um redirecionamento para errfile como ">& errfile" o stderr de todos os processos de SimpleCommand serão redirecionados para o errfile.

### Shell Subsystems

Outros subsistemas que completam a shell são:

- Variáveis de Ambiente: Expressões da forma ${VAR} são expandidas com o correto uso da variável de ambiente. Além disso, a shell deve poder setar, expandir e printar variáveis de ambiente.
- WildCards: Argumentos na forma "a * a" são expandidos para todos os arquivos que batem com eles no diretório local e em múltiplos diretórios.
- SubShells: Argumentos entre `` são executados e o output é enviado como um input para a shell.


### Utilizando Lex e Yacc para implementação do Parser

Para implementar o parser foram utilizadas duas ferramentas UNIX: Lex e Yacc. Tais ferramentas são usadas na implementação de compiladores, interpretadores e preprocessadores. Um parser é dividido em duas partes: um Lexical Analyzer ou Lexer e um Parser que processa os tokens de acordo com a gramática e constrói a Command Table.


