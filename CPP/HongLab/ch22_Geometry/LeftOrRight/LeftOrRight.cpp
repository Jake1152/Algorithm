#include "../draw_helper.h"

using namespace std;
using namespace cv;
using namespace hlab;

// https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/
// Click Materials Removed from 3e

int Direction(Point p0, Point p1, Point p2)
{
	int x0 = p0.x;
	int x1 = p1.x;
	int x2 = p2.x;
	int y0 = p0.y;
	int y1 = p1.y;
	int y2 = p2.y;

	return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);

	//return true; // TODO: 벡터곱(vector product, cross product) 사용
}

void DrawArrow(cv::Mat& image, Point line_start, Point line_end, cv::Scalar color)
{
	cv::Point temp = line_end - line_start;
	cv::line(image, line_start - temp * 1000, line_start + temp * 1000, cv::Scalar(200, 200, 200), 1, LINE_AA);
	cv::circle(image, line_start, 5, color, -1, LINE_AA);
	cv::arrowedLine(image, line_start, line_end, color, 1, LINE_AA);
}

int main(int argc, char** argv)
{
	hlab::initialize(1280, 960); // 그려질 화면의 해상도 (width, height)

	Point line_start = Point(640, 400);
	Point line_end = Point(640, 600);

	movable_points.push_back(&line_start);
	movable_points.push_back(&line_end);

	vector<Point> points;

	for (int i = 0; i < 30; i++)
		points.push_back(Point(rand() % image.cols, rand() % image.rows));

	points.push_back(Point(500, 500));

	for (auto& p : points)
		movable_points.push_back(&p);

	while (true)
	{
		hlab::preframe(); // 그리기 준비 작업
		// std::cout << "After hlab::preframe()" << std::endl;

		for (Point p : points)
		{
			// 양수면 왼쪽, 음수면 오른쪽, 0이면 직선 위에
			int cross = Direction(line_start, line_end, p);

			// cv::Scalar color = cross == 0 ? kBlack : cross > 0 ? kRed : kBlue;
			cv::Scalar color;
			if (cross == 0) {
				color = kBlack;
			} else if (cross > 0) {
				color = kRed;
			} else {
				color = kBlue;
			}

			cv::circle(image, p, 15, color, -1, LINE_AA);
		}
		// std::cout << "After for loop" << std::endl;
		// 마우스로 클릭한 물체 가장자리 그리기
		if (selected)
			cv::circle(image, *selected, 17, cv::Scalar(0, 255, 0), 1, LINE_AA);

		// 화살표 그리기
		DrawArrow(image, line_start, line_end, cv::Scalar(30, 30, 30));
		// std::cout << "After DrawArrow()" << std::endl;

		if (hlab::postframe()) break; // 그린 후에 마무리 작업, ESC 누르면 종료
		// std::cout << "After hlab::postframe()" << std::endl;
	}

	return 0;
}
