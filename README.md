# Logic-Signal-Probabilities

This software implements three different methods to estimate the probability values for signals in a mapped logic circuit. The problem of calculating signal probabilities is still an open question as how to be done with exact precision and acceptable time/space complexity. 

The code is able to read a circuit in verilog format and a library of cells in liberty format to perform the logic signal probability calculations. 

About the methods: One approach uses an exhaustive method, which has unacceptable time complexity. Another approach has O(N) complexity, with N being the size of the logic circuit, although probability values calculated are incorrect. A third approach was also implemented where the error in probability values are mittigated by considering the presence of reconvergent paths in the circuit.

This software was used on a research project by the student Augusto Berndt during his undergraduation thesis at FURG (the PDF text is available in this repository, in Portuguese "Métodos para Cálculo das Probabilidades deSinais em Circuitos Combinacionais"). This implementation was realized during 2016 and 2018.

