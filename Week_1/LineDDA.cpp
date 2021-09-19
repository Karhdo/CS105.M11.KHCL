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

void LineDDA_1(int x1, int y1, int x2, int y2) // Trường hợp tăng chậm giảm chậm
{
    int inc_x = 1, Dx = x2 - x1, Dy = y2 - y1;
    int x = x1;
    float y = y1;
    float m = (float)Dy / Dx;
    
    glBegin(GL_POINTS);
    glVertex2d(x, round(y));
       
    while(x < x2){
        x += inc_x;
        y += m;
        glVertex2d(x,round(y));
    }
    glEnd();
}

void LineDDA_2(int x1, int y1, int x2, int y2) // Trường hợp tăng nhanh giảm nhanh
{
    int inc_y = 1, Dx = x2 - x1, Dy = y2 - y1;
    float x = x1;
    int y = y1;
    float m = (float)Dx / Dy;
    
    glBegin(GL_POINTS);
    glVertex2d(round(x), y);
       
    while(y < y2){
        x += m;
        y += inc_y;
        glVertex2d(round(x), y);
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
                LineDDA_1(x_start, y_start, x_end, y_end);
            else
                LineDDA_1(x_end, y_end, x_start, y_start);
        }
        else // Tăng nhanh giảm nhanh
        {
            if (y_start <= y_end)
                LineDDA_2(x_start, y_start, x_end, y_end);
            else
                LineDDA_2(x_end, y_end, x_start, y_start);
        }
    }
    glViewport(0, 0, 640, 480); // Vị trí và kích thước cửa số khung hình
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
