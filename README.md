# 🌌 N-Body Problem Implementations 🚀

Welcome to the n-body-implementations repository! Here, you'll find various implementations of the N-Body problem in different programming languages. All of these implementations have been translated to C using a large language model (GPT-4) within ChatGPT. 🤖

The original implementations were taken from ["The Computer Language Benchmarks Game"](https://github.com/hanabi1224/Programming-Language-Benchmarks/). 🎮

## ✨ Features

    🌟 Working translations: The translated code is functional and has been tested.
    📖 Readable code: The code is easy to read and understand.
    ⚡ Faster performance: The translated code is faster compared to the hand-written counterparts.

## 🐛 Bugs & Fixes

Although ChatGPT is pretty amazing, it's not always perfect. There was at least one instance where the produced code had an error. However, after asking ChatGPT, it was able to find the mistake and fix it. 🩹

## 🚧 Optimizations

We asked ChatGPT to create an optimized version of the C++ code, but it didn't quite work out. The execution time remained unchanged. 🕒

## 💡 Creating Code from Scratch

We also challenged ChatGPT to create the code from scratch by giving it detailed requirements. And guess what? It successfully delivered working code! 🎉

## 📚 Contents

This repository contains the following language implementations:

    C++
    Python
    Java
    Perl
    Ruby

Feel free to browse the code and experiment with it! If you find any issues or have suggestions for improvements, don't hesitate to submit an issue or a pull request. 📥

Happy coding! 🌠

## C++ benchmark

```bash
$ g++ -O2 -o nbody_cpp nbody.cpp
$ time ./nbody_cpp 5000000
-0.169075164
-0.169083134

real    0m0.684s
user    0m0.680s
sys     0m0.004s
```

## Translations

### Java

```bash
$ javac nbody.java
$ time java app 5000000
-0.169075164
-0.169083134

real    0m0.968s
user    0m0.942s
sys     0m0.020s
```

```
$ g++ -O2 -o nbody_translated_from_java nbody_translated_from_java.c
$ time ./nbody_translated_from_java 5000000
-0.169075164
-0.169083134

real    0m0.790s
user    0m0.790s
sys     0m0.000s
```

### Python

```bash
$ time python3 ./nbody.py 5000000
-0.169075164
-0.169083134

real    2m7.619s
user    2m7.316s
sys     0m0.008s
```

```
$ g++ -O2 -o nbody_translated_from_python nbody_translated_from_python.c
$ time ./nbody_translated_from_python 5000000
-0.169075164
-0.169083134

real    0m1.150s
user    0m1.149s
sys     0m0.000s
```

### Perl

```bash
$ time perl nbody.pl 5000000
-0.169075164
-0.169083134

real    0m38.948s
user    0m38.934s
sys     0m0.000s
```

```bash
$ g++ -O2 -o nbody_translated_from_perl nbody_translated_from_perl.c
$ time ./nbody_translated_from_perl 5000000
-0.169075164
-0.169083134

real    0m0.774s
user    0m0.773s
sys     0m0.000s
```

### Ruby

```bash
$ time ruby nbody.rb 5000000
-0.169075164
-0.169083134

real    0m35.989s
user    0m35.962s
sys     0m0.012s
```

```bash
$ g++ -O2 -o nbody_translated_from_ruby nbody_translated_from_ruby.c
$ time ./nbody_translated_from_ruby 5000000
-0.169075164
-0.169083134

real    0m0.889s
user    0m0.888s
sys     0m0.000s
```

The first try with the ruby translation actually give an error, you can find it in the repository:

```bash
$ g++ -O2 -o nbody_translated_from_ruby_wrong nbody_translated_from_ruby_wrong.c
$ time ./nbody_translated_from_ruby_wrong 5000000
-0.352827577
161039.070118648

real    0m0.900s
user    0m0.899s
sys     0m0.000s
```

I tell it to chatGPT which answered me back: 
> Apologies for the oversight. I found the error in the initialization of the sun's mass. The initialize_planet function is not being used, and the mass should be assigned directly in the array. Here is the corrected main function:

It was an error referred to the measurement units, you can see it:

```bash
$ diff nbody_translated_from_ruby*
```



## Optimization (did not work)

```bash
$ g++ -O2 -o nbody_optimized nbody_optimized.cpp
$ time ./nbody_optimized 5000000
-0.169075164
-0.169083134

real    0m0.781s
user    0m0.780s
sys     0m0.000s
```

The first iteration returned a segmentation fault. Confronted with it chatGPT said that:
> The segmentation fault may be due to accessing argv[1] when no command-line argument is provided. To fix this issue, we should add a check for the number of command-line arguments before accessing argv[1]. 

but segmentation fault occourred again. Confronted again it said:
>  I have identified the issue with the segmentation fault, which is caused by the use of a global std::array with const elements. Since we need to modify the solar system's bodies during the simulation, we can't declare them as const.

After that it worked, you can see the differences:
```bash
$ nbody_optimized.cpp nbody_optimized_segfault.cpp
```

## Generated code

I questioned chatGPT with the following prompt.
```
Write a c++ program for the n bodies problem taking into account the sun, jupiter, saturn, uranus, and neptune. For each celestial body you have to calculate its position and its velocity during different iterations, representing time. 

The program then calculates the offset of the center of mass of the solar system and applies it to the bodies to ensure that the center of mass of the system is stationary.

The program then calculates the total energy of the solar system using the positions and velocities of the planets and prints it out.

The program then runs a loop that updates the positions and velocities of the planets over time using numerical integration. The loop runs for a specified number of iterations that is passed in as a command-line argument.

After the loop completes, the program calculates the total energy of the solar system again and prints it out.

The code will simulate the motion of the solar system and calculates its energy over time.
```

I later specified that I wanted the gravitational constant in astronomical units (AU) to simplify the calculation.

I then specify explicitely the initial conditions, since the masses were right, but positions and velocities of the planets were not (you can find them commented out in the code).

The results are the following. The energy differs for the gravitational constant with respect to the previous data.

```
$ g++ -O2 -o nbody_generated nbody_generated.cpp
$ time ./nbody_generated 5000000
Initial energy: -0.004287908766
Final energy: -0.004286636787

real    0m2.659s
user    0m2.658s
sys     0m0.000s
```

## ⚙️ Infrastructure

All the tests were made on a `t2.micro` AWS instance with openSUSE Leap 15.4.
