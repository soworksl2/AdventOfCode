This project may look disorganized, and in fact, it is disorganized. But we’ll be shaping it up later. If you want more context, this repository is for my YouTube series on solving the Advent of Code in different programming languages.

My [YouTube channel](https://www.youtube.com/@jvivas-code)

the [Advent of Code 2015 Playlist](https://www.youtube.com/playlist?list=PLLkeQ2g_xcvVe7TDZxytR1Y5SmLstD3LE)

# How to Build

Yo have to generate the build with CMAKE.

you can use (`SOW_STD_EXAMPLES` cmake variable to `OFF`) if you do not want to compile the standard library examples.

then go to the generated build directory and do `make` or IDK. build the project with the tools you selected.

# TODO

- name the functions a little bit better bro.
- `S_split` have segfault if the str passed is null!.
- in MAX, MIN, macros, please, cast data to the corresponding type to ensure void* arrays works ok. in smath.h
- `S_to_hex_format` needs refactor weird unsigned char, just build and you will see.
