#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

int x_start, y_start, x_end, y_end;

void initGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // R=1, G=1, B=1, anpha=1 => Nền đen
    gluOrtho2D(0, 640, 0, 480); // Vị trị điểm vẽ
}

void LineBresenham(int x_start, int y_start, int x_end ,int y_end)
{
    int x = x_start;
    int y = y_start;
    int dx = x_end - x_start;
    int dy = y_end - y_start;
    int P = 2*dx - dy;
    
    glBegin(GL_POINTS);
    glVertex2d(x, y); // Vẽ point tại vị trí (x, y)
    
    while (x < x_end)
    {
        if (P < 0)
            P += 2 * dy;
        else
        {
            P += 2 * (dy - dx);
            y++;
        }
        x++;
        glVertex2d(x, y);
    }
    glEnd();
}

void MyDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // Xoá màu trong vùng đệm khung
    glPointSize(3); // Kích thước của point
    glColor3f(1.0f, 0.0f, 0.0f); // Màu của point: Red
    LineBresenham(x_start, y_start, x_end, y_end); // Kích thước khung nhìn
    glViewport(0, 0, 640, 480);
    glFlush(); // Đẩy hình ảnh ra vùng đệm khung
    
}

int main(int argc, char** argv)
{
    cout<<"Enter Frist Point: ";
    cin>>x_start>>y_start;
    cout<<"Enter Second Point: ";
    cin>>x_end>>y_end;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); //Thiết lập chế độ hiển thị của cửa sổ
    glutInitWindowSize(640, 480); // Khởi tạo kích thước của cửa số ứng dụng (640, 480)
    glutInitWindowPosition(0, 0); // Khỏi tạo vị trí ban đầu của của sổ
    glutCreateWindow("Bresenham line algorithm"); // Đặt tên cho cửa sổ ứng dụng
    
    initGL();
    glutDisplayFunc(MyDisplay);
    glutMainLoop(); //Vòng lặp chờ xử lý sự kiện
}
