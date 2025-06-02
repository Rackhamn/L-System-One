# L-System
Also known as Lindenmayersystem.  
It is a recursive system built on simple replacement rules.  
[L-System (Wikipedia)](https://en.wikipedia.org/wiki/L-system)  

## Current Implementation of Rules
Rules `F+[FF-X]` are handled procedurally and not recursively.  
We go through all of the characters in the current state string and apply the current rules.  
If the state is `FF` and the rule is `F+F` then state+1 would be `F+FF+F`.  
  
Once we have gone through all of the rules for all of the states for the given number of iterations we can go on to draw the final state onto the image.  
As most classic implementation, we also use a "turtle" to draw with. It's just a point in space.  
Each rule like `F` or `X` draws a line or fills an circle with a color.  
Rules like `-` and `+` rotates the turtle direction for the drawing.  

The program outputs `*.ppm` images, and they are not viewable online but you should be able to view them on whatever OS you have.

## Some Select Example outputs:
More outputs can be found in the `img/` directory.  

![one](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_1.png)  
![four](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_4.png)  
![seven](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_7.png)  
![eleven](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_11.png)  
![fifteen](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_15.png)  
![twenty](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_20.png)  
![twentythree](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_23.png)  
![thirty](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_30.png)  
![thirtythree](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_33.png)  
![thirtyfive](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_35.png)  
![fortysix](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_46.png)  
Here we can see the basis of the basic L-System rules currently implemented.  
![sixtyone](https://github.com/Rackhamn/L-System-One/blob/main/img/lsys_img_61.png)  
