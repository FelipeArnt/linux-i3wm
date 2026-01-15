# gash - Gabi shell 

 A implementação da gash é dividida em três partes: **Parser** , **Executor** e **Subsistema da Shell**


 ## Parser:

 O Parser é o componente de software que faz a leitura da linha de comandos, por exemplo "pwd" e coloca em uma estrutura de dados chamada Command Table que armazena os comandos que serão executados.



## Executor:

 O Executor vai pegar a Command Table criada pelo parser e, para todo SimpleCommand no array será criado um novo processo. Se necessário, também criará pipes para comunicar o output de um dos processos para o input do próximo. Adicionalmente, irá redirecionar o standard input, standard output, e standard error se houver qualquer redirecionamento. 

 A trama abaixo exibe uma linha de comando "A | B | C | D". Se existe um redirecionamento como "< infile" detectado pelo Parser, o input do primeiro SimpleCommand(A) é redirecionado do infile. Se existe um redirecionamento de output como "> outfile", é redirecionado o output do ultimo SimpleCommand(D) para o outfile.

 `A | B | C | D > outfile < infile  > errfile`

Se existe um redirecionamento para errfile como ">& errfile" o stderr de todos os processos de SimpleCommand serão redirecionados para o errfile.

## Shell Subsystems

Outros subsistemas que completam a shell são:

- Variáveis de Ambiente: Expressões da forma ${VAR} são expandidas com o correto uso da variável de ambiente. Além disso, a shell deve poder setar, expandir e printar variáveis de ambiente.
- WildCards: Argumentos na forma "a * a" são expandidos para todos os arquivos que batem com eles no diretório local e em múltiplos diretórios.
- SubShells: Argumentos entre `` são executados e o output é enviado como um input para a shell.


## Utilizando Lex e Yacc para implementação do Parser

Para implementar o parser foram utilizadas duas ferramentas UNIX: Lex e Yacc. Tais ferramentas são usadas na implementação de compiladores, interpretadores e preprocessadores. Um parser é dividido em duas partes: um Lexical Analyzer ou Lexer e um Parser que processa os tokens de acordo com a gramática e constrói a Command Table.


<img width="728" height="410" alt="image" src="https://github.com/user-attachments/assets/da3dec1f-370b-4a78-818f-c31a38f90371" />

Os tokens são descritos em um arquivo shell.l utilizando de expressões regulares. O arquivo shell.l é processado com o programa **`lex`** que gera o Lexical Analyzer. <--TO-DO-->

---  

## Shell Grammar
As regras de gramática shell são **SimpleCommands** e **Pipelines**.

### SimpleCommand

SimpleCommand é uma sequência de parâmetros opcionais seguidos de uma palavra blank-separeted com a opção de redirecionamento intercalado. 

- A primeira palavra é o comando a ser executado, e as palavras seguintes, se existirem, são argumentos para o comando. Se o nome de um comando for fornecido, as atribuições de parâmetros modificam o ambiente do comando quando ele é executado. 
- O valor de um simples comando é o seu "exit status", ou 128 + o signal number se o terminar com um signal. Por exemplo: `echo foo` é um simples comando com argumentos.


### Pipelines

Um Pipeline é, ou um SimpleCommand, ou uma sequência de dois ou mais SimpleCommands onde cada comando é separado um do outro por um "|" ou "|&". Quando os comandos são separados por "|", a saída padrão do primeiro comando é conectada à entrada padrão do próximo. 

E um "|&" é uma abreviação de "2>&1 |", que conecta tanto a saída padrão, quanto o erro padrão do comando à entrada padrão do próximo. O valor de um pipeline é o valor do último comando, a menos que o pipeline seja precedido de "!". Nesse caso, o valor recebe o "inverso lógico" do valor do último comando. 

Por exemplo: 

- echo foo | sed 's/foo/bar/' é um pipeline, onde o output (foo + uma nova linha) do primeiro comando é passado para o input do segundo.
- Se um pipeline é precedido por um `coproc`, ele é executado como um coprocessado; Um two-way pipe é estabelecido entre o pipeline e a parent shell.
- O shell pode ler ou escrever no coprocesso por meio dos operadores de redirecionamento '>&p' e '<&p' ou com 'print -p' e 'read -p'. 
- Um pipeline não pode ser precedido por 'coproc' e '!' simultaneamente. Se o controle de tarefas estiver ativo, o coprocesso pode ser tratado, exceto em entrada e saída, como uma tarefa em segundo plano comum.
