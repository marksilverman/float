# float
This is a small program I wrote to help me understand how floating point numbers are encoded (as per IEEE 754).
- it decodes a single-precision (32-bit), small-endian floating point number
- aside from zero and negative zero, it doesn't understand any "special" numbers (like infinity or NaN)

The output looks like this:

     % ./float
    input: 3.14159
    in binary: 0b01000000010010010000111111011011

    s xxxxxxxx mmmmmmmmmmmmmmmmmmmmmmm
    0 10000000 10010010000111111011011

    sign (1-bit): 0
    exponent (8-bits): 0b10000000 - 0b1111111 = 1
    mantissa (23-bits): 0b10010010000111111011011

    lhs-of-radix: 0b11 --> 3
    rhs-of-radix: 0b0010010000111111011011 --> 0.141593
    result: 3.14159
    the result matches the input
     % 
