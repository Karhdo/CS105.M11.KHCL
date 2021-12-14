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

void LineBresenham_1(int x1, int y1, int x2, int y2) //Bresenham với đường thẳng tăng chậm và giảm chậm
{
    int Dx = x2 - x1;
    int Dy = y2 - y1;
    int y_step = (Dy >= 0) ? 1 : -1;
    
    Dx = abs(Dx);
    Dy = abs(Dy);
    
    int P = 2*Dy - Dx;
    int x = x1;
    int y = y1;
    
    glBegin(GL_POINTS);
    glVertex2i(x, y); // Vẽ point tại vị trí (x, y)
    
    while (x < x2)
    {
        if (P < 0)
            P += 2 * Dy;
        else
        {
            P += 2 * (Dy - Dx);
            y += y_step;
        }
        x++;
        glVertex2i(x, y);
    }
    glEnd();
}

void LineBresenham_2(int x1, int y1, int x2, int y2) //Bresenham với đường thẳng tăng nhanh và giảm nhanh
{
    int Dx = x2 - x1;
    int Dy = y2 - y1;
    int x_step = (Dx >= 0) ? 1 : -1;
    
    Dx = abs(Dx);
    Dy = abs(Dy);
    
    int P = 2*Dx - Dy;
    int x = x1;
    int y = y1;
    
    glBegin(GL_POINTS);
    glVertex2i(x, y); // Vẽ point tại vị trí (x, y)
    
    while (y < y2)
    {
        if (P < 0)
            P += 2 * Dx;
        else
        {
            P += 2 * (Dx - Dy);
            x += x_step;
        }
        y++;
        glVertex2i(x, y);
    }
    glEnd();
}

void MyDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // Xoá màu trong vùng đệm khung
    glPointSize(3); // Kích thước của point
    glColor3f(1.0f, 0.0f, 0.0f); // Màu của point: Red
    
    if ((x_end == x_start) && (y_end == y_start)) //TH 2 điểm trùng nhau
    {
        glBegin(GL_POINTS);
        glVertex2i(x_start, y_start);
        glEnd();
    }
    else // TH 2 điểm không trùng nhau
    {
        if (abs(x_end - x_start) >= abs(y_end - y_start)) // Tăng chậm giảm chậm
        {
            if (x_start <= x_end)
                LineBresenham_1(x_start, y_start, x_end, y_end);
            else
                LineBresenham_1(x_end, y_end, x_start, y_start);
        }
        else // Tăng nhanh giảm nhanh
        {
            if (y_start <= y_end)
                LineBresenham_2(x_start, y_start, x_end, y_end);
            else
                LineBresenham_2(x_end, y_end, x_start, y_start);
        }
        glViewport(0, 0, 640, 480);
        glFlush(); // Đẩy hình ảnh ra vùng đệm khung
    }
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
