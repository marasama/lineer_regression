#ifndef A_PLOT
#define A_PLOT

#include <iostream>
#include <string>
#include <vector>
#include "A_Plot_macro.hpp"

struct Plot
{
    std::vector<double> x;
    std::vector<double> y;
    std::string style;
    std::string title;
    std::string color;
    int lineWidth;

    Plot(const std::vector<double> &xVals,
         const std::vector<double> &yVals,
         const std::string &plotStyle,
         const std::string &plotTitle,
         const std::string &lineColor = "black",
         int width = 1)
        : x(xVals), y(yVals), style(plotStyle),
          title(plotTitle), color(lineColor), lineWidth(width)
    {
    }
};

class A_Plot
{
  private:
    FILE *plot_pipe;
  public:
    A_Plot();
    ~A_Plot();

    int init();
    void plot(const Plot &plotObj);
    void plotMultiple(const std::vector<Plot> &plots);
    void setLabel(const std::string &axis, const std::string &label);
    void setTitle(const std::string &title);

    Plot createLinePlotX(double slope,
      double intercept,
      double startX,
      double endX,
      const std::string &title = "Line",
      const std::string &color = "black",
      int lineWidth = 1);

    Plot createLinePlotY(double slope,
          double intercept,
          double startY,
          double endY,
          const std::string &title = "Line",
          const std::string &color = "black",
          int lineWidth = 1);
    };

#endif