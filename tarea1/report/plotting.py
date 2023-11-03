import pandas as pd
import plotly.graph_objects as go


def build_lines_fig(
    means: pd.DataFrame,
    title: str = None,
    yaxis_title: str = None,
    scale: str = "linear",
) -> go.Figure:
    fig = go.Figure()

    fig.add_trace(
        go.Scatter(
            x=means.index,
            y=means["nearestx"],
            name="Nearest X",
            mode="lines",
            line=dict(color="rgb(31, 119, 180)"),
        )
    )

    fig.add_trace(
        go.Scatter(
            x=means.index,
            y=means["hilbert"],
            name="Hilbert Curve",
            mode="lines",
            line=dict(color="rgb(255, 127, 14)"),
        )
    )

    fig.add_trace(
        go.Scatter(
            x=means.index,
            y=means["sort_tile_recursive"],
            name="Sort Tile Recursive",
            mode="lines",
            line=dict(color="rgb(44, 160, 44)"),
        )
    )

    fig.update_layout(
        title=title,
        xaxis_title="Number of points",
        yaxis_title=yaxis_title,
        yaxis_type=scale,
        legend_title="Algorithm",
    )
    fig.update_xaxes(tickangle=0)

    return fig


def build_comparison_boxplot(
    means: pd.DataFrame,
    title: str = None,
    yaxis_title: str = None,
    scale: str = "linear",
) -> go.Figure:
    """
    Uses plotly to plot the execution time for each algorithm.
    Plots all 3 box plots in the same figure in log scale.
    """

    fig = go.Figure()

    fig.add_trace(
        go.Box(
            y=means["nearestx"],
            name="Nearest X",
            boxmean=True,
            marker_color="darkorange",
            boxpoints="all",
            jitter=0.2,
            pointpos=-1.8,
        )
    )

    fig.add_trace(
        go.Box(
            y=means["hilbert"],
            name="Hilbert Curve",
            boxmean=True,
            marker_color="darkblue",
            boxpoints="all",
            jitter=0.2,
            pointpos=-1.8,
        )
    )

    fig.add_trace(
        go.Box(
            y=means["sort_tile_recursive"],
            name="Sort Tile Recursive",
            boxmean=True,
            marker_color="darkgreen",
            boxpoints="all",
            jitter=0.2,
            pointpos=-1.8,
        )
    )

    fig.update_layout(
        title=title,
        xaxis_title="Bulk Load Algorithm",
        yaxis_title=yaxis_title,
        yaxis_type=scale,
    )

    return fig
