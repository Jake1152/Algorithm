#include "../shared/draw_helper.h"
#include "BalancedQuadtree.h"
#include "PathFinding.h"

using namespace std;
using namespace cv;
using namespace hlab;

#include <iostream>
#include <list>
#include <vector>
#include <limits>

using namespace std;
using namespace hlab;

struct Rectangle
{
	int x, y, width, height;

	bool IsInside(Point p)
	{
		if (p.x < x) return false;
		if (p.x >= x + width) return false;
		if (p.y < y) return false;
		if (p.y >= y + height) return false;
		return true;
	}
};

void DisplayQuadtree(Mat& image, BalancedQuadtree::Node* n)
{
	if (!n) return;

	bool has_child = false;
	for (auto* c : n->children)
		if (c)
			has_child = true;

	//if (has_child)
	//{
	//	cv::line(image, { n->x, n->y + n->height / 2 }, { n->x + n->width, n->y + n->height / 2 }, Scalar(217, 217, 214), 1, LINE_AA);
	//	cv::line(image, { n->x + n->width / 2, n->y }, { n->x + n->width / 2 , n->y + n->height }, Scalar(217, 217, 214), 1, LINE_AA);
	//}

	for (auto* c : n->children)
		if (c)
		{
			DisplayQuadtree(image, c);
		}

	cv::rectangle(image, Rect(n->x, n->y, n->width + 1, n->height + 1), Scalar(0, 102, 255), 1, LINE_4); // width/height + 1 주의

	//if (!has_child) // leaf node
	//	for (auto* adj : n->neighbors) // 이웃 노드들과의 연결선
	//		cv::line(image, { n->Center().x, n->Center().y }, { adj->Center().x, adj->Center().y }, Scalar(217, 217, 214), 1, LINE_4);

	//for (auto& p : n->objects)
	//{
	//	cv::circle(image, { p.x, p.y }, 5, Scalar(200, 200, 200), -1, LINE_AA);
	//}
}

