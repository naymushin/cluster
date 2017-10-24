Computational cluster with hypercube topology based on
microprocessors with low power consumption.

Cluster is built on STM32F765ZG microcontrollers (ARM Cortex-M7F)
using FreeRTOS operating system.

Hardware architecture of cluster is as follows:
1. There are 16 executive modules connected to main control node through
Ethernet interface using switch device.
2. Each executive module consists of 16 executive nodes and 1 control
node. Control node is connected with main control node through switch
device. Also control node is connected to all executive nodes through
4-to-16 decoder.
3. Each executive node uses 4 SPI interfaces to interact with other
nodes in topology of 4-dimensional cube (hypercube).

Flow of tasks is sent to main control node from outside.
Then each task is sent to control nodes and is splitted to several
atomic subtasks and, finally, all subtasks is performed on executive
nodes. Results of all subtasks form result of whole task and is sent
to main control node.

Theoretical maximum of computational power is 118,4 GFlops with
total power consumption of 41,6 W.