#!/usr/bin/env python3

import argparse
from pathlib import Path


def repeat_example(root, relative_path, repeat):
    return (root / relative_path).read_text(encoding="ascii") * repeat


def make_deep_nesting(depth):
    return "+" + ("[" * depth) + "-" + ("]" * depth) + "\n"


def make_wide_sweep(width, passes):
    return ("+" * passes) + "[" + (">" * width) + ("<" * width) + "-]\n"


def make_arith_pipeline(repeat):
    kernel = ">++++[>++++<-]>[<+>-]<[-]<"
    return (kernel * repeat) + "\n"


def make_copy_restore(repeat):
    kernel = ">++++[>++++<-]>[->+>+<<]>>[-<<+>>]<[-]<[-]<<"
    return (kernel * repeat) + "\n"


def generated_cases(root):
    return (
        {
            "name": "mandelbrot_x2",
            "description": "practical workload based on mandelbrot, repeated 2x",
            "program": lambda: repeat_example(root, "examples/mandelbrot.b.txt", 2),
        },
        {
            "name": "hanoi_x2",
            "description": "practical workload based on hanoi, repeated 2x",
            "program": lambda: repeat_example(root, "examples/hanoi.b.txt", 2),
        },
        {
            "name": "deep_nesting_512",
            "description": "syntax-heavy nesting stress with depth 512",
            "program": lambda: make_deep_nesting(512),
        },
        {
            "name": "wide_sweep_24k_x128",
            "description": "large pointer sweep within tape limits, repeated 128 passes",
            "program": lambda: make_wide_sweep(24000, 128),
        },
        {
            "name": "arith_pipeline_4k",
            "description": "large arithmetic and transfer pipeline repeated 4096 times",
            "program": lambda: make_arith_pipeline(4096),
        },
        {
            "name": "copy_restore_2k",
            "description": "copy and restore loop idiom repeated 2048 times",
            "program": lambda: make_copy_restore(2048),
        },
    )


def cmd_generate(output_dir):
    root = Path(__file__).resolve().parents[1]
    output_dir.mkdir(parents=True, exist_ok=True)

    for case in generated_cases(root):
        path = output_dir / (case["name"] + ".bf")
        path.write_text(case["program"](), encoding="ascii")

    return 0


def build_parser():
    parser = argparse.ArgumentParser(
        description="Generate synthetic Brainf_ck benchmark cases."
    )
    subparsers = parser.add_subparsers(dest="command")

    generate_parser = subparsers.add_parser("generate")
    generate_parser.add_argument("output_dir", type=Path)

    return parser


def main():
    parser = build_parser()
    args = parser.parse_args()

    if args.command is None:
        parser.print_help()
        return 2

    if args.command == "generate":
        return cmd_generate(args.output_dir)

    parser.error("unsupported command: {}".format(args.command))
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
