<!-- Banner -->
<p align="center">
  <a href="https://www.uit.edu.vn/" title="Trường Đại học Công nghệ Thông tin" style="border: none;">
    <img src="https://i.imgur.com/WmMnSRt.png" alt="Trường Đại học Công nghệ Thông tin | University of Information Technology">
  </a>
</p>

<h1 align="center"><b>ĐỒ HOẠ MÁY TÍNH</b></h>

## THÀNH VIÊN NHÓM
| STT    | MSSV          | Họ và Tên              |Chức Vụ    | Github                                                  | Email                   |
| ------ |:-------------:| ----------------------:|----------:|--------------------------------------------------------:|-------------------------:
| 1      | 19521676      | Đỗ Trọng Khánh         |Nhóm trưởng|[trong-khanh-1109](https://github.com/trong-khanh-1109)  |19521676@gm.uit.edu.vn   |
| 2      | 19521383      | Võ Phạm Duy Đức        |Thành viên |[ducducqn123](https://github.com/ducducqn123)            |19521383@gm.uit.edu.vn   |

## GIỚI THIỆU MÔN HỌC
* **Tên môn học:** Đồ hoạ máy tính
* **Mã môn học:** CS105
* **Mã lớp:** CS105.M11.KHCL
* **Năm học:** HK1 (2021 - 2022)
* **Giảng viên**: ThS.Cáp Phạm Đình Thăng

## QUÁ TRÌNH
### Week 1: CÁC THUẬT TOÁN VẼ ĐƯỜNG THẲNG
#### 1. Thuật toán Digital differential analyzer (DDA)
  - Phương trình đường thẳng: `y = m.x + b`.</br>
  </br>![Phương trình đường thẳng](Image/ptdt.png)
  - Để đơn giản hóa giải thuật ta xét đường thẳng với `min [0,1] , Dx > 0`
  - Tại mỗi bước ta cho `X` tăng lên 1 đơn vị tức là `Xi+1 = Xi + 1 => Yi+1 = Yi + m`
  - Do `m` là số thực nên muốn `Yi+1` là số nguyên ta phải làm tròn trước khi truy xuất tọa độ để đưa ra màn hình.
  - Với đường thẳng có `m > 1` ta sẽ làm ngược lại cho `Y` biến thiên và tính `X` theo `Y` nghĩa là tại mỗi bước ta có Yi+1 = Yi + 1 => Xi+1 = Xi + m
  - Với các đoạn thẳng có `Dx <0` ta sẽ cho `X` giảm xuống chứ không tăng.</br>

<table>
<tr>
  <td>
    <img src="https://github.com/trong-khanh-1109/CS105.M11.KHCL/blob/d745acb3dbbf247cb71d60679b1c07f4fd4313f7/Image/DDA.png" />
  </td>
  <td>
    <img src="https://github.com/trong-khanh-1109/CS105.M11.KHCL/blob/d745acb3dbbf247cb71d60679b1c07f4fd4313f7/Image/Lu%CC%9Bu%20%C4%91o%CC%82%CC%80%20DDA.png" />
  </td>
</tr>
<table>
  
  - Code: [DDA Algorithm](Week_1/DDA.cpp)
 
#### 2. Thuật toán Bresenham
<table>
<tr>
  <td width>
    <img src="https://github.com/trong-khanh-1109/CS105.M11.KHCL/blob/97306c26556cc8f728ac43947e344b378dffbae1/Image/Bresenham.png" />
  </td>
  <td>
    <img src="https://github.com/trong-khanh-1109/CS105.M11.KHCL/blob/97306c26556cc8f728ac43947e344b378dffbae1/Image/Lu%CC%9Bu%20%C4%91o%CC%82%CC%80%20Bresenham.png" />
  </td>
</tr>
<table>
  
  - Code: [DDA Algorithm](Week_1/Bresenham.cpp)

<!-- Footer -->
<p align="center">© Copyright by Đỗ Trọng Khánh</p>
