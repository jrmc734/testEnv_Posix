# Change Log
Este arquivo documenta as principais mudanças entre as versões de release que foram feitas ao longo do projeto na branch `main`.
 
Este change log é fortemente inspirado no [changelog de juampynr](https://gist.github.com/juampynr/4c18214a8eb554084e21d6e288a18a2c).
 
## Unreleased (v3.0) - 2025-03-16

Essa release adiciona os testes ao projeto e melhora a UI.
 
### Adicionado

- [Feature: [controlador] relatório](https://github.com/jrmc734/testenv_posix/issues/22) - Adiciona relatório de comandos do usuário ao final da execução
- [Testes: Escrever testes](https://github.com/jrmc734/testenv_posix/issues/8) - Adiciona testes dos módulos mq_utils e shm_utils

### Alterado

- [Refactor: [controller] improve user interface](https://github.com/jrmc734/testenv_posix/issues/46) - Melhora interface do usuário quanto aos comandos do teclado
- [Refactor: [mq_utils] refactor mq_utils to make testing easier](https://github.com/jrmc734/testenv_posix/issues/43) - Altera tipos de retorno das funções `read_mq()` e `write_mq()` para facilitar os testes
 
## [v2.0](https://github.com/jrmc734/testenv_posix/releases/tag/v2.0) - 2025-03-15
  
Nesta versão, o Controller é capaz de inicializar ambos os outros processos (Instrument Cluster e Sensor Simulator). Além disso, o Instrument Cluster agora recebe entrada do usuário através do teclado e a envia para o Controller.  

O Controller, ao receber um sinal SIGINT ou SIGUSR2, encerra os subprocessos e fecha com segurança a memória compartilhada e a fila de mensagens.  

Adiciona duas novas threads ao arquivo `sensor_simulator.c` para enviar velocidade e temperatura do motor.

### Adicionado

- [Feature: [controlador] sinais](https://github.com/jrmc734/testenv_posix/issues/20) - Cria funções para tratar sinais SIGINT, SIGUSR1 e SIGUSR2 no Controller
- [Feature: [sensores] temperatura](https://github.com/jrmc734/testenv_posix/issues/18) - Cria thread no Sensor Simulator para enviar valores aleatórios de temperatura para a memória compartilhada
- [Feature: [sensores] velocidade](https://github.com/jrmc734/testenv_posix/issues/16) - Cria thread no Sensor Simulator para enviar valores aleatórios de velocidade para a memória compartilhada

 
### Alterado

- [Feature: [controlador] Criar processos secundários](https://github.com/jrmc734/testenv_posix/issues/33) - Executa os binários do Sensor Simulator e do Instrument Cluster direto do Controller utilizando fork() e exec()
- [Feature: [painel_carro] comandos de usuário](https://github.com/jrmc734/testenv_posix/issues/19) - Recebe input do usuário através do Instrument Cluster
 
## [v1.0](https://github.com/jrmc734/testenv_posix/releases/tag/v1.0) - 2025-03-14

Nesta versão, os três módulos (`controller.c`, `instrument_cluster.c` e `sensor_simulator.c`) podem ser inicializados em três terminais diferentes e se comunicar de forma eficaz usando a fila de mensagens e a memória compartilhada.  

O objetivo é provar que a comunicação pode ser realizada, e, para isso, o Instrument Cluster e o Sensor Simulator enviam informações aleatórias para o Controller.
 
### Added

- [Criar controlador](https://github.com/jrmc734/testenv_posix/issues/2) - Cria o arquivo controller.c
- [Criar sensores](https://github.com/jrmc734/testenv_posix/issues/4) - Cria o arquivo sensor_simulator.c
- [Criar painel do carro](https://github.com/jrmc734/testenv_posix/issues/15) - Cria o arquivo instrument_cluster.c
- [Feature: [controlador] inicialização](https://github.com/jrmc734/testenv_posix/issues/21) - Cria o loop principal do controlador, que vai ler a fila de mensagens e a memória compartilhada
- [Feature: [comunicação] painel e controlador](https://github.com/jrmc734/testenv_posix/issues/14) - Cria fila de mensagens no controlador; escreve valores aleatórios na fila através do Instrument Cluster; lê a fila de mensagens no controlador e printa as mensagens recebidas
- [Implementar memória compartilhada](https://github.com/jrmc734/testenv_posix/issues/12) - Cria objeto de memória compartilhada no controlador e o semáforo para controlar seu acesso
- [Feature: [comunicação] sensores e controlador](https://github.com/jrmc734/testenv_posix/issues/5) - Abre área de memória compartilhada no Sensor Simulator e cria thread para escrever nela; lê a área de memória compartilhada no controlador e printa as mensagens obtidas no terminal
- [Feature: [sensores] rotação](https://github.com/jrmc734/testenv_posix/issues/17) - Cria thread no Sensor Simulator para enviar valores aleatórios de RPM para a memória compartilhada
