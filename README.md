This is an engima machine coded in C++. Uses the enigma rotors from 1930.

Has features such as initial ring setting, reflector and a plugboard.

How it works:

Plugboard:
Before entering the rotors, the signal passes through a plugboard (steckerbrett), where pairs of letters can be swapped.
The plugboard adds another layer of substitution, increasing the complexity and making the code harder to break.
For example if a and h are linked together, a becomes h and visa versa.

Rotors:
The machine has several rotating discs, called rotors, which are the heart of the encryption process.
Each rotor has 26 positions (one for each letter of the alphabet) and internal wiring that scrambles the input letter into a different output letter.
After each key press, the rightmost rotor advances one position, changing the wiring and thus the encryption pattern. When it completes a full turn, it triggers the rotor to its left to move, adding to the complexity.

Reflector:
After passing through the rotors, the signal hits a reflector, which bounces it back through the rotors in reverse, further scrambling the letter.




Link to reference used for rotor and other information:
https://en.wikipedia.org/wiki/Enigma_rotor_details
