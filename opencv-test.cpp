#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>
using namespace cv;
using namespace std;
Vec4i p;
void grises(Mat org, Mat sal);
void des_grs(Mat grs, Mat img_out);
void umbral(Mat img_gris, Mat sal, float n);
void operaciones_img(Mat in1, Mat in2, Mat out);
void aritmeticas(Mat in, Mat out, int s, float fact); //	1 = +, 2 = -, 3 = *, 4 = /
void negativo(Mat in, Mat out);
void invertir_v(Mat in, Mat out);
void f_promedio(Mat in, Mat out);
void conteo(Mat in);
void dilatacion(Mat in, Mat aux, int n);
void erosion(Mat in, Mat out, int n);
void apertura(Mat in, Mat out, int n);
void cierre(Mat in, Mat out, int n);
void histograma(Mat in, Mat out);
int video(void);
void sobel(Mat in, Mat out);
void prewitt(Mat in, Mat out);
void roberts(Mat in, Mat out);
void kirsch(Mat in, Mat out);
void robinson(Mat in, Mat out);
void mouse_coor(int event, int x, int y, int flags, void* pt);
void im_ROI(Mat in, Mat out);
void desplegar_color(Mat in, Mat out);
//void imprimir_txt(Mat image);

int main() {
	video();
	//Mat image = imread("C:/Users/emi_s/Pictures/SVC/aleman.jpg");
	//////Mat image1 = imread("C:/Users/emi_s/Pictures/ejemplo1b.jpg");
	//cout << "canales:" << image.channels() << " filas: " << image.rows << " columnas: " << image.cols << endl;
	//im_ROI(image);
	//imshow("Original", image);
	//setMouseCallback("Original", mouse_coor, &p);
	//for (int i = 0; i < 1; i++)
	//{
	//	waitKey(0);
	//	setMouseCallback("Original", mouse_coor, &p);
	//	cout << "x1: " << p.val[0] << "y1: " << p.val[1] << "x2: " << p.val[2] << "y2 : " << p.val[3] << endl;
	//}
	//Rect rect(p.val[0], p.val[1], (p.val[2] - p.val[0]), (p.val[3] - p.val[1]));
	//rectangle(image, rect, Scalar(255, 0, 0), 2);
	//imshow("Original", image);
	//Mat griss(image.rows, image.cols, CV_32FC1);
	////Mat griss1(image.rows, image.cols, CV_32FC1);
	//Mat aux(image.rows, image.cols, CV_32FC1);
	//Mat aux1(image.rows, image.cols, CV_32FC1);
	//Mat aux2(image.rows, image.cols, CV_32FC1);
	//Mat aux3(image.rows, image.cols, CV_32FC1);
	//Mat aux4(image.rows, image.cols, CV_32FC1);
	//Mat umb(image.rows, image.cols, CV_32FC1);
	//Mat img_salida(image.rows, image.cols, CV_8UC1);
	//grises(image, griss);
	//des_grs(griss, img_salida);
	//imshow("gris", img_salida);
	//histograma(griss, aux);
	//des_grs(aux, img_salida);
	//imshow("Ecualizacion", img_salida);
	//grises(image1, griss1);
	//des_grs(griss1, img_salida);
	//umbral(griss, umb, 200.0);
	//des_grs(umb, img_salida);
	//imshow("Umbral", img_salida);
	//conteo(umb);
	//operaciones_img(griss, griss1, aux);
	//negativo(umb, aux);
	//dilatacion(umb, aux1);
	//cierre(umb, aux1);
	//aritmeticas(griss, aux, 4, 10);
	//invertir_v(griss, aux);
	//f_promedio(griss, aux);
	//sobel(griss, aux);
	//prewitt(griss, aux1);
	//roberts(griss, aux2);
	//kirsch(griss, aux3);
	//robinson(griss, aux4);
	//des_grs(aux, img_salida);
	//imshow("Sobel", img_salida);
	//des_grs(aux1, img_salida);
	//imshow("Prewitt", img_salida);
	//des_grs(aux2, img_salida);
	//imshow("Roberts", img_salida);
	//des_grs(aux3, img_salida);
	//imshow("Kirsch", img_salida);
	//des_grs(aux4, img_salida);
	//imshow("Robinson", img_salida);
	//imwrite("C:/Users/emi_s/Pictures/Salida1.jpg", img_salida);
	//Mat image = imread("C:/Users/emi_s/Pictures/SVC/wolverine.jpg");
	//cout << "canales:" << image.channels() << " filas: " << image.rows << " columnas: " << image.cols << endl;
	//Mat aux(image.rows, image.cols, CV_32FC3);
	//Mat aux1(image.rows, image.cols, CV_8UC3);
	//im_ROI(image, aux);
	//desplegar_color(aux, aux1);
	//imshow("Salida", aux1);
	//waitKey(0);
}

