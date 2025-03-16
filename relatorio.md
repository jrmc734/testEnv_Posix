# Relatório - Projeto Gerência de Configuração
Este documento se trata de um relatório descritivo das estratégias utilizadas no desenvolvimento do projeto da disciplina de Gerência de Configuração.

## Estratégia de branching utilizada
Para a criação e organização de branches, foi utilizado um modelo similar ao [Gitflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow), com:
 - uma branch `main` estável para criação das tags de release;
 - uma branch de desenvolvimento `develop`, onde as novas features eram integradas antes das releases;
 - branches `feature/*` para desenvolvimento de novas features separado da `develop`;
 - e branches `fix/*` para correção de bugs.

## Convenção de commits
Para commits mais elaborados, foi adotada uma estratégia similar ao [Karma](https://karma-runner.github.io/6.4/dev/git-commit-msg.html), onde as mensagens de commit seguiam um padrão de:
```
<type>[(<scope>)]: <subject>
<BLANK LINE>
[<body>]
```
onde:
- `<type>` corresponde a `feat`, `[bug]fix`, `chore`, `test`, `build`, entre outros, de acordo com o objetivo do commit;
- `(<scope>)` é opcional e pode nomear o(s) arquivo(s) a ser(em) modificado(s) ou o conceito a ser aplicado;
- `subject` é uma mensagem curta e descritiva do que o commit realiza;
-  e `body` é opcional e pode ser uma descrição mais longa ou uma lista das alterações feitas (listadas com bullets).

### Exemplos

```
test(mq_utils): add tests for mq_utils
- add Unity to project
- add first tests for mq_utils
- configure gitignore to ignore test binaries
- add target to Makefile to build and run tests
```

```
bugfix: uptading .gitignore
```

Em casos de commits mais simples, como a criação e atualização de actions ou arquivos .md, não foi adotada uma convenção específica. 
(Ex: "[Create CD.yml](https://github.com/jrmc734/testenv_posix/commit/d24358d3b09b3e474fe0cdab008d05ff43705cbc)", "[Create CHANGELOG.md](https://github.com/jrmc734/testenv_posix/commit/23dbd731f65d3360308ab02ab4023dc75396d698)")

## Procedimento de build e CI/CD

## Estrutura e política de testes
Os testes foram criados numa pasta `test/` separada da pasta `src/` e testam as "bibliotecas" criadas.

```
.
├── bin/
├── inc/
├── Makefile
├── obj/
├── README.md
├── src/
└── test/
    ├── test_controller.c
    ├── test_mq_utils.c
    ├── test_mq_utils_read.c
    ├── test_shm_utils.c
    ├── unity.c
    ├── unity.h
    └── unity_internals.h
```

Foi criado um target `test` no `Makefile` na pasta raiz. Assim, basta navegar até o diretório raiz e digitar
```
$ make test
```
que os testes, utilizando o framework Unity, serão realizados.

Além disso, há um workflow [test-ci.yml](https://github.com/jrmc734/testenv_posix/blob/develop/.github/workflows/test-ci.yml) para realizar os testes sempre que houver um push ou pull request em qualquer branch.

## Forma de versionamento adotada

Foram criadas tags e releases em pontos estáveis do código:

- Na [v1.0](https://github.com/jrmc734/testenv_posix/releases/tag/v1.0), é possível executar o código dos 3 módulos separadamente e verificar a comunicação entre eles.
- Na [v2.0](https://github.com/jrmc734/testenv_posix/releases/tag/v2.0), é possível execugtar apenas o Controlador e este, por sua vez, inicializa os dois outros módulos. Aqui a comunicação segue um padrão e é possível ler comandos do usuário.
- Na [v3.0], ...

## Gerenciamento de issues

No início do projeto, foi criado um planejamento no GitHub Project Boards [aqui](https://github.com/users/jrmc734/projects/4/views/1). 
Seguindo os [requisitos do projeto da disciplina de POSIX](https://github.com/Curso-de-Sistemas-Embarcados/Trabalho-1/blob/main/README.md), 
criamos cards pra cada um deles, e, ao abrir PRs, foi utilizada referência cruzada para [fechar issues automaticamente](https://docs.github.com/en/issues/tracking-your-work-with-issues/using-issues/linking-a-pull-request-to-an-issue).

## Lições aprendidas
Pudemos exercitar na prática conceitos de gerência de configuração e ficar maravilhados ao vê-los funcionar.

## Reflexões
- "Por mais longa que seja a caminhada, o mais importante é dar o primeiro passo." - Vinícius de Moraes
- "Slow and steady wins the race", moral da fábula _A Tartaruga e a Lebre_
- Padronização é muito importante na hora de procurar erros e onde problemas podem ter acontecidos
- Revisão de PRs dá uma maior confiabilidade para o código a ser integrado
- 


