from pathlib import Path

import pandas as pd


def load_results(path: Path):
    """Takes a path to a directory containing the results of the merge sort
    algorithm and returns a DataFrame with the results.
    """

    if not path.is_dir():
        raise ValueError(f"{path} is not a directory")

    if not len(list(path.glob("*.csv"))):
        raise ValueError(f"{path} is empty")

    lines = []
    exp_nums = []
    for file in path.glob("*.csv"):
        data = file.read_text().strip().split(",")
        filename = file.name.split(".")[0]
        exp_num = filename.split("_")[2]
        if len(data) != 2:
            print(f"Skipping {file} due to invalid data")
            continue
        lines.append(tuple(data))
        exp_nums.append(exp_num)
    n, time = zip(*lines)

    df = pd.DataFrame(
        {
            "n": n,
            "time": time,
            "experiment": exp_nums,
        }
    )
    return df.reset_index(drop=True)
