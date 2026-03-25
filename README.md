# Brainf_ck JIT Compiler

This is a JIT compiler for the Brainf\_ck programming language, implemented in C using LLVM. It takes a Brainf\_ck program as input and compiles it to machine code at runtime, allowing for fast execution of Brainf\_ck programs.

## Benchmarks

The benchmark results comparing it to unoptimized Brainf\_ck implementations written in JavaScript and C are as follows:

<!-- benchmark:start -->
```text
Benchmark 1: ./build/bfjit ./build/benchmark_cases/mandelbrot_x2.bf
  Time (mean ± σ):      3.081 s ±  0.010 s    [User: 3.049 s, System: 0.032 s]
  Range (min … max):    3.066 s …  3.094 s    10 runs
 
Benchmark 2: /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/mandelbrot_x2.bf
  Time (mean ± σ):      5.429 s ±  0.076 s    [User: 5.427 s, System: 0.001 s]
  Range (min … max):    5.337 s …  5.592 s    10 runs
 
Benchmark 3: ./build/bfjit ./build/benchmark_cases/hanoi_x2.bf
  Time (mean ± σ):      2.346 s ±  0.029 s    [User: 2.286 s, System: 0.060 s]
  Range (min … max):    2.286 s …  2.400 s    10 runs
 
Benchmark 4: /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/hanoi_x2.bf
  Time (mean ± σ):      38.6 ms ±   0.1 ms    [User: 37.7 ms, System: 0.8 ms]
  Range (min … max):    38.5 ms …  38.7 ms    10 runs
 
Summary
  /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/hanoi_x2.bf ran
   60.77 ± 0.75 times faster than ./build/bfjit ./build/benchmark_cases/hanoi_x2.bf
   79.81 ± 0.29 times faster than ./build/bfjit ./build/benchmark_cases/mandelbrot_x2.bf
  140.61 ± 1.97 times faster than /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/mandelbrot_x2.bf
```
<!-- benchmark:end -->

## License

This project is licensed under the MIT License.
