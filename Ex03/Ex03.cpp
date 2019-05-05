#include "Picture.h"
#include "SpiralPolygon.h"


int main() {
	PenPolygon* poly = new PenPolygon(15,15, M_PI_4/2, RED);

	for (int i = 0; i < 7; ++i)
	{
		poly->move(10);
		poly->turn(M_PI_4);
	}

	Polygon* poly1 = new SpiralPolygon(8, 255, 2, 0, 0, 25, 0, 1, M_PI_4);
	Polygon* poly2 = new SpiralPolygon(80, 255, 8, 100, 50, 1, 0, 1.1, M_PI_4);

	Picture pic;
	pic.add(poly);
	pic.add(poly1);
	pic.add(poly2);

	pic.draw(400, 300, 800, 600, 0.25);
	pic.draw(400, 300, 800, 600, 0.5);
	pic.draw(400, 300, 800, 600, 0.75);
	pic.draw(400, 300, 800, 600, 1);
	pic.draw(200, 150, 800, 600, 1);
	pic.draw(0, 0, 800, 600, 1);
	pic.draw(400, 300, 800, 600, 1.25);

	delete poly;
	delete poly1;
	delete poly2;
	return 0;
}
