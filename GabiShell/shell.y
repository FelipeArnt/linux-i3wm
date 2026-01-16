/*TO:DO -> Shell grammar rules para o parser*/

/* Grammar rules em Backus-Naur form*/

cmd [arg]* [ | cmd[arg]* ]*
    [ [> filename] ] [ [< filename] ] [ [>& filename] ] [ [>> filename] ] [ [>>& filename] ]* [&]
