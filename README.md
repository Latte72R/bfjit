# Brainf_ck JIT Compiler

This is a JIT compiler for the Brainf\_ck programming language, implemented in C using LLVM. It takes a Brainf\_ck program as input and compiles it to machine code at runtime, allowing for fast execution of Brainf\_ck programs.

## Benchmarks

The benchmark results comparing it to unoptimized Brainf\_ck implementations written in JavaScript and C are as follows:

<!-- benchmark:start -->
```text
Benchmark 1: ./build/bfjit ./examples/mandelbrot.b.txt
  Time (mean ± σ):      1.461 s ±  0.005 s    [User: 1.442 s, System: 0.019 s]
  Range (min … max):    1.455 s …  1.470 s    10 runs
 
Benchmark 2: /tmp/Brainfuck/extras/hydrogen8 ./examples/mandelbrot.b.txt
  Time (mean ± σ):      2.717 s ±  0.048 s    [User: 2.716 s, System: 0.001 s]
  Range (min … max):    2.600 s …  2.784 s    10 runs
 
Benchmark 3: ./build/bfjit ./examples/hanoi.b.txt
  Time (mean ± σ):     997.3 ms ±  14.6 ms    [User: 961.8 ms, System: 35.1 ms]
  Range (min … max):   980.9 ms … 1019.9 ms    10 runs
 
Benchmark 4: /tmp/Brainfuck/extras/hydrogen8 ./examples/hanoi.b.txt
  Time (mean ± σ):      19.7 ms ±   0.3 ms    [User: 18.9 ms, System: 0.7 ms]
  Range (min … max):    19.1 ms …  20.3 ms    10 runs
 
Benchmark 5: ./build/bfjit ./build/benchmark_cases/deep_nesting_512.bf
  Time (mean ± σ):      1.805 s ±  0.046 s    [User: 1.744 s, System: 0.060 s]
  Range (min … max):    1.765 s …  1.890 s    10 runs
 
Benchmark 6: /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/deep_nesting_512.bf
  Time (mean ± σ):     802.0 µs ±  29.9 µs    [User: 421.9 µs, System: 287.8 µs]
  Range (min … max):   763.3 µs … 851.2 µs    10 runs
 
Benchmark 7: ./build/bfjit ./build/benchmark_cases/arith_pipeline_4k.bf
  Time (mean ± σ):     12.082 s ±  0.145 s    [User: 11.537 s, System: 0.543 s]
  Range (min … max):   11.701 s … 12.199 s    10 runs
 
Benchmark 8: /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/arith_pipeline_4k.bf
  Time (mean ± σ):      10.3 ms ±   0.1 ms    [User: 8.1 ms, System: 2.1 ms]
  Range (min … max):    10.2 ms …  10.6 ms    10 runs
 
Benchmark 9: ./build/bfjit ./build/benchmark_cases/copy_restore_2k.bf
  Time (mean ± σ):      3.443 s ±  0.031 s    [User: 3.381 s, System: 0.061 s]
  Range (min … max):    3.415 s …  3.515 s    10 runs
 
Benchmark 10: /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/copy_restore_2k.bf
  Time (mean ± σ):       8.7 ms ±   0.1 ms    [User: 7.3 ms, System: 1.3 ms]
  Range (min … max):     8.5 ms …   8.8 ms    10 runs
 
Summary
  /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/deep_nesting_512.bf ran
   10.80 ± 0.41 times faster than /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/copy_restore_2k.bf
   12.87 ± 0.51 times faster than /tmp/Brainfuck/extras/hydrogen8 ./build/benchmark_cases/arith_pipeline_4k.bf
   24.61 ± 0.99 times faster than /tmp/Brainfuck/extras/hydrogen8 ./examples/hanoi.b.txt
 1243.51 ± 49.76 times faster than ./build/bfjit ./examples/hanoi.b.txt
 1821.90 ± 68.12 times faster than ./build/bfjit ./examples/mandelbrot.b.txt
 2250.37 ± 101.75 times faster than ./build/bfjit ./build/benchmark_cases/deep_nesting_512.bf
 3388.19 ± 139.90 times faster than /tmp/Brainfuck/extras/hydrogen8 ./examples/mandelbrot.b.txt
 4292.95 ± 164.63 times faster than ./build/bfjit ./build/benchmark_cases/copy_restore_2k.bf
15065.70 ± 589.66 times faster than ./build/bfjit ./build/benchmark_cases/arith_pipeline_4k.bf
```
<!-- benchmark:end -->

## License

This project is licensed under the MIT License.
