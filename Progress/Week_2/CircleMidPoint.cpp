#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

int xc, yc, R;

void initGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // R=1, G=1, B=1, anpha=1 => Nền đen
    gluOrtho2D(-320, 320, -240, 240); // Vị trị điểm vẽ
}

void Draw8point (int xc, int yc, int x, int y)
{
    glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc - y, yc - x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc - x, yc + y);
    glEnd();
}

void CircleMidPoint(int xc, int yc, int R)
{
    int y = R, x = 0;
    float P = 5/4 - R;
    Draw8point(xc, yc, x, y); // Vẽ 8 điểm đối xứng qua trục Ox và Oy.
    while (x < y)
    {
        if (P < 0) // Điểm M nằm ngoài đường tròn => chọn điểm P(xi + 1, yi)
            P += 2*x + 3;
        else // Điểm M nằm trên hoặc trong đường tròn => chọn điểm S(xi + 1, yi -1)
        {
            P += 2*(x - y) + 5;
            y--;
        }
        x++;
        Draw8point(xc, yc, x, y); // Vẽ 8 điểm tiếp theo
    }
}


void MyDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // Xoá màu trong vùng đệm khung
    glPointSize(3); // Kích thước của point
    glColor3f(1.0f, 0.0f, 0.0f); // Màu của point: Red
    CircleMidPoint(xc, yc, R);
    glViewport(0, 0, 640, 480);
    glFlush();
}

int main(int argc, char** argv)
{
    cout<<"Nhap toa do tam cua duong tron: ";
    cin>>xc>>yc;
    cout<<"Nhap ban kinh cua duong tron: ";
    cin>>R;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); //Thiết lập chế độ hiển thị của cửa sổ
    glutInitWindowSize(640, 480); // Khởi tạo kích thước của cửa số ứng dụng (640, 480)
    glutInitWindowPosition(0, 0); // Khỏi tạo vị trí ban đầu của của sổ
    glutCreateWindow("Circle MidPoint algorithm"); // Đặt tên cho cửa sổ ứng dụng
    
    initGL();
    glutDisplayFunc(MyDisplay);
    glutMainLoop(); //Vòng lặp chờ xử lý sự kiện
}
