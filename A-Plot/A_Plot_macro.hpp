#define X_LABEL "xlabel"
#define Y_LABEL "ylabel"
// SCATTER_PLOT:
// This macro represents the GNUPlot plotting style "points",
// which is used to create scatter plots (i.e., individual data points with no connecting lines).
// Example:
//     plot.plot(x, y, SCATTER_PLOT);
#define SCATTER_PLOT "points"

// LINE_PLOT:
// This style draws a continuous line between data points.
// It is commonly used to show trends or functional relationships.
// Example:
//     plot.plot(x, y, LINE_PLOT);
#define LINE_PLOT "lines"

// LINE_POINTS_PLOT:
// This combines both a line and visible data points.
// Useful when you want to show both the data and the shape of the curve clearly.
// Example:
//     plot.plot(x, y, LINE_POINTS_PLOT);
#define LINE_POINTS_PLOT "linespoints"

// IMPULSE_PLOT:
// This style creates vertical lines from the x-axis to each data point (like a signal).
// Often used in signal processing or stem plots.
// Example:
//     plot.plot(x, y, IMPULSE_PLOT);
#define IMPULSE_PLOT "impulses"

// HISTOGRAM_PLOT:
// Uses filled bars to represent data values (GNUPlot calls this "boxes").
// Ideal for visualizing frequencies or categorical data.
// Example:
//     plot.plot(x, y, HISTOGRAM_PLOT);
#define HISTOGRAM_PLOT "boxes"