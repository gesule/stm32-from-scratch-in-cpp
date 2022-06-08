# stm32-from-scratch-in-cpp
A concept proof to replace CMSIS-HAL with a c++ library more expressive and more lightweight in runtime.

La motivación de este proyecto es que no he conseguido aceptar que un programa trivial como el típico "Blink" ocupe mas de 6kb de flash, quizá sea porque ha pasado demasiado tiempo con MCUs de 8 bits, pero siempre me ha molestado, y además el código resultante al utilizar STM32-HAL me resulta feo y pesado a la vista.

Con esta prueba de concpto se trata de atisbar como podría verse una implementación de un HAL en C++.
Este HAL tendría como objetivos:
  - Minimizar el coste de inicialización del MCU, tanto en memoria de programa como en ciclos de CPU.
  - Mejorar la legibilidad.
  - Reducir la curva de aprendizaje del HAL, tratando de hacer mas intuitivo su uso.

Se deja de lado el interés por unificar las APIS para la inicialización de periféricos a traves de toda la familia STM32. Este objetivo complicaría los anteriores, y además lo mas productivo para esta tarea es utilizar un generador de código a partir de un configurador visual, como el STM32Cube. Sin embargo conviene que el código generado resulte legible y conciso.

Compilado con las opciones: 
   -std=gnu++20 -Os 

resulta un binario que ocupa 700 bytes. De los cuales 576 son debidos a la rutina: startup.s.

Un programa similar con STM32-HAL ocupa 6,66kB.

Comparando: (700-576)/(6660-576) = 0.020. ~ 1/50 WTF!



