#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
#include <iomanip>

struct Point {
	int x;
	int y;

	Point(int x, int y) : x(x), y(y) {};
};

Point *start_p;

int cross_prod(Point &v1, Point &v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

Point *previous(std::stack<Point *> &s) {
	Point *top = s.top();
	s.pop();
	Point *prev = s.top();
	s.push(top);
	return prev;
}


int distance(Point *p1, Point *p2) {
	return std::pow(p1->x - p2->x, 2) + std::pow(p1->y - p2->y, 2);
}

int orientation_angle(Point *p0, Point *p1, Point *p2) {
	Point v1 = Point(p1->x - p0->x, p1->y - p0->y);
	Point v2 = Point(p2->x - p0->x, p2->y - p0->y);
	int orientation = cross_prod(v1, v2);

	if (!orientation) return 0;
	return orientation < 0 ? -1 : 1;

}

bool cmp_orientation(Point *p1, Point *p2) {
	int angle = orientation_angle(start_p, p1, p2);
	if (!angle) return distance(start_p, p1) <= distance(start_p, p2);
	return angle > 0;
}

void remove_collinear(std::vector<Point *> &points) {
	int idx = 1;
	for (int i = 1; i < points.size(); i++) {
		while (i + 1 < points.size() && !orientation_angle(start_p, points[i], points[i + 1])) i++;
		std::swap(points[i], points[idx++]);
	}

	for (int i = idx; i < points.size(); i++) delete points[i];
	points.resize(idx);
}

double cross_prod_area(Point *a, Point *b, Point *c) {
	Point v1 = Point(b->x - a->x, b->y - a->y);
	Point v2 = Point(c->x - a->x, c->y - a->y);
	return std::abs(cross_prod(v1, v2)) * 1.0 / 2;
}

double hull_area(std::stack<Point *> &hull) {
	double area = 0;
	Point *a = start_p;
	Point *b;
	Point *c = hull.top();
	hull.pop();

	while (hull.size() > 1) {
		b = c;
		c = hull.top();
		hull.pop();
		area += cross_prod_area(a, b, c);
	}
	return area;
}

double convex_hull_area(std::vector<Point *> &points) {
	start_p = points[0];
	int l_i = 0;
	for (int i = 1; i < points.size(); i++) {
		Point *current = points[i];
		if (current->y < start_p->y || (current->y == start_p->y && current->x < start_p->x)) {
			start_p = current;
			l_i = i;
		}
	}

	std::swap(points[0], points[l_i]);
	std::sort(points.begin() + 1, points.end(), cmp_orientation);
	remove_collinear(points);

	std::stack<Point *> s;
	for (int i = 0; i < 3; i++) s.push(points[i]);

	for (int i = 3; i < points.size(); i++) {
		while (s.size() > 1 && orientation_angle(previous(s), s.top(), points[i]) != 1) {
			s.pop();
		}
		s.push(points[i]);
	}

	return hull_area(s);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	std::vector<Point *> points;
	int n;
	std::cin >> n;

	int x, y;
	for (int i = 0; i < n; i++) {
		std::cin >> x >> y;
		points.push_back(new Point(x, y));
	}

	std::cout << std::fixed << std::setprecision(3) << convex_hull_area(points) << "\n";

	for (Point *p: points) delete p;
	return 0;
}