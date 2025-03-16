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

A estratégia de CI/CD foi configurada por meio de workflows no **GitHub Actions**, localizados em `.github/workflows/`.

---

## CI (Integração Contínua)

**Objetivo:** Compilar e testar o projeto sempre que houver **push** ou **Pull Request** na `develop` (ou em branches de `feature/` ou `fix/`).

**Arquivo:** `test-ci.yml` (como exemplo).

### Etapas

1. Fazer **checkout** do repositório ([actions/checkout](https://github.com/actions/checkout)).
2. Instalar dependências necessárias (compilador C, etc.).
3. Executar `make clean && make`.
4. Executar `make test`, rodando os testes do framework **Unity**.

> **Resultado:** Qualquer falha de compilação ou teste impede que o Pull Request seja aceito sem correções.

---

## Release CD (Entrega Contínua)

**Objetivo:** Criar uma release e publicar uma imagem Docker quando:
- há **push** na branch `main`, ou
- quando se cria uma **tag** (por exemplo, `vX.Y`).

**Arquivo:** `CD.yml`.

### Etapas

1. **Checkout** do código.
2. **Build e teste** (para garantir consistência).
3. **Docker**: Gera-se duas imagens docker. Uma imagem é a versão específica da release (com o nome do number_runner da action) e outra imagem sendo o `lastest`, com isso sempre teremos uma imagem para cade release e uma imagem sempre sendo uma última versão.

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
Pudemos exercitar na prática conceitos de gerência de configuração e ficar maravilhados ao vê-los funcionar (principalmente as actions).
- **Pipelines de CI/CD**: Os pipelines de CI/CD são excelentes para acelerar a criação de releases e integração dos códigos, além de garantir que não possa fazer um push de um código defeituoso em branches importantes (main ou develop).
- **Github Projects**: A utilização do Projects do Github é uma ferramenta bem interessante para organizar uma equipe.
- **Padronização de commits e revisão de PRs**: Percebemos que, ao adotar convenções de commits e exigir revisões de Pull Requests, reduzimos significativamente o retrabalho. Com a padronização, era fácil identificar onde e por que uma mudança foi feita.
- **Gerência de versão e tags**: Descobrimos que taguear versões estáveis e criar releases no GitHub era mais útil do que imaginávamos, pois facilitou a recuperação de uma versão funcional quando algo quebrava em uma branch de desenvolvimento.
- **Docker no processo de build e deploy**: No início, os integrantes não tinham familiaridade com Docker. Com o tempo, aprendemos que a criação de uma imagem padronizada e a publicação no Docker Hub simplificam o compartilhamento do ambiente e a execução da aplicação em diferentes máquinas.
- **Documentação e histórico**: A manutenção de um CHANGELOG.md e de um relatório contínuo de SCM ajudou na organização, pois cada membro ficou mais consciente do que estava sendo feito.
- **Gerenciamento do código fonte**: Ao utilizar a estrutura base do Github Flow, com main e develop como branches principais e features/ como branches temporárias e que agregavam funcionalidades ao código, percebemos que o processo de desenvolvimento se torna mais padronizado e organizado.

## Reflexões
- "Por mais longa que seja a caminhada, o mais importante é dar o primeiro passo." - Vinícius de Moraes
- "Slow and steady wins the race", moral da fábula _A Tartaruga e a Lebre_
- Padronização é muito importante na hora de procurar erros e onde problemas podem ter acontecidos
- Revisão de PRs dá uma maior confiabilidade para o código a ser integrado
- A definição de regras de proteção nas branches principais garante uma camada de proteção contra código defeituoso
- Utilização de branches temporárias para desenvolvimento de novas funcionalidades e correção de bugs se mostrou bastante proveitoso, garantindo um processo mais padronizado entre a equipe.
- O github secrets é bem interessante! Excelente ferramenta que o grupo desconhecia
- Entender e aprender como funciona o Github Actions é muito importante, tanto para o projeto como para o mercado de trabalho no geral.

