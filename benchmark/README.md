JS と C で書いたベンチマーク (最適化なし)

## Structure

- `bf.c`: 以前の比較対象として使っていた素朴な C 実装
- `bf.js`: 比較対象の素朴な JavaScript 実装
- `suite.py`: 速度測定用の合成ベンチケースを生成するスクリプト
- `hydrogen`: `https://github.com/rdebath/Brainfuck` の `extras/hydrogen.c` からビルドする比較対象

## Covered cases

- 実プログラム: `mandelbrot`, `hanoi`
- 実用拡大型: `mandelbrot_x2`, `hanoi_x2`
- 構文ストレス: `deep_nesting_512`
- ポインタ移動ストレス: `wide_sweep_24k_x128`
- 算術パイプライン: `arith_pipeline_4k`
- コピー/復元イディオム: `copy_restore_2k`

## Usage

```sh
git clone https://github.com/rdebath/Brainfuck /tmp/Brainfuck
cmake -S . -B build
cmake --build build
ctest --test-dir build -L benchmark --output-on-failure
```

必要に応じて `-DBFJIT_HYDROGEN_SOURCE_DIR=/path/to/Brainfuck/extras` を指定してください。

`benchmark` ラベルのテストは `bfjit` と `hydrogen8` の両方に対して同じ入力群を流し、短すぎるケースを避けつつ、構文の深さ・ポインタ走査・典型的なループイディオム・実プログラムをまとめて比較できる構成になっています。