void grises(Mat org, Mat sal) {
	Mat aux(org.rows, org.cols, CV_32FC3);
	org.convertTo(aux, CV_32FC3);
	for (int i = 0; i < org.rows; i++)
		for (int j = 0; j < org.cols; j++)
		{
			Vec3f pixel = aux.at<Vec3f>(i, j);
			sal.at<float>(i, j) = 0.114*pixel[0] + 0.587*pixel[1] + 0.299*pixel[2];
//			sal.at<float>(i, j) = (pixel[0] + pixel[1] + pixel[2]) / 3.0;
		}
}
void umbral(Mat img_gris, Mat sal, float n) {
	for (int i = 0; i < img_gris.rows; i++)
		for (int j = 0; j < img_gris.cols; j++)
		{
			if (img_gris.at<float>(i, j) <= n)
				sal.at<float>(i, j) = 0.0;
			else
				sal.at<float>(i, j) = 255.0;
		}
}
void des_grs(Mat gris, Mat img_out) {
	gris.convertTo(img_out, CV_8UC1);
}
void aritmeticas(Mat in, Mat out, int s, float fact) {
	switch (s)
	{
	case 1:
		for (int i = 0; i < in.rows; i++)
			for (int j = 0; j < in.cols; j++)
			{
				out.at<float>(i, j) = in.at<float>(i, j) + fact;
				if (out.at<float>(i, j) > 255.0)
					out.at<float>(i, j) = 255.0;
				if (out.at<float>(i, j) < 0.0)
					out.at<float>(i, j) = 0.0;
			}
		break;
	case 2:
		for (int i = 0; i < in.rows; i++)
			for (int j = 0; j < in.cols; j++)
			{
				out.at<float>(i, j) = in.at<float>(i, j) - fact;
				if (out.at<float>(i, j) > 255.0)
					out.at<float>(i, j) = 255.0;
				if (out.at<float>(i, j) < 0.0)
					out.at<float>(i, j) = 0.0;
			}
		break;
	case 3:
		for (int i = 0; i < in.rows; i++)
			for (int j = 0; j < in.cols; j++)
			{
				out.at<float>(i, j) = in.at<float>(i, j) * fact;
				if (out.at<float>(i, j) > 255.0)
					out.at<float>(i, j) = 255.0;
				if (out.at<float>(i, j) < 0.0)
					out.at<float>(i, j) = 0.0;
			}
		break;
	case 4:
		for (int i = 0; i < in.rows; i++)
			for (int j = 0; j < in.cols; j++)
			{
				out.at<float>(i, j) = in.at<float>(i, j) / fact;
				if (out.at<float>(i, j) > 255.0)
					out.at<float>(i, j) = 255.0;
				if (out.at<float>(i, j) < 0.0)
					out.at<float>(i, j) = 0.0;
			}
		break;
	default:
		break;
	}
}
void operaciones_img(Mat in1, Mat in2, Mat out) {
	for (int i = 0; i < in1.rows; i++)
		for (int j = 0; j < in1.cols; j++)
		{
			out.at<float>(i, j) = in1.at<float>(i, j) + in2.at<float>(i, j);
			if (out.at<float>(i, j) > 255.0)
				out.at<float>(i, j) = 255.0;
			if (out.at<float>(i, j) < 0.0)
				out.at<float>(i, j) = 0.0;
		}
}
void negativo(Mat in, Mat out) {
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			out.at<float>(i, j) = 255.0 - in.at<float>(i, j);
		}
}
void invertir_v(Mat in, Mat out) {
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			out.at<float>(i, j) = in.at<float>((in.rows-i-1), (in.cols-j-1));
		}
}
void invertir_h(Mat in, Mat out) {
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			out.at<float>(i, j) = in.at<float>(i, (in.cols - 1)- j);
		}
}
void f_promedio(Mat in, Mat out) {
	float acu = 0.0;
	for (int i = 1; i < in.rows - 1; i++)
		for (int j = 1; j < in.cols - 1; j++)
		{
			for (int ii = i-1; ii < i + 2; ii++)
				for (int jj = j-1; jj < j + 2; jj++)
				{
					acu = in.at<float>(ii, jj) + acu;
				}
			out.at<float>(i, j) = acu / 9.0;
			acu = 0.0;
		}
}
void conteo(Mat in) {
	queue<Vec2i> fifo;
	int cont = 0;
	for (int i = 1; i < in.rows - 1; i++) 
		for (int j = 1; j < in.cols - 1; j++)
		{
			if (in.at<float>(i, j) == 255.0) {
				fifo.push(Vec2i(i, j));
				cont = cont + 1;
				in.at<float>(i, j) = cont * 5.0;
				while (!fifo.empty()) {
					Vec2i u = fifo.front();
					fifo.pop();
					for (int ii = u[0] - 1; ii < u[0] + 2; ii++)
						for (int jj = u[1] - 1; jj < u[1] + 2; jj++)
						{
							if (in.at<float>(ii, jj) == 255.0) {
								fifo.push(Vec2i(ii, jj));
								in.at<float>(ii, jj) = cont * 5.0;
							}
						}
				}
			}
		}
	cout << "Numero de objetos: " << cont << endl;
}
void dilatacion(Mat in, Mat aux, int n){
	for (int a = 0; a <= n; a++){
		for (int i = 1; i < in.rows - 1; i++)
			for (int j = 1; j < in.cols - 1; j++){
				if (in.at<float>(i, j) != 0.0){
					for (int ii = i - 1; ii < i + 2; ii++)
						for (int jj = j - 1; jj < j + 2; jj++)
							aux.at<float>(ii, jj) = 255.0;
				}
			}
	}
}
void erosion(Mat in, Mat out, int n){
	for (int a = 0; a <= n; a++)
	{
		Mat aux1(in.rows, in.cols, CV_32FC1);
		Mat aux2(in.rows, in.cols, CV_32FC1);
		negativo(in, aux1);
		dilatacion(aux1, aux2, n);
		negativo(aux2, out);
	}
}
void apertura(Mat in, Mat out, int n) {
	Mat aux1(in.rows, in.cols, CV_32FC1);
	erosion(in, aux1, n);
	dilatacion(aux1, out, n);
}
void cierre(Mat in, Mat out, int n) {
	Mat aux1(in.rows, in.cols, CV_32FC1);
	dilatacion(in, aux1, n);
	erosion(aux1, out, n);
}
void histograma(Mat in, Mat out) {
	float vec[256] = { 0 };
	float sk[256] = { 0 };
	float vk[256] = { 0 };
	float vkr[256] = { 0 };
	float a = 0.0;
	float skmin, skmax;
	ofstream datos("datos_histograma.txt");
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			a = in.at<float>(i, j);
			vec[int(a)] = vec[int(a)] + 1.0;
		}
	sk[0] = vec[0];
	for (int k = 1; k < 256; k++)
	{
		sk[k] = vec[k] + sk[k - 1];
	}
	skmax = sk[255];
	int ban = 0;
	for (int k = 0; k < 256; k++)
	{
		if (ban == 0)
		{
			if (sk[k] != 0.0)
			{
				skmin = sk[k];
				ban = 1;
			}
		}
	}
	for (int k = 0; k < 256; k++)
	{
		vk[k] = (255.0 * (sk[k] - skmin)) / (skmax - skmin);
		vkr[k] = round(vk[k]);
		datos << vec[k] << "\t" << vkr[k] << endl;
	}
	a = 0.0;
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			a = in.at<float>(i, j);
			out.at<float>(i, j) = vkr[int(a)];

		}
	datos.close();
}
int video(void) {
	VideoCapture vid(1);
	if (!vid.isOpened())
		return -1;
	for (;;) {
		Mat img;
		vid >> img;
		imshow("Video_web", img);
		if (waitKey(50) > 0)
		{
			imwrite("C:/Users/emi_s/Pictures/SVC/eng.jpg", img);
			break;
		}
	}
	return 0;
}
void sobel(Mat in, Mat out) {
	float vec[9] = { 0 };
	int a =  0;
	float gx = 0.0, gy = 0.0, g = 0.0;
		for (int i = 1; i < in.rows - 1; i++)
			for (int j = 1; j < in.cols - 1; j++) {
				a = 0;
				for (int ii = i - 1; ii < i + 2; ii++)
					for (int jj = j - 1; jj < j + 2; jj++) {
						vec[a] = in.at<float>(ii, jj);
						a++;
					}
				gx = (vec[2] + 2 * vec[5] + vec[8]) - (vec[0] + 2 * vec[3] + vec[6]);
				gy = (vec[6] + 2 * vec[7] + vec[8]) - (vec[0] + 2 * vec[1] + vec[2]);
				g = abs(gx) + abs(gy);
				if (g >= 255.0)
					g = 255.0;
				if (g <= 0.0)
					g = 0.0;
				out.at<float>(i, j) = g;
			}
}
void prewitt(Mat in, Mat out) {
	float vec[9] = { 0 };
	int a = 0;
	float gx = 0.0, gy = 0.0, g = 0.0;
	for (int i = 1; i < in.rows - 1; i++)
		for (int j = 1; j < in.cols - 1; j++) {
			a = 0;
			for (int ii = i - 1; ii < i + 2; ii++)
				for (int jj = j - 1; jj < j + 2; jj++) {
					vec[a] = in.at<float>(ii, jj);
					a++;
				}
			gx = (vec[2] + vec[5] + vec[8]) - (vec[0] + vec[3] + vec[6]);
			gy = (vec[6] + vec[7] + vec[8]) - (vec[0] + vec[1] + vec[2]);
			g = abs(gx) + abs(gy);
			if (g >= 255.0)
				g = 255.0;
			if (g <= 0.0)
				g = 0.0;
			out.at<float>(i, j) = g;
		}
}
void roberts(Mat in, Mat out) {
	float vec[9] = { 0 };
	int a = 0;
	float gx = 0.0, gy = 0.0, g = 0.0;
	for (int i = 1; i < in.rows - 1; i++)
		for (int j = 1; j < in.cols - 1; j++) {
			a = 0;
			for (int ii = i - 1; ii < i + 2; ii++)
				for (int jj = j - 1; jj < j + 2; jj++) {
					vec[a] = in.at<float>(ii, jj);
					a++;
				}
			gx = vec[0] - vec[4];
			gy = vec[1] - vec[3];
			g = abs(gx) + abs(gy);
			if (g >= 255.0)
				g = 255.0;
			if (g <= 0.0)
				g = 0.0;
			out.at<float>(i, j) = g;
		}
}
void kirsch(Mat in, Mat out) {
	float vec[9] = { 0 };
	float k[8] = { 0 };
	int a = 0;
	float kx=0.0, ky=0.0, g = 0.0;
	for (int i = 1; i < in.rows - 1; i++)
		for (int j = 1; j < in.cols - 1; j++) {
			a = 0;
			for (int ii = i - 1; ii < i + 2; ii++)
				for (int jj = j - 1; jj < j + 2; jj++) {
					vec[a] = in.at<float>(ii, jj);
					a++;
				}
			k[0] = 5 * (vec[2] + vec[5] - vec[8]) - 3 * (vec[0] + vec[1] + vec[3] + vec[6] + vec[7]);
		
			k[1] = 5 * (vec[2] + vec[5] - vec[8]) - 3 * (vec[0] + vec[1] + vec[3] + vec[6] + vec[7]);
			
			k[2] = 5 * (vec[2] + vec[5] - vec[8]) - 3 * (vec[0] + vec[1] + vec[3] + vec[6] + vec[7]);
			
			k[3] = 5 * (vec[2] + vec[5] - vec[8]) - 3 * (vec[0] + vec[1] + vec[3] + vec[6] + vec[7]);
			
			k[4] = 5 * (vec[2] + vec[5] - vec[8]) - 3 * (vec[0] + vec[1] + vec[3] + vec[6] + vec[7]);
			
			k[5] = 5 * (vec[2] + vec[5] - vec[8]) - 3 * (vec[0] + vec[1] + vec[3] + vec[6] + vec[7]);
			
			k[6] = 5 * (vec[2] + vec[5] - vec[8]) - 3 * (vec[0] + vec[1] + vec[3] + vec[6] + vec[7]);
			
			k[7] = 5 * (vec[2] + vec[5] - vec[8]) - 3 * (vec[0] + vec[1] + vec[3] + vec[6] + vec[7]);

			g = k[0];
			if (g < k[1])
				g = k[1];
			else {
				g = g;
				if (g < k[2])
					g = k[2];
				else {
					g = g;
					if (g < k[3])
						g = k[3];
					else {
						g = g;
						if (g < k[4])
							g = k[4];
						else {
							g = g;
							if (g < k[5])
								g = k[5];
							else {
								g = g;
								if (g < k[6])
									g = k[6];
								else {
									g = g;
									if (g < k[7])
										g = k[7];
									else
										g = g;
								}
							}
						}
					}
				}
			}
			//for (int i = 0; i < 8; i++)
			//	if(g>0)
					//cout << "Para k" << " = " << k << " y g es: " << g << endl;
			if (g >= 255.0)
				g = 255.0;
			if (g <= 0.0)
				g = 0.0;

			out.at<float>(i, j) = g;
		}
}
void robinson(Mat in, Mat out) {
	float vec[9] = { 0 };
	float r[8] = { 0 };
	int a = 0;
	float rx = 0.0, ry = 0.0, g = 0.0;
	for (int i = 1; i < in.rows - 1; i++)
		for (int j = 1; j < in.cols - 1; j++) {
			a = 0;
			for (int ii = i - 1; ii < i + 2; ii++)
				for (int jj = j - 1; jj < j + 2; jj++) {
					vec[a] = in.at<float>(ii, jj);
					a++;
				}
			rx = (vec[2] + 2 * vec[5] + vec[8]) - (vec[0] + 2 * vec[3] + vec[6]);
			ry = (-vec[6] + vec[8]) - (vec[0] - vec[2]);
			r[0] = abs(rx) + abs(ry);

			rx = (2 * vec[2] + vec[5]) - (vec[3] + 2 * vec[6]);
			ry = (-2 * vec[6] - vec[7]) - (- vec[1] - 2 * vec[2]);
			r[1] = abs(rx) + abs(ry);

			rx = (vec[2] - vec[8]) - (-vec[0] + vec[6]);
			ry = (- vec[6] - 2 * vec[7] - vec[8]) - (- vec[0] - 2 * vec[1] - vec[2]);
			r[2] = abs(rx) + abs(ry);

			rx = (- 2 * vec[5] - 2 * vec[8]) - (-2 * vec[0] - vec[3]);
			ry = (- vec[7] - 2 * vec[8]) - (-2 * vec[0] - vec[1]);
			r[3] = abs(rx) + abs(ry);

			rx = (- vec[2] - 2 * vec[5] - vec[8]) - (- vec[0] - 2 * vec[3] - vec[6]);
			ry = (vec[6] - vec[8]) - (- vec[0] + vec[2]);
			r[4] = abs(rx) + abs(ry);

			rx = (-2 * vec[2] - vec[5]) - (- vec[3] - 2 * vec[6]);
			ry = (2 * vec[6] + vec[7]) - (vec[1] + 2 * vec[2]);
			r[5] = abs(rx) + abs(ry);

			rx = (- vec[2] + vec[8]) - (vec[0] - vec[6]);
			ry = (- vec[6] + vec[8]) - (vec[0] - vec[2]);
			r[6] = abs(rx) + abs(ry);

			rx = (vec[5] + 2 * vec[8]) - (2 * vec[0] + vec[3]);
			ry = (vec[7] + 2 * vec[8]) - (2 * vec[0] + vec[1]);
			r[7] = abs(rx) + abs(ry);
			g = r[0];
			if (g < r[1])
				g = r[1];
			else {
				g = g;
				if (g < r[2])
					g = r[2];
				else {
					g = g;
					if (g < r[3])
						g = r[3];
					else {
						g = g;
						if (g < r[4])
							g = r[4];
						else {
							g = g;
							if (g < r[5])
								g = r[5];
							else {
								g = g;
								if (g < r[6])
									g = r[6];
								else {
									g = g;
									if (g < r[7])
										g = r[7];
									else
										g = g;
								}
							}
						}
					}
				}
			}
			//for (int i = 0; i < 8; i++)
			//	if (g > 0)
			//		cout << "Para r" << i << " = " << r[i] << " y g es: " << g << endl;
			if (g >= 255.0)
				g = 255.0;
			if (g <= 0.0)
				g = 0.0;

			out.at<float>(i, j) = g;
		}
}
void ma_co(Mat in, Mat out) {
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			if (in.at<float>(i, j) == 255.0) {
				out.at<Vec3f>(i, j)[2] = 255.0;
				out.at<Vec3f>(i, j)[1] = 0.0;
				out.at<Vec3f>(i, j)[0] = 0.0;
			}
		}
}
void conv_u_float(Mat in, Mat out) {
	in.convertTo(out, CV_32FC3);
}

