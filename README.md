# Sliding-Puzzle

This code solve the sliding puzzle https://en.wikipedia.org/wiki/Sliding_puzzle using deterministic algorithm (not A*). It produces a random puzzle and solves it. 

   12   15    2    6         1    2    3    4
    3    0    7    9         5    6    7    8
    8    5   14   13   ===>  9   10   11   12
   10    4    1   11        13   14   15    0
   
   The zero is the empty space.
   
   Sometimes the puzzle can not end up to the above state, and end up in this situation:
   
    4    5   15    0         1    2    3    4
   10   14   13    3         5    6    7    8
   11    2    6   12  ===>   9   10   11   15
    9    7    1    8        13   14   12    0
    
    Therefore it finds another solution for it:
    
    4    5   15    0        15   14   13   12
   10   14   13    3        11   10    9    8
   11    2    6   12  ===>   7    6    5    4
    9    7    1    8         3    2    1    0  
 


