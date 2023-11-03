from pathlib import Path

import pandas as pd


def inject_header(df: pd.DataFrame) -> pd.DataFrame:
    """
    Injects a header into the dataframe.
    Transforms the current header into the first row.
    """
    df = df.copy()
    header = [f"q{i}" for i in range(1, 101)]

    first_row = df.iloc[0].copy()
    df.columns = header
    df.index = df.index + 1
    df.iloc[0] = first_row

    return df


def inject_n_index(df: pd.DataFrame) -> pd.DataFrame:
    """
    Injects a index with the input size into the dataframe.
    """

    df = df.copy()
    # x
    powers_of_2 = [
        "2¹⁰",
        "2¹¹",
        "2¹²",
        "2¹³",
        "2¹⁴",
        "2¹⁵",
        "2¹⁶",
        "2¹⁷",
        "2¹⁸",
        "2¹⁹",
        "2²⁰",
        "2²¹",
        "2²²",
        "2²³",
        "2²⁴",
        "2²⁵",
    ]

    # df.index = [f"2^{i}" for i in range(10, 25)]
    df.index = powers_of_2
    return df


def load_data(path: Path) -> pd.DataFrame:
    """
    Loads data from a csv file and injects a header and
    a column with the input size.
    """
    df = pd.read_csv(path, usecols=range(100), header=None)
    df = inject_header(df)
    df = inject_n_index(df)
    return df.T