void desplegar_color(Mat in, Mat out) {
	in.convertTo(out, CV_8UC3);
}

void im_ROI(Mat in, Mat out) {
	Rect a;
	float r = 0.0, g = 0.0, b = 0.0, res = 0.0;
	float pi = 3.14159265359;
	float num = 0.0, den = 0.0, minn = 0.0, srgb = 0.0;
	float vec[3] = { 0.0 };
	float hmin = 360.0, hmax = 0.0;
	float val = 0.0;
	float rad = pi / 180.0;
	float hh, ss, iii;
	a = selectROI(in);
	rectangle(in, Point(a.x, a.y), Point(a.x + a.width, a.y + a.height), Scalar(255, 0, 0), 2);
	Mat aux(in.rows, in.cols, CV_32FC3);
	Mat h(in.rows, in.cols, CV_32FC1);
	Mat s(in.rows, in.cols, CV_32FC1);
	Mat ii(in.rows, in.cols, CV_32FC1);
	in.convertTo(aux, CV_32FC3);
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			Vec3f pixel = aux.at<Vec3f>(i, j);
			r = pixel[2];
			g = pixel[1];
			b = pixel[0];
			ii.at<float>(i, j) = (r + g + b) / 3.0;
			num = 0.5 * ((r - g) + (r - b));
			den = sqrt(((r - g) * (r - g)) + ((r - b) * (g - b)));
			res = acos((num / den)) * (180.0 / pi);
			if (b > g)
				h.at<float>(i, j) = 360.0 - res;
			else
				h.at<float>(i, j) = res;
			if (r == g && r == b)
				h.at<float>(i, j) = 90.0;
			vec[0] = r;
			vec[1] = g;
			vec[2] = b;
			minn = vec[0];
			for (int l = 0; l < 3; l++)
			{
				if (minn > vec[l]) {
					minn = vec[l];
				}
			}
			srgb = r + g + b;
			if (srgb == 0.0)
				srgb = 0.0001;
			s.at<float>(i, j) = 1 - ((3.0 * minn) / srgb);
			//cout << "RGB: " << r << " " << g << " " << b << endl;
			//cout << "HSI: " << h << " " << s << " " << ii << endl;
			//cout << endl;
		}
	cout << "OK" << endl;
	for (int k = a.y; k < a.y + a.height; k++)
		for (int m = a.x; m < a.x + a.width; m++) {
			if (h.at<float>(k, m) > hmax)
				hmax = h.at<float>(k, m);
			if (h.at<float>(k, m) < hmin)
				hmin = h.at<float>(k, m);
		}
	cout << "OK1" << endl;
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			if (h.at<float>(i, j) >= hmin and h.at<float>(i, j) <= hmax)
				h.at<float>(i, j) = val;
			else
				h.at<float>(i, j) = h.at<float>(i, j);
		}
	cout << "OK2" << endl;
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++) {
			iii = ii.at<float>(i, j);
			ss = s.at<float>(i, j);
			hh = h.at<float>(i, j);
			if (hh == 0.0) {
				r = iii + (2.0 * iii * ss);
				g = iii - (iii * ss);
				b = iii - (iii * ss);
			}
			else if (hh > 0 and hh < 120.0) {
				b = iii - (iii * ss);
				r = iii * (1 + ((ss * cos(hh * rad)) / (cos((60 - hh) * rad))));
				g = (3.0 * iii) - r - b;
			}
			else if (hh == 120.0) {
				r = iii - (iii * ss);
				b = iii - (iii * ss);
				g = iii + (2.0 * iii * ss);
			}
			else if (hh > 120.0 and hh < 240.0) {
				r = iii - (iii * ss);
				g = iii * (1 + ((ss * cos((hh - 120) * rad)) / (cos((180 - hh) * rad))));
				b = 3.0 * iii - r - g;
			}
			else if (hh == 240.0) {
				r = iii - (iii * ss);
				g = iii - (iii * ss);
				b = iii + (2.0 * iii * ss);
			}
			else if (hh > 240.0 and hh < 360.0) {
				g = iii - (iii * ss);
				b = iii * (1 + (ss * cos((hh - 240.0) * rad)) / (cos((300 - hh) * rad)));
				r = (3.0 * iii) - g - b;
			} 
			out.at<Vec3f>(i, j)[0] = b;
			out.at<Vec3f>(i, j)[1] = g;
			out.at<Vec3f>(i, j)[2] = r;
			hmax = 0.0;
			hmin = 360.0;
		}
	cout << "OK3" << endl;
}
void mouse_coor(int event, int x, int y, int flags, void* pt) {
	Vec4i* p = (Vec4i*)pt;

	if (event == EVENT_LBUTTONDOWN) {
		p[0][0] = x;
		p[0][1] = y;
	}
	if (event == EVENT_LBUTTONUP) {
		p[0][2] = x;
		p[0][3] = y;
	}
}
//void imprimir_txt(Mat in) {
//	ofstream aux("datos_imagen.txt");
//	for (int i = 0; i < in.rows; i++)
//		for (int j = 0; j < in.cols; j++)
//		{
//			aux << "val: " << in.at<float>(i, j) << "\n" << endl;
//		}
//}