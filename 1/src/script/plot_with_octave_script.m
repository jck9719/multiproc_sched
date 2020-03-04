graphics_toolkit ("gnuplot");
format long;
output_precision = 1;

d = [3.0,1.5,0.0;0.0,1.5,3.0];
barh (d, "stacked");
set (gca (), "ydir", "reverse");
xlabel ("Time");
ylabel ("Machines");
title ("Diagram");
legend ({"Z1","Z2","Z3"}, "location", "eastoutside");
print -dpng output/optimize_diagram.png;