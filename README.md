# Project0-Compi
Students:
Jose Pablo Fernández Cubillo, 2019047740
Roberto Vidal Patiño, 2019065537

There are two makefiles:
1) The one inside folder "Compiler" compiles the compiler, which
   creates a file to be run like ./compiler on console
2) The one that is outside, next to the folders "Compiler" and
   "Test Programs", is for assembling the .s programs that result
   fron the compilation of the micro program
   
When executing the compiler (./compiler) the name of the file to
be compiled is requested, it would look something like:

Enter file name: program.txt

Where program.txt is the name of the file to compile. It is
recommended to only use files with the .txt extension, since
this is the type of file used for the test we did. The result
is a .s program.

To assemble the resulting .s program one must use the second
makefile where a parameter for the name of the file should be
inserted. So, running the makefile for the .s program would look
like this:

makefile name=program

Note that one must not insert the file extension only the name
of the file, also the file must be in the same location of the
makefile, or at least this is the way we tested it.
