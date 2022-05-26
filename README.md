# SNAKE_LeVuMinhNghia_21020366
I. Cài đặt chương trình
  1. Tải CodeBlocks
  2. Dowload code, font và ảnh tại: https://github.com/lenghia100703/SnakeCpp
  3. Cài đặt SDL2 tại https://www.libsdl.org/download-2.0.php#source, SDL_image tại https://www.libsdl.org/projects/SDL_image/,
     SDL_ttf tại https://www.libsdl.org/projects/SDL_ttf/release/. Sau khi dowload về giải nén.
  4. Sau đó vào CodeBlocks vào phần Setting -> Compiler -> Linker settings và chép dòng "-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image" vào mục
     Other linker opptions.
  5. Setting -> Compiler -> Search directories -> Compiler và sau đó dẫn đường dẫn đến \include\SDL2 của cả 3 thư mục vừa giải nén được. Tiếp đó sang 
     mục Linker ta dẫn đường dẫn đến \lib của 3 thư mục vừa giải nén được.
  6. Vào cả 3 thư mục vừa giải nén vào vào thư mục bin sao chép các file .dll vào project của bạn là có thể hoàn thành việc cài đặt.

II. Mô tả chung về trò chơi
  
  Trò chơi tên là Snake, được lấy cảm hứng từ trò chơi rắn cổ điển. Khi vào trò chơi thì ta sẽ điều khiển 1 con rắn và làm sao để ăn được thức ăn và 
  sau mỗi lần ăn sẽ dài ra.
  
III. Mô tả các chức năng đã cài đặt
  
  1. Có những tính năng như rắn cổ điển: ăn thì sẽ tăng kích thước, va vào thân rắn và tường thì rắn sẽ chết.
  2. Tính điểm: sau mỗi lần ăn được thức ăn thì ta sẽ nhận được 1 điểm.
  3. Menu bắt đầu và kết thúc: Menu bắt đầu sẽ có nút PLAY để chơi game và EXIT để thoát game, còn Menu kết thúc sẽ hiện lên số điểm mà bạn nhận được
     và nút RESTART để có thể chơi lại.
  4. Link Youtube: https://www.youtube.com/watch?v=cpY3_qeDdus&ab_channel=nghiale

IV. Các kỹ thuật được sử dụng trong lập trình

  1. Mảng
     
     Game sử dụng mảng động deque và không sử dụng mảng tĩnh array. Deque có tác dụng là liên tục update rắn và kiểm tra khi đầu rắn đâm vào thân rắn.
     Lý do sử dụng deque thay vì vector vì deque có khả năng xóa và thêm phần tử vào vị trí đầu tiên thay vì chỉ ở cuối như vector. 
  2. Con trỏ 
     
     Con trỏ được sử dụng đa phần trong hai hàm khỏi tạo cửa sổ: initSDL và quitSDL. Đa phần các hàm và phương thức trong bài sử dụng biến tham số. 
     Em lựa chọn biến tham số vì nó có thể giúp chương trình tiết kiệm bộ nhớ và dễ sử dụng hơn nhiều so với biến con trỏ.
  3. Lớp

     Lớp đóng vai trò quan trọng trong chương trình game. Em sử dụng lớp để tạo ra lớp Snake(liên quan đến con rắn) và lớp Food(thức ăn của rắn).
  4. Đồ họa

     Em sử dụng đồ họa SDL2, SDL_image, SDL_ttf để hiển thị con rắn các ảnh menu và chữ lên màn hình.
     
V. Kết luận, hướng phát triển và các điều tâm đắc rút ra được

   1. Kết luận

     Về cơ bản em đã thành công làm mô phỏng được game rắn cổ điển và có một số tính năng mới. Nhìn chung thì code có thể chưa được tối ưu nhưng các tên hàm, biến 
     đầy đủ rõ ràng. Tuy vậy em thấy dự án của mình chưa được hoàn thiện theo như kì vọng. Do em cài SDL_mixer bị lỗi nên game không có âm thanh điều đó đã làm game 
     bớt sống động đi rất nhiều.
     
   2. Định hướng phát triển

     Về mặt này thì điều đầu tiên em làm là sẽ thêm phần âm thanh cho game. Sau đó em sẽ thêm các chế độ chơi cho game, ví dụ như: chế độ chơi thường, chế độ chơi 
     có thêm tường, chế độ chơi mà ở đó mỗi loại thức ăn sẽ có công dụng khác nữa, chế độ chơi cho 2 người cùng 1 lúc chẳng hạn. Em có thể cải thiện về mặt hình ảnh 
     của rắn, thức ăn sao cho đẹp hơn. Việc phát triển thêm nhiều tính năng sẽ làm cho game thú vị và đặc sắc hơn.
     
   3. Điều rút ra sau khi làm game

     Điều đầu tiên em rất là vui vì lần đầu trong đời có thể tạo ra được một dự án game dù chỉ là nhỏ và cơ bản thôi. Qua đây em đã được vận dụng kiến thức được học 
     vào thực hành giúp nắm chắc kiến thức và vận dụng một cách thành thạo hơn. Việc nắm được việc làm một game cần phải làm những gì đã giúp em thấy sự khó khăn của 
     các lập trình viên không chỉ trong làm game mà còn làm web, làm ứng dụng,... Đặc biệt nhất qua dự án game lần này em đã rút ra rất nhiều kinh nghiệm. Ví dụ như 
     thay vì viết code vào hết hàm main, đặt tên biến linh tinh thì giờ em đã hiểu cách gọi hàm, gọi tên biến sao cho phù hợp, tách thành nhiều hàm, các lớp để cho 
     chương trình dễ hiểu và sạch đẹp nhất.
      
  
