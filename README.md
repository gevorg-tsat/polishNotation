***== Quest received. Develop an src/graph.c program in C for creating graphs of functions defined by arbitrary expressions. To calculate the values ​​of expressions, use Dijkstra's algorithm for translating expressions into Polish notation. The program is assembled using a Makefile. The name of the build stage is all. The executable file must be stored at the root in the build folder named graph. ==***

* ***Conditions***

The size of the field for displaying graphs is a rectangle of 25 by 80 points.

Definition area - [0; 4 Pi]

Range of values - [-1; 1]

Orientation of the coordinate plane - the ordinate axis is directed downward, the abscissa axis is directed to the right.

The center of coordinates is middle of the left border (point {0, 13}).

You don't need to draw axes. 

Nothing but the graph should be displayed.

Values are rounded according to the rules of mathematics.

* ***Graphics***
  
The field should be displayed using Star symbol for the chart line and "." for the rest of the screen space.

* ***Modules***

Expression parsing and creating a list of lexical units.

Translation into Polish notation and calculation using this notation.

Drawing a graph in the terminal.

 library for organizing dynamic data structures (stack, list, etc.).


<br/>
<br/>

 ***Example:*** 

Input: sin(cos(2*x))

Output:

```
................................................................................
................................................................................
.........***.................**..................**.................***.........
........*...................*..*................*..*...................*........
............*...................*..............*...................*............
.......*...................*........................*...................*.......
.............*...................*............*...................*.............
..........................*..........................*..........................
......*..................................................................*......
..............*..................................................*..............
..................................*..........*..................................
.........................*............................*.........................
.....*....................................................................*.....
...............*................................................*...............
...................................*........*...................................
....*...................*..............................*...................*....
................*..............................................*................
....................................*......*....................................
.......................*................................*.......................
...*.............*............................................*.............*...
......................*..............*....*..............*......................
..*...............*...................*..*...................*...............*..
**.................***.................**.................***.................**
................................................................................
................................................................................
```

> Only `<math.h>`, `<stdio.h>`, `<stdlib.h>`, `<string.h>` and your own modules can be used 

> This task does not provide an auto-check for output, your image may differ slightly from this example

> All possible operations and functions are below

## Important notes:

* The game must be written in C, have a structured style, and run from the terminal; 
  
* Your source code will be tested by the static analyzer `cppcheck`, as well as the style linter `cpplint`. 
  
* Instructions on how to run these tests on your computer are in the `materials` folder. 
  
* We also recommend taking a look at the `code-samples` folder.

* Check your program for memory leaks!

> When developing the game, follow 
the principles of structured programming of E. Dijkstra.

***LOADING...***

# Chapter II

## List 1.

>Reverse Polish notation (RPN), also known as Polish postfix notation or simply postfix notation, is a mathematical notation in which operators follow their operands, in contrast to Polish notation (PN), in which operators precede their operands. It does not need any parentheses as long as each operator has a fixed number of operands. The description "Polish" refers to the nationality of logician Jan Łukasiewicz, who invented Polish notation in 1924.
>
>The reverse Polish scheme was proposed in 1954 by Arthur Burks, Don Warren, and Jesse Wright and was independently reinvented by Friedrich L. Bauer and Edsger W. Dijkstra in the early 1960s to reduce computer memory access and utilize the stack to evaluate expressions. The algorithms and notation for this scheme were extended by the Australian philosopher and computer scientist Charles L. Hamblin in the mid-1950s.
>
>During the 1970s and 1980s, Hewlett-Packard used RPN in all of their desktop and hand-held calculators, and continued to use it in some models into the 2020s. In computer science, reverse Polish notation is used in stack-oriented programming languages such as Forth, STOIC, PostScript, RPL and Joy.

***LOADING...***


## List 2.

>In computer science, the shunting-yard algorithm is a method for parsing mathematical expressions specified in infix notation. It can produce either a postfix notation string, also known as Reverse Polish notation (RPN), or an abstract syntax tree (AST). The algorithm was invented by Edsger Dijkstra and named the "shunting yard" algorithm because its operation resembles that of a railroad shunting yard. Dijkstra first described the Shunting Yard Algorithm in the Mathematisch Centrum report MR 34/61.
>
>Like the evaluation of RPN, the shunting yard algorithm is stack-based. Infix expressions are the form of mathematical notation most people are used to, for instance "3 + 4" or "3 + 4 × (2 − 1)". For the conversion there are two text variables (strings), the input and the output. There is also a stack that holds operators not yet added to the output queue. To convert, the program reads each symbol in order and does something based on that symbol. The result for the above examples would be (in Reverse Polish notation) "3 4 +" and "3 4 2 1 − × +", respectively.
>
>The shunting-yard algorithm was later generalized into operator-precedence parsing.

***LOADING...***


## List 3.

> Possible operations & functions \
> "+" \
> "-" (unary and binary) \
> "*" \
> "/" \
> "()" \
> sin(x) \
> cos(x) \
> tan(x) \
> ctg(x) \
> sqrt(x) \
> ln(x)

***LOADING...***

