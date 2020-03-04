graphics_toolkit ("gnuplot");
format long;
output_precision = 1;

d = [4.0,4.0,6.0,0.0,0.0;0.0,0.0,8.0,6.0,0.0;0.0,0.0,0.0,0.0,2.0];
barh (d, "stacked");
set (gca (), "ydir", "reverse");
xlabel ("Time");
ylabel ("Machines");
title ("Diagram");
legend ({"Z1","Z2","Z3","Z4","Z5"}, "location", "eastoutside");
print -dpng output/optimize_diagram.png;
open output/optimize_diagram.png;