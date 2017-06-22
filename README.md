# Hướng dẫn biên dịch Libpro

## Yêu cầu
- đã cài đặt Qt 4.8 trở lên

## Đối với Linux

1. Mở terminal lên và chuyển thư mục làm việc đến thư mục chứa mã nguồn:  cd <đường đẫn đến thư mục>
2. Sử dụng qmake của Qt để sinh makefile: qmake
3. Biên dịch mã nguồn thành chương trình: make
4. Sau khi thực hiện lệnh make ta được 1 file thực thi tên là Libpro_v2 (cùng thư mục với mã nguồn). Đây đã là file chương trình hoàn chỉnh nhưng cần đặt file này cùng thư mục với thư mục data (chứa dữ liệu của chương trình) thì mới chạy được
5. Chạy chương trình bằng lệnh: ./Libpro_v2


## Đối với Window

1. Khởi chạy chương trình command window của Qt (tên là Qt x.x for Desktop với x.x là phiên bản Qt)
2. Chuyển thư mục làm việc đến thư mục chứa mã nguồn cd <đường đẫn đến thư mục>, nếu thư mục nằm ổ đĩa khác, sử lệnh <ổ đĩa>: (vd D: sẽ đến ổ D) để di chuyển đến ổ đĩa tương ứng trước khi dùng lệnh cd.
3. Sử dụng qmake của Qt để sinh makefile: qmake
4. Biên dịch mã nguồn thành chương trình: make
5. Sau khi biên dịch sẽ sinh ra 2 thư mục là debug và release, chương trình sau khi biên dịch tên là LibPro_v2.exe nằm trong thư mục release, nhưng vẫn chưa chạy được
6. Để có thể chạy được chương trình ta cần chạy thêm lệnh: windeployqt.exe --quick .
7. Copy thư mục data vào thư mục release (thư mục chứa chương trình), đến đây chương trình có thể chạy được, chạy chương trình bằng lệnh: Libpro_v2.exe

## Chú ý
1. Tài khoản mặc định có các phiên bản trước là "root", mật khẩu "root"
2. Tài khoản mặc định cho phiên bản hiện tại là "admin", mật khẩu "123"
3. Thư mục data (chứa dữ liệu của chương trình) phải được đặt trong cùng thư mục chứ file thực thi
