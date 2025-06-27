#include "A_Plot.hpp"
#include <stdexcept>
#include <stdlib.h>

A_Plot::A_Plot() : plot_pipe(nullptr)
{
    init();
}

A_Plot::~A_Plot()
{
    if (plot_pipe)
    {
        pclose(plot_pipe);
        plot_pipe = nullptr;
    }
}

int A_Plot::init()
{
    plot_pipe = popen("gnuplot -persist", "w");
    if (!plot_pipe)
    {
        std::cerr << "Failed to open gnuplot pipe." << std::endl;
        return (1);
    }
    return (0);
}

Plot A_Plot::createLinePlotX(double slope,
    double intercept,
    double startX,
    double endX,
    const std::string &title,
    const std::string &color,
    int lineWidth)
{
    std::vector<double> x = {startX, endX};
    std::vector<double> y = {
    slope * startX + intercept,
    slope * endX + intercept
    };

    return Plot(x, y, LINE_PLOT, title, color, lineWidth);
}

Plot A_Plot::createLinePlotY(double slope,
    double intercept,
    double startY,
    double endY,
    const std::string &title,
    const std::string &color,
    int lineWidth)
{
    if (slope == 0.0)
    {
    std::cerr << "Cannot create vertical line when slope is zero." << std::endl;
    return Plot({}, {}, LINE_PLOT, title, color, lineWidth);
    }

    std::vector<double> y = {startY, endY};
    std::vector<double> x = {
    (startY - intercept) / slope,
    (endY - intercept) / slope
    };

    return Plot(x, y, LINE_PLOT, title, color, lineWidth);
}

void A_Plot::plot(const Plot &plotObj)
{
    if (!plot_pipe || plotObj.x.size() != plotObj.y.size())
    {
        std::cerr << "Invalid plot call: null pipe or mismatched data size.\n";
        return;
    }

    fprintf(plot_pipe, "plot '-' with %s linecolor rgb \"%s\" linewidth %d title \"%s\"\n",
            plotObj.style.c_str(),
            plotObj.color.c_str(),
            plotObj.lineWidth,
            plotObj.title.c_str());

    for (size_t i = 0; i < plotObj.x.size(); ++i)
    {
        fprintf(plot_pipe, "%f %f\n", plotObj.x[i], plotObj.y[i]);
    }

    fprintf(plot_pipe, "e\n");
    fflush(plot_pipe);
}

void A_Plot::plotMultiple(const std::vector<Plot> &plots)
{
    if (!plot_pipe || plots.empty())
    {
        std::cerr << "Invalid multi-plot call.\n";
        return;
    }

    fprintf(plot_pipe, "plot ");
    for (size_t i = 0; i < plots.size(); ++i)
    {
        const Plot &p = plots[i];
        fprintf(plot_pipe, "'-' with %s linecolor rgb \"%s\" linewidth %d title \"%s\"",
                p.style.c_str(),
                p.color.c_str(),
                p.lineWidth,
                p.title.c_str());

        if (i < plots.size() - 1)
        {
            fprintf(plot_pipe, ", ");
        }
    }
    fprintf(plot_pipe, "\n");

    for (const auto &p : plots)
    {
        for (size_t j = 0; j < p.x.size(); ++j)
        {
            fprintf(plot_pipe, "%f %f\n", p.x[j], p.y[j]);
        }
        fprintf(plot_pipe, "e\n");
    }

    fflush(plot_pipe);
}

void A_Plot::setLabel(const std::string &axis, const std::string &label)
{
    if (plot_pipe)
    {
        fprintf(plot_pipe, "set %s \"%s\"\n", axis.c_str(), label.c_str());
    }
}

void A_Plot::setTitle(const std::string &title)
{
    if (plot_pipe)
    {
        fprintf(plot_pipe, "set title \"%s\"\n", title.c_str());
    }
}