# Dự án game môn Lập trình nâng cao INT2215 1
- Tên sinh viên: Trần Viết Dũng
- MSV: 21020009
- Lớp: K66CC
# Cài đặt và chạy chương trình:
- Điều kiện: Có compiler C++ và đã tải các thư viện SDL2, SDL2_image, SDL2_ttf, SDL2_mixer. 
- Tải source code về máy: git clone https://github.com/Samoyed23/Conway-game.git 
- Sử dụng Makefile để biên dịch chương trình
- Bắt đầu chạy game bằng cách gõ ./main  
# Mô tả chung về trò chơi:
- Mô phỏng Game of life, môt bài toán nổi tiếng thuộc lĩnh vực cellcular automation của nhà toán học Horton Conway. Đây là một trò chơi mà không có người chơi, sự tiến hóa được xác định bằng trạng thái ban đầu, có ý nghĩa khoa học phức tạp mặc dù luật chơi khá đơn giản như sau:
- Ban đầu là mạng lưới các ô (tế bào) tạo nên một không gian hai chiều không giới hạn. Trạng thái của mỗi ô (tế bào): sống hoặc chết, quyết định bởi sự tương tác với 8 ô hàng xóm mà Conway gọi là các tế bào liền kề.
1. Ô đang sống mà có ít hơn hai hàng xóm đang sống thì sẽ chết (quá ít dân)
2. Ô đang sống mà có nhiều hơn 3 hàng xóm đang sống sẽ chết (quá đông dân)
3. Ô đang sống mà có 2 hoặc 3 hàng xóm đang sống sẽ tiếp tục sống (tồn tại cân bằng)
4. Ô chết mà có đúng 3 hàng xóm đang sống sẽ chuyển thành ô sống (sự sinh sản)
- Mẫu ban đầu là mầm của hệ thống. Thế hệ đầu tiên được tạo ra bằng cách áo dụng luật trên cho tất cả mọi tế bào trong hạt giống và mỗi một thế hệ mới được tạo ra là một hàm thuần túy của thế hệ trước đó.
- Chi tiết: https://conwaylife.com/forums/
# Mô tả dự án:
- Có giao diện đơn giản và âm thanh dễ chịu
- Các chức năng cơ bản, nhận sự kiện bàn phím như begin(SPACE), stimulate(S), restart(R), pause(P), điều chỉnh tốc độ, exit(ESC)
- Click chuột để tạo mầm của hệ thống
- Hiển thị số tế bào hiện tại (population), trạng thái đông đúc nhất (crowdest) và trạng thái ít nhất (lowest) 
- Video demo: 
# Các kỹ năng, ý tưởng rút ra từ dự án
- Cách set up môi trường, tích hợp thư viện
- Refactor, phân chia file và sử dụng github
- Cải thiện kiến thức C++
# Kết luận, hướng phát triển:
- Tham khảo cách sử dụng SDL2 trên https://lazyfoo.net/tutorials/SDL/
- Tạo và sử dụng hình ảnh từ http://pixelartmaker.com/
- Âm thanh miễn phí trên https://www.chosic.com/free-music/games/
- Hướng phát triển của game: Cải thiện hình ảnh, tương tác các tế bào trong trạng thái sống chết, thêm các mẫu mầm có hiệu ứng thú vị của cộng đồng mạng vào trò chơi.
