# Folding a cube

### Description
[This problem](https://open.kattis.com/problems/foldingacube) gave a 6x6 ascii art layout of a piece of paper. The goal was to see if this paper could be folded into a cube. 

### Solution
To check if a piece of paper can be folded into a cube, all you have to do is determine if there are six unique sides you can make. My approach to this was to define a set of valid transitions from one face of a cube to another. Consider the cube layout below, where I've numbered each side.

```
.3.
425
.1.
.0.
```
This is folded such that 0 is adjacent to 1, 4, 5, and 3; 1 is adjacent to 0, 2, 4, and 5; and so on. The way I defined my transitions was the set of locations I could go to from any face after entering from any face. For example, if I entered 2 from 1, I can go left to enter 4, straight to enter 3, or right to enter 5. In the code, you'll see a `map` variable that defines all of these transitions.

Once I have this, I just do a graph search, starting at any face to see if I can cover six different faces.