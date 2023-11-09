from pathlib import Path

import pandas as pd


def load_mergesort_results(path: Path):
    """Takes a path to a directory containing the results of the merge sort
    algorithm and returns a DataFrame with the results.
    """

    if not path.is_dir():
        raise ValueError(f"{path} is not a directory")

    if not len(list(path.glob("*.csv"))):
        raise ValueError(f"{path} is empty")

    lines = []
    for file in path.glob("*.csv"):
        data = file.read_text().strip().split(",")
        lines.append(tuple(data))
    universes, experiments, times = zip(*lines)

    df = pd.DataFrame(
        {
            "universe": universes,
            "experiment": experiments,
            "time": times,
        }
    )
    df["universe"] = df["universe"].astype(int)
    df["experiment"] = df["experiment"].astype(int)
    df["time"] = df["time"].astype(float)
    df.sort_values(["universe", "experiment"], inplace=True)
    return df


def load_radixsort_results(path: Path):
    """Takes a path to a directory containing the results of the radix sort
    algorithm and returns a DataFrame with the results.
    """
    if not path.is_dir():
        raise ValueError(f"{path} is not a directory")

    if not len(list(path.glob("*.csv"))):
        raise ValueError(f"{path} is empty")

    lines = []
    for file in path.glob("*.csv"):
        data = file.read_text().strip().split(",")
        lines.append(tuple(data))
    universes, bucket_size, experiments, times = zip(*lines)

    df = pd.DataFrame(
        {
            "universe": universes,
            "bucket_size": bucket_size,
            "experiment": experiments,
            "time": times,
        }
    )
    df["universe"] = df["universe"].astype(int)
    df["bucket_size"] = df["bucket_size"].astype(int)
    df["experiment"] = df["experiment"].astype(int)
    df["time"] = df["time"].astype(float)
    df.sort_values(["universe", "bucket_size", "experiment"], inplace=True)
    return df