int main(int argc, char** argv)
{
	hlab::initialize(1280, 960);

	Mat map = imread("../map1280x960.png", cv::IMREAD_COLOR); // 주의: map.png의 해상도와 화면 해상도가 같아야 합니다.
	cv::flip(map, map, 0);
	if (map.empty()) {
		cout << "Failed to read map.png file." << endl;
		return -1;
	}

	Point start_prev = { -1, -1 }; // 마우스 드래그로 인한 이동 확인용
	Point end_prev = { -1, -1 };   // 마우스 드래그로 인한 이동 확인용

	Point start_point = { 0, 0 };
	Point end_point = { map.cols - 1, map.rows - 1 };

	movable_points.push_back(&start_point);
	movable_points.push_back(&end_point);

	BalancedQuadtree qtree(0, 0, image.cols, image.rows, 6); // max_level이 너무 낮으면 지형을 제대로 반영하지 못해서 뚫고 가는 경우가 발생합니다.
	DijkstraShortestPaths d;

	while (true)
	{
		// 처음 시작할 때, 또는 시작점과 끝점이 이동했을 경우에 쿼드 트리와 그래프 새로 만들기
		if (!left_down && (start_prev != start_point || end_prev != end_point))
		{
			// TODO: 빈칸 채우기 용도라기 보다는, 
			//       지도 이미지 읽어들이는 방법을 자연스럽게 알려드리는 용도로 제공해드리는 코드입니다.
			qtree.DeleteAll();

			qtree.Insert(start_point, true);
			qtree.Insert(end_point, true);

			// 시작점과 끝 점을 실제로 만들어진 쿼드트리 노드의 중심으로 업데이트
			start_point = qtree.FindLeaf(start_point)->Center();
			end_point = qtree.FindLeaf(end_point)->Center();

			start_prev = start_point;
			end_prev = end_point;

			// 지도를 읽어들여서 쿼드 트리 분할
			// 검은색 픽셀은 갈 수 없는 곳, 흰색 픽셀은 갈 수 있는 곳을 의미
			for (int r = 1; r < map.rows - 1; r += 1)
				for (int c = 1; c < map.cols - 1; c += 1) // 구현 편의상 가장자리 픽셀들은 무시
				{
					// 주변에 검은색 픽셀과 맞닿아 있는 흰색 픽셀 위치에 점 추가
					if (map.at<Vec3b>(r, c)[0] > 0)
					{
						if (map.at<Vec3b>(r + 1, c)[0] == 0 || map.at<Vec3b>(r - 1, c)[0] == 0 ||
							map.at<Vec3b>(r, c + 1)[0] == 0 || map.at<Vec3b>(r, c - 1)[0] == 0 ||
							map.at<Vec3b>(r + 1, c + 1)[0] == 0 || map.at<Vec3b>(r + 1, c - 1)[0] == 0 ||
							map.at<Vec3b>(r - 1, c + 1)[0] == 0 || map.at<Vec3b>(r - 1, c - 1)[0] == 0)
						{
							// TODO: 흰색과 검은색이 만나는 가장자리 입니다.
							// TODO: 흰색과 검은색이 만나는 가장자리에서는 무엇을 해야할까?
							qtree.Insert({ c,r }, true); // colum: x좌표, y좌표 (openCV 이미지 행렬 특징)
						}
					}
				}

			// qtree.SplitMax();   // 최대 해상도로 모두 분할 (테스트용)

			// TODO: g에 edge 추가
			// TOKNOW: g는 무엇인가?
			qtree.FindNeighbors();

			// 그래프에는 연결관계만 저장되고, 노드의 좌표는 쿼드트리 사용
			// 그래프의 정점 수는 쿼드트리의 리프노드의 수와 같음
			EdgeWeightedDigraph g(int(qtree.leaves.size()));

			vector<double> heur(qtree.leaves.size());
			
			int	start_index = qtree.FindLeaf(start_point)->index;
			int	end_index = qtree.FindLeaf(end_point)->index;

			for (auto* l : qtree.leaves)
			{
				auto diff = l->Center() - qtree.leaves[end_index]->Center();
				heur[l->index] = std::abs(diff.x) + std::abs(diff.y);

				if (map.at<Vec3b>(l->Center().y, l->Center().x)[0] == 0)
					continue;

				for (auto* adj : l->neighbors) // 그래프에서 정점 사이의 연결관계 만들기
				{
					if (map.at<Vec3b>(adj->Center().y, adj->Center().x)[0] == 0)
						continue;
					
					double dist = cv::norm(l->Center() - qtree.leaves[adj->index]->Center());

					g.AddEdge(hlab::DirectedEdge(l->index, adj->index, dist));
				}
			}
			// TODO: d.Initialize(g, start_index, end_index, heur);
			d.Initialize(g, start_index, end_index, heur);
		}

		if (!hlab::left_down) // 마우스로 드래그하는 동안에는 경로 업데이트 중지
			d.Update(); // 힌트

		auto path = d.GetPath(); // 힌트

		hlab::preframe();

		// 지도 이미지를 화면에 그리기
		for (int c = 0; c < image.cols; c++)
			for (int r = 0; r < image.rows; r++)
				if (map.at<Vec3b>(r, c)[0] == 0) // 흑백 BMP 이미지
					image.at<Vec3b>(r, c) = Vec3b(255, 191, 0);

		DisplayQuadtree(image, qtree.root);

		// TODO:
		//  경로를 찾는 과정에서 방문한 정점들 표시
		for (int i = 0; i < qtree.leaves.size(); i++)
		{
			Point p = qtree.leaves[i]->Center();

			if (d.visited[i])
				cv::circle(image, p, 3, kPureBlue, -1, LINE_AA);
			else
				cv::circle(image, p, 3, kBrightGray, -1, LINE_AA);
		}

		for (int i = 1; i < path.size(); i++)
		{
			Point start = qtree.leaves[path[i - 1]]->Center();
			Point end = qtree.leaves[path[i]]->Center();
			cv::line(image, start, end, kPureBlue, 1, LINE_AA);
		}

		cv::circle(image, start_point, 7, kPureRed, -1, LINE_AA);
		cv::circle(image, end_point, 7, kPureRed, -1, LINE_AA);

		if (hlab::postframe()) break;
	}

	return 0;
}