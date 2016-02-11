AVRInlineAsm
============

This project is intended to be a set of source files making use of the GCC's
inline assembly feature.

I'm going rather to include practical (or showing how it works/why you need to
do it this way) examples as you can find the theory on the net.

I'll try to keep all the files clear and well-commented but don't be afraid to
ask if you have any questions or something needs extra explanation.

How Is Inline Assembly Seen by the Compiler?
--------------------------------------------

Whenever you use inline assembly the compiler threats it as a kind of blackbox
that takes some data, processes it and produces some output.
