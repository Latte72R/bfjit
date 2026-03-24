# Brainf_ck JIT Compiler

This is a JIT compiler for the Brainf\_ck programming language, implemented in C using LLVM. It takes a Brainf\_ck program as input and compiles it to machine code at runtime, allowing for fast execution of Brainf\_ck programs.

## Benchmarks

The benchmark results comparing it to unoptimized Brainf\_ck implementations written in JavaScript and C are as follows:

<!-- benchmark:start -->
```text
Benchmark 1: ./build/bfjit ./examples/hanoi.b.txt
  Time (mean ± σ):     821.2 ms ±  11.3 ms    [User: 783.0 ms, System: 37.7 ms]
  Range (min … max):   811.3 ms … 848.5 ms    10 runs
 
Benchmark 2: ./build/simple_c ./examples/hanoi.b.txt
  Time (mean ± σ):     11.240 s ±  0.195 s    [User: 11.237 s, System: 0.002 s]
  Range (min … max):   10.815 s … 11.535 s    10 runs
 
Benchmark 3: bun ./benchmark/bf.js ./examples/hanoi.b.txt
  Time (mean ± σ):     27.051 s ±  0.927 s    [User: 27.055 s, System: 0.035 s]
  Range (min … max):   24.423 s … 27.490 s    10 runs
 
Summary
  ./build/bfjit ./examples/hanoi.b.txt ran
   13.69 ± 0.30 times faster than ./build/simple_c ./examples/hanoi.b.txt
   32.94 ± 1.22 times faster than bun ./benchmark/bf.js ./examples/hanoi.b.txt
```
<!-- benchmark:end -->

## License

This project is licensed under the MIT License.
