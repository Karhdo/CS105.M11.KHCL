#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

int x_start, y_start, x_end, y_end;

void initGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //R=1, G=1, B=1, anpha=1 => Nền đen
    gluOrtho2D(0, 640, 0, 480); //Vị trị điểm vẽ
}

void DDA_algorithm(int x_start, int y_start, int x_end, int y_end)
{
    int dx = x_end - x_start;
    int dy = y_end - y_start;
    int steps;
    
    if (abs(dy) > abs(dx))
        steps = dy;
    else
        steps = dx;
    
    double x = x_start * 1.0;
    double y = y_start * 1.0;
    
    double inc_x = 1.0 * dx/steps;
    double inc_y = 1.0 * dy/steps;
    
    glBegin(GL_POINTS);
    glVertex2d(x, y); // Vẽ point tại vị trí (x, y)
    for (int i = 0; i <= steps; i++)
    {
        x += inc_x;
        y += inc_y;
        glVertex2d(round(x), round(y));
    }
    glEnd();
}

void MyDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // Xoá màu trong vùng đệm khung
    glPointSize(3); // Kích thước của point
    glColor3f(1.0f, 0.0f, 0.0f); // Màu của point: Red
    DDA_algorithm(x_start, y_start, x_end, y_end);
    glViewport(0, 0, 640, 480); // Kích thước khung nhìn
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
    glutCreateWindow("DDA Line algorithm"); // Đặt tên cho cửa sổ ứng dụng
    
    initGL();
    glutDisplayFunc(MyDisplay);
    glutMainLoop(); //Vòng lặp chờ xử lý sự kiện
}
