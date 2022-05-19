# Dự án game môn Lập trình nâng cao INT2215 1
- Tên sinh viên: Trần Viết Dũng
- MSV: 21020009
- Lớp: K66CC
# Cài đặt và chạy chương trình:
- Điều kiện: Có C++ compiler và đã tải các thư viện SDL2, SDL2_image, SDL2_ttf, SDL2_mixer
- Tải source code về máy: git clone https://github.com/Samoyed23/Conway-game.git 
- Sử dụng Makefile để biên dịch chương trình
- Bắt đầu chạy game bằng cách gõ ./main  
# Mô tả chung về trò chơi:
- Mô phỏng Game of life, môt bài toán nổi tiếng thuộc lĩnh vực cellcular automation của nhà toán học Horton Conway. Cuối năm 1940, John von Neumann định nghĩa Life như một tạo phẩm có thể tự tái sản xuất và tương tự với một máy Turing. Đây là một trò chơi mà không có người chơi, sự tiến hóa được xác định bằng trạng thái ban đầu, có ý nghĩa khoa học phức tạp mặc dù luật chơi khá đơn giản như sau:
- Ban đầu là mạng lưới các ô (tế bào) tạo nên một không gian hai chiều không giới hạn. Trạng thái của mỗi ô (tế bào): sống hoặc chết, quyết định bởi sự tương tác với 8 ô hàng xóm mà Conway gọi là các tế bào liền kề.
1. Ô đang sống mà có ít hơn hai hàng xóm đang sống thì sẽ chết (quá ít dân)
2. Ô đang sống mà có nhiều hơn 3 hàng xóm đang sống sẽ chết (quá đông dân)
3. Ô đang sống mà có 2 hoặc 3 hàng xóm đang sống sẽ tiếp tục sống (tồn tại cân bằng)
4. Ô chết mà có đúng 3 hàng xóm đang sống sẽ chuyển thành ô sống (sự sinh sản)
- Mẫu ban đầu là mầm của hệ thống. Thế hệ đầu tiên được tạo ra bằng cách áp dụng luật trên cho tất cả mọi tế bào trong hạt giống và mỗi một thế hệ mới được tạo ra là một hàm thuần túy của thế hệ trước đó.
- Chi tiết: https://conwaylife.com/forums/  http://dotat.at/prog/life/life.html
# Mô tả dự án:
- Có giao diện đơn giản và âm thanh dễ chịu
- Các chức năng cơ bản, nhận sự kiện bàn phím như begin (SPACE), stimulate (S), restart (R), pause (P), điều chỉnh tốc độ up/down, exit (ESC)
- Chuột trái/phải để tạo/xóa mầm ban đầu của hệ thống
- Hiển thị số tế bào hiện tại (population), trạng thái đông đúc nhất (crowdest) và trạng thái ít nhất (lowest) 
- Video demo: 
# Các kỹ năng, ý tưởng rút ra từ dự án
- Cách set up môi trường, tích hợp thư viện
- Refactor, phân chia file và làm việc với git, github
- Cải thiện kiến thức C++
- Cải thiện kiến thức khoa học liên quan đến Conway's game
# Tham khảo và hướng phát triển:
- Tự code, tự tìm hiểu logic Conway's game trên internet
- Học SDL2 trên https://lazyfoo.net/tutorials/SDL/ 
- Tạo hình ảnh miễn phí từ http://pixelartmaker.com/, https://www.hexcolortool.com/
- Lấy âm thanh miễn phí trên https://www.chosic.com/free-music/games/
- Hướng phát triển: Cải thiện giao diện hình ảnh đẹp hơn, thêm các mẫu mầm có hiệu ứng sinh độc đáo được phát hiện bởi cộng đồng mạng, các mẫu mầm có thể mô phỏng ý nghĩa khoa học của trò chơi.
- Tối ưu game: Endgame khi các tế bào đạt trở nên stable, tức là sự sống chết của các tế bào không thay đổi nữa, khi đó population cố định. Tuy nhiên có 1 trường hợp đặc biệt không phải stable pattern nhưng population vẫn đạt được trạng thái cố định, theo nghĩa nào đó thì đây vẫn được coi là endgame. Hiện tại em chưa và vẫn đang cố gắng detect trạng thái này, hy vọng thầy cô và các bạn có thể đóng góp vào source code giúp em hoàn thiện trò chơi.
