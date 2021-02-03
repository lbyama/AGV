GitHub

Instale o git no Linux pelo terminal, usando a linha de comando 
"sudo apt-get install git"
"sudo apt update"

No diretório do projeto em sua máquina, inicie o git com "git init" no terminal.
Configure seu nome e e-mail com 
"git config --global user.name "seu_nome"
"git config --global user.email "seu_e-mail"

Clone este repositório para a sua máquina usando "git clone https://github.com/JuliaChrist/Pipoqueira_motosserra_prototipo_inicial.git"

A branch principal do projeto é a "main". Para criar a sua branch e fazer alterações, use "git checkout -b nome_da_branch"
No repositório local voce pode alternar as branchs usando "git checkout nome_branch"
Com "git branch" é possível vizualizar em que branch você está no momento.

Para salvar suas alterações e enviá-las ao repositório remoto, use as linhas de comando
"git add ." (adiciona todos os arquivos)
"git commit -am "descrição da alteração" (faz o commit das alterações. Caso seja necessário retornar uma versão do código, são os commits que serão utilizados, portanto recomenda-se fazer o commit das alterações após cada alteração feita no código)

Para enviar as alterações ao repositório remoto, faça um pull request.




