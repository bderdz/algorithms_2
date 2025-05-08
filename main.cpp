//#include <iostream>
//#include <vector>
//
//struct Point {
//	int x;
//	int y;
//
//	Point(int x, int y) : x(x), y(y) {};
//};
//
//int cross_prod(Point *v1, Point *v2) {
//	return v1->x * v2->x - v1->y * v2->y;
//}
//
//bool cmp_cross_prod() {
//	return false;
//}
//
//int main() {
//	std::ios_base::sync_with_stdio(false);
//	std::cout.tie(nullptr);
//	std::cin.tie(nullptr);
//
//	std::vector<Point *> points;
//	int n;
//	std::cin >> n;
//
//	int x, y;
//	for (int i = 0; i < n; i++) {
//		std::cin >> x >> y;
//		points.push_back(new Point(x, y));
//	}
//
//	for (Point *p: points) {
//		delete p;
//	}
//	return 0;
//}