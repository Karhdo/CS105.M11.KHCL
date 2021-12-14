#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <iostream>
#include <math.h>
using namespace std;

int xc, yc, select;
double a, b;

void initGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // R=1, G=1, B=1, anpha=1 => Nền đen
    gluOrtho2D(0, 640, 0, 480); // Vị trị điểm vẽ
}

void Draw4Point(int xc, int yc, int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - x, yc + y);
    glEnd();
}

void EllipseMidPoint(int xc, int yc, double a, double b)
{
    int x = 0, y = b;
    float x0 = a * a / sqrt(a * a + b * b), P = b * b - a * a * b + a * a / 4;
    Draw4Point(xc, yc, x, y);
    while (x <= x0)
    {
        if (P < 0)
            P += (b * b) * (2 * x + 3);
        else
        {
            P += (b * b) * (2 * x + 3) - 2 * a * a * (y - 1);
            y--;
        }
        x++;
        Draw4Point(xc, yc, x, y);
    }

    x = a; y = 0;
    P = a * a - b * b * a + b * b / 4;
    Draw4Point(xc, yc, x, y);
    while (x > x0)
    {
        if (P < 0)
            P += (a * a) * (2 * y + 3);
        else
        {
            P += (a * a) * (2 * y + 3) - 2 * b * b * (x - 1);
            x--;

        }
        y++;
        Draw4Point(xc, yc, x, y);
    }
}

struct Color
{
    float r, g, b;
};

Color getPixelColor(int x, int y)
{
    Color color;
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, &color);
    return color;
}

void setPixelColor(int x, int y, Color color)
{
    glBegin(GL_POINTS);
    glColor3f(color.r, color.g, color.b);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

//Boundary fill
void BoundaryFill(int x, int y, Color colorDraw, Color colorBorder)
{
    Color color;
    color = getPixelColor(x, y);
    cout << color.r << "," << color.g << "," << color.b << "\n";
    if (color.r == colorBorder.r && color.g == colorBorder.g && color.b == colorBorder.b)
    {
        setPixelColor(x, y, colorDraw);
        BoundaryFill(x + 1, y, colorDraw, colorBorder);
        BoundaryFill(x, y + 1, colorDraw, colorBorder);
        BoundaryFill(x - 1, y, colorDraw, colorBorder);
        BoundaryFill(x, y - 1, colorDraw, colorBorder);
    }
}

//Scanline fill
void ScanLineFill(int a, int b, Color colorDraw, Color colorBorder)
{
    int y_max = b;
    int y_min = -b + 1;
    int x, x1, x2;
    Color color_tam;
    while (y_min < y_max)
    {
        x = a * sqrt(1 - ((float)((y_min)*y_min) / (b * b))); // Tìm giao điểm giữa đường thẳng y_min và elip
        x += 320;
        do
        {
            color_tam = getPixelColor(x, y_min + 240);
            cout << color_tam.r << "," << color_tam.g << "," << color_tam.b << "\n";
            if (color_tam.r == colorBorder.r && color_tam.g == colorBorder.g && color_tam.b == colorBorder.b)
            {
                x--;
            }
        } while (color_tam.r == colorBorder.r && color_tam.g == colorBorder.g && color_tam.b == colorBorder.b);

        x1 = 320 - ((int)x - 320);
        x2 = (int)x;
        int y_min_tam = 240 + y_min;
        for (int i = x1; i <= x2;i++)
        {
            setPixelColor(i, y_min_tam, colorDraw);
        }
        y_min++;
    }
}

void onMouseClick(int button, int state, int x, int y)
{
    Color colorDraw = { 0.0f, 1.0f, 0.0f };
    Color colorOld = { 1.0f, 1.0f, 1.0f };
    Color colorBorder = { 1.0f, 0.0f, 0.0f };
    switch (select)
    {
    case 1:
        BoundaryFill(320, 240, colorDraw, colorOld);
        break;
    case 2:
        ScanLineFill(a, b, colorDraw, colorBorder); // Thực hiện tô màu theo dòng quét
        break;
    }
}

void drawText(int xPos, int yPos, char str[]) // Hàm in chuỗi ra màn hình
{
    glRasterPos2i(xPos, yPos);
    void* font = GLUT_BITMAP_9_BY_15; // font chữ
    for (int i = 0;i < strlen(str);i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}



void MyDisplay()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Thiết lập màu cho khung: màu trắng
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    EllipseMidPoint(320, 240, a, b); // Thực hiện vẽ elip bằng thuật toán Midpoint
    char str[100] = "Click chuot de to mau Ellipse";
    drawText(0 - 125 + 320, b + 50 + 240, str); // In chuỗi ra màn hình
    glFlush();
}

int main(int argc, char** argv)
{
    cout << "Ellipse co phuong trinh x^2/a^2 + y^2/b^2 = 1\n";
    cout << "Nhap ban kinh cua duong ellipse: ";
    cin >> a >> b;
    cout << "1. To mau bang thuat toan de quy (Boundary Fill)\n";
    cout << "2. To mau theo dong quet (Scanline Fill)\n";
    cout << "Nhap vao lua chon cua ban: ";
    cin >> select;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //Thiết lập chế độ hiển thị của cửa sổ
    glutInitWindowSize(640, 480); // Khởi tạo kích thước của cửa số ứng dụng (640, 480)
    glutInitWindowPosition(0, 0); // Khỏi tạo vị trí ban đầu của của sổ
    glutCreateWindow("Ellipse MidPoint algorithm"); // Đặt tên cho cửa sổ ứng dụng

    glutDisplayFunc(MyDisplay);
    initGL();
    glutMouseFunc(onMouseClick);
    glutMainLoop(); //Vòng lặp chờ xử lý sự kiện
    return 0;
}
