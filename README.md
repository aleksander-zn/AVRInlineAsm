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

This approach has the following implications:

*   It is rather unlikely that the compiler will change anything within an `asm`
    statement as it doesn't even check whether the code assembles correctly.

*   However, if you do not use any of the output operands, the compiler is
    allowed to remove your `asm` code entirely.

*   Similary, if you place an `asm` statement inside a loop where it is always
    'called' with the same input operands, the compiler will likely move that
    code before (or after) the loop.

To tell the compiler that the result of executing your `asm` code depends on
something that is not listed as an input operand (e.g. the state of a
microcontroller's pin) or on the other hand, that results may vary even if
input operands do not change, you should use the `volatile` keyword.

This is also the case when your `asm` statement has some side effects (e.g it
changes the state of a pin, writes to some SFR).

Any statement that has no output operands is *implicitly volatile*.
