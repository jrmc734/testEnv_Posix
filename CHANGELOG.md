# Change Log
All notable changes to this project will be documented in this file.
 
This changelog is strongly inspired by [juampynr's sample changelog](https://gist.github.com/juampynr/4c18214a8eb554084e21d6e288a18a2c).
 
## Unreleased (v3.0) - 2025-03-16

This release adds the tests to the project and improves the terminal user interface.
 
### Added

- [Feature: [controlador] relatório](https://github.com/jrmc734/testenv_posix/issues/22) - Add user commands report at the end of execution
- [Testes: Escrever testes](https://github.com/jrmc734/testenv_posix/issues/8) - Create tests to mq_utils and shm_utils

### Changed

- [Refactor: [controller] improve user interface](https://github.com/jrmc734/testenv_posix/issues/46) - Improve user interface to show commands more easily
- [Refactor: [mq_utils] refactor mq_utils to make testing easier](https://github.com/jrmc734/testenv_posix/issues/43) - Change read_mq and write_mq return types to make testing easier.
 
### Fixed
 
## [v2.0](https://github.com/jrmc734/testenv_posix/releases/tag/v2.0) - 2025-03-15
  
In this release, the Controller is capable of initializing both of the other processes (Instrument Cluster and Sensor Simulator). Also, the Instrument Cluster now receives input from the user and sends it to the Controller.

The Controller, upon receiving a SIGINT or SIGUSR2 signal, terminates the subprocesses and closes the shared memory and message queue objects safely.

Add two new threads to sensor_simulator.c.

### Added
- [Feature: [controlador] sinais](https://github.com/jrmc734/testenv_posix/issues/20) - Create functions to handle SIGINT, SIGUSR1 and SIGUSR2 signals in the Controller
- [Feature: [sensores] temperatura](https://github.com/jrmc734/testenv_posix/issues/18) - Create thread in sensor_simluator.c to send random temperature info to shared memory
- [Feature: [sensores] velocidade](https://github.com/jrmc734/testenv_posix/issues/16) - Create thread in sensor_simluator.c to send random speed info to shared memory

 
### Changed

- [Feature: [controlador] Criar processos secundários](https://github.com/jrmc734/testenv_posix/issues/33) - Execute Sensor Simulator and Instrument Cluster binaries using fork() and exec() directly from the Controller. Now we can execute everything from just 1 terminal.
- [Feature: [painel_carro] comandos de usuário](https://github.com/jrmc734/testenv_posix/issues/19) - Receive user input through the Instrument Cluster.
 
## [v1.0](https://github.com/jrmc734/testenv_posix/releases/tag/v1.0) - 2025-03-14

In this release, the three modules (controller.c, instrument_cluster.c and sensor_simulator.c) can be initialized in three different terminals and can communicate effectively using the message queue and the shared memory objects.

The goal is to prove that the communication can be done, and so the Instrument Cluster and the Sensor Simulator send random information to the Controller.
 
### Added

- [Criar controlador](https://github.com/jrmc734/testenv_posix/issues/2) - Create file controller.c
- [Criar sensores](https://github.com/jrmc734/testenv_posix/issues/4) - Create file sensor_simulator.c
- [Criar painel do carro](https://github.com/jrmc734/testenv_posix/issues/15) - Create file instrument_cluster.c
- [Feature: [controlador] inicialização](https://github.com/jrmc734/testenv_posix/issues/21) - Create controller loop
- [Feature: [comunicação] painel e controlador](https://github.com/jrmc734/testenv_posix/issues/14) - Create message queue in the controller; write to mq random values in the instrument cluster; make the controller read mq continuously and print received messages.
- [Implementar memória compartilhada](https://github.com/jrmc734/testenv_posix/issues/12) - Create shared memory object and semaphore in the controller.
- [Feature: [comunicação] sensores e controlador](https://github.com/jrmc734/testenv_posix/issues/5) - Open shared memory in sensor_simulator.c and write to it; read shared memory in the controler.
- [Feature: [sensores] rotação](https://github.com/jrmc734/testenv_posix/issues/17) - Create thread in sensor_simluator.c to send random RPM info to shared memory
