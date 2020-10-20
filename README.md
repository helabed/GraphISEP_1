# GraphISEP_1
Graphically Interactive Structural Engineering Program - One (GraphISEP 1)

This program was part of my Master's of Engineering thesis at the University of Wisconsin - Madison (1991)

[The Application of the Object Oriented Programming Paradigm In Developing Structural Engineering Computer programs](https://drive.google.com/file/d/1K8eX76825fJd8Y4yKsxIHGSn5zcTPYPX/view)

GraphISEP One was developed in 1990 with `Think C with Objects` and the `Think Class Library`. It is about 22,000 lines of code (not including the Class Library).

GrahpISEP One allowed the user of the application to layout and design structural wood trusses connected with Gusset Plates (with spikes) - the same as those used in residential and light commercial floor and roof trusses. GraphISEP One communicated with a backend Fortran program that crunched the number to validate that the trusses were sound for the given load applied on them (such as floor, snow, wind loads, etc...). 

`Think C with Objects` was the first incarnation of `Objective-C` and eventually became [Symantec C++ with the Think Class Library (TCL)](https://en.wikipedia.org/wiki/THINK_C).

This was my first massive body of work before graduating and becoming an engineer then a programmer.

This was before any version control system existed - i.e no CVS, no SVN, and definitely no Git or Github.

We kept track of changes mentally and backed up our application folder/directory very frequently to external hard disks. (or floppy disks)

Chapter 3 and 4 of my Master's Thesis (above) have a gazzillion screenshots of how GraphISEP One worked. And the class names in the thesis match those in the code of this project.

Chapter 5 of my Master's Thesis (above) gives an overview of how the `Direct Stiffness Method` can be used to gather the Global Stiffness and Global Forces matrices and calculate the displacement matrix and thus the stresses applied on the structure (wood truss in this case).

The `Direct Stiffness Method (DSM)` is a specialized/simplified version of the `Finite Element Analysis (FEA)` method when using beams, columns and trusses where the axial, shear and flexural behavior(moments) of such elements is more predictable than the 2-Dimensional plates and 3-Dimensional generic elements used by FEA.

Enjoy !
