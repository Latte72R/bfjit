# Brainf_ck JIT Compiler

This is a JIT compiler for the Brainf\_ck programming language, implemented in C using LLVM. It takes a Brainf\_ck program as input and compiles it to machine code at runtime, allowing for fast execution of Brainf\_ck programs.

## Benchmarks

The benchmark results comparing it to unoptimized Brainf\_ck implementations written in JavaScript and C are as follows:

<!-- benchmark:start -->
```text
Benchmark 1: ./build/bfjit ./examples/mandelbrot.b.txt
  Time (mean ± σ):      1.355 s ±  0.007 s    [User: 1.339 s, System: 0.015 s]
  Range (min … max):    1.347 s …  1.369 s    10 runs
 
Benchmark 2: /tmp/Brainfuck/extras/hydrogen8 ./examples/mandelbrot.b.txt
  Time (mean ± σ):      1.961 s ±  0.006 s    [User: 1.960 s, System: 0.001 s]
  Range (min … max):    1.955 s …  1.970 s    10 runs
 
Benchmark 3: ./build/bfjit ./examples/hanoi.b.txt
  Time (mean ± σ):     784.5 ms ±   6.1 ms    [User: 749.7 ms, System: 34.5 ms]
  Range (min … max):   776.0 ms … 793.1 ms    10 runs
 
Benchmark 4: /tmp/Brainfuck/extras/hydrogen8 ./examples/hanoi.b.txt
  Time (mean ± σ):      14.1 ms ±   0.1 ms    [User: 13.4 ms, System: 0.5 ms]
  Range (min … max):    13.9 ms …  14.2 ms    10 runs
 
Benchmark 5: ./build/bfjit ./build/benchmark_cases/deep_nesting_512.bf
  Time (mean ± σ):      13.5 ms ±   0.2 ms    [User: 7.7 ms, System: 5.6 ms]
  Range (min … max):    13.2 ms …  13.8 ms    10 runs
 
Benchmark 6: /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/deep_nesting_512.bf
  Time (mean ± σ):     601.1 µs ±  58.9 µs    [User: 254.1 µs, System: 279.4 µs]
  Range (min … max):   554.8 µs … 760.1 µs    10 runs
 
Benchmark 7: ./build/bfjit ./build/benchmark_cases/arith_pipeline_4k.bf
  Time (mean ± σ):     110.5 ms ±   0.8 ms    [User: 102.8 ms, System: 7.5 ms]
  Range (min … max):   109.8 ms … 112.3 ms    10 runs
 
Benchmark 8: /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/arith_pipeline_4k.bf
  Time (mean ± σ):       8.3 ms ±   0.1 ms    [User: 6.9 ms, System: 1.2 ms]
  Range (min … max):     8.1 ms …   8.6 ms    10 runs
 
Benchmark 9: ./build/bfjit ./build/benchmark_cases/copy_restore_2k.bf
  Time (mean ± σ):      56.9 ms ±   0.4 ms    [User: 48.2 ms, System: 8.4 ms]
  Range (min … max):    56.3 ms …  57.5 ms    10 runs
 
Benchmark 10: /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/copy_restore_2k.bf
  Time (mean ± σ):       6.9 ms ±   0.1 ms    [User: 5.6 ms, System: 1.2 ms]
  Range (min … max):     6.8 ms …   7.3 ms    10 runs
 
Summary
  /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/deep_nesting_512.bf ran
   11.55 ± 1.16 times faster than /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/copy_restore_2k.bf
   13.73 ± 1.37 times faster than /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/arith_pipeline_4k.bf
   22.54 ± 2.23 times faster than ./build/bfjit ./build/benchmark_cases/deep_nesting_512.bf
   23.41 ± 2.30 times faster than /tmp/Brainfuck/extras/hydrogen8 ./examples/hanoi.b.txt
   94.66 ± 9.30 times faster than ./build/bfjit ./build/benchmark_cases/copy_restore_2k.bf
  183.87 ± 18.07 times faster than ./build/bfjit ./build/benchmark_cases/arith_pipeline_4k.bf
 1305.15 ± 128.34 times faster than ./build/bfjit ./examples/hanoi.b.txt
 2253.35 ± 221.20 times faster than ./build/bfjit ./examples/mandelbrot.b.txt
 3262.07 ± 319.92 times faster than /tmp/Brainfuck/extras/hydrogen8 ./examples/mandelbrot.b.txt
```
<!-- benchmark:end -->

## License

This project is licensed under the MIT License.
