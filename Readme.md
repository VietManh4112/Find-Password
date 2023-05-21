## Password Finding Problem
Cho một mật khẩu cho trước gồm N ký tự(bao gồm chữ cái, dấu, chữ số và khoảng trắng). Sử dụng thuật toán di truyền(GAs) để tìm ra được chuỗi mật khẩu tương ứng với chuỗi mật khẩu đề bài.

### Initial Population- Khởi tạo quần thể
- Nhìn chung thuật toán sẽ mô phỏng lại hầu hết những hiện tượng xảy ra trong quá trình tiến hóa của động vật. Vì vậy để thuật toán có thể vận hành được, thì điều đầu tiên cần có chính là Quần thể. Xét bài toán tìm mật khẩu, quần thể sẽ bao gồm những chuỗi N kí tự, được sinh ra ngẫu nhiên.

![image](https://nerophung.github.io/assets/img/2020-05-28-genetic-algorithm/step1.png)

### Evaluation Fitness - Đánh giá năng lực
- Tiếp theo, mỗi chuỗi mật khẩu sẽ được đánh giá sự chính xác so với mật khẩu cho trước, với mỗi kí tự giống với mật khẩu cho trước tại đúng vị trí sẽ được 1 point.

![image](https://nerophung.github.io/assets/img/2020-05-28-genetic-algorithm/step2.png)

- Thành phần Point ở đây sẽ đại diện cho khả năng sinh tồn của cá thể trong quần thể, càng lớn tức cá thể đó càng thích nghi với môi trường tốt.

### Selection - Chọn lọc
- Sau khi đã đánh giá được quần thể, các cá thể có khả năng sinh tồn tốt hơn sẽ có cơ hội được sinh sản nhiều hơn các cá thể còn lại. Các chuỗi kí tự mật khẩu sẽ được lựa chọn theo số Point đang có.

![image](https://nerophung.github.io/assets/img/2020-05-28-genetic-algorithm/step3.png)

### Crossover - Sinh sản
- Vào giai đoạn sinh sản, các cá thể con sẽ được kế thừa các đặc tính từ cả bố và mẹ. Thông thường, cá thể con sẽ nhận một nửa gen từ mỗi bố, mẹ.

![image](https://nerophung.github.io/assets/img/2020-05-28-genetic-algorithm/step4.png)

- Cá thể con có thể sẽ thích nghi tốt hơn, hoặc kém hơn. Ngoài ra, có những kiểu lai tạo khác nhau như 2 Point, Uniform Selection.

![image](https://nerophung.github.io/assets/img/2020-05-28-genetic-algorithm/step5.png)

![image](https://nerophung.github.io/assets/img/2020-05-28-genetic-algorithm/step6.png)

### Mutation - Đột biến
- Dễ nhận thấy rằng, nếu chỉ bằng việc sinh ngẫu nhiên và lai tạo, sẽ rất khó để tìm được nghiệm. Trừ khi cá thể khởi tạo phù hợp luôn với yêu cầu đề bài, tức là có đáp án luôn từ đầu - Ăn May. Như đã nói từ đầu, Đột biến chính là nguyên liệu của Chọn lọc tự nhiên, bằng việc lựa chọn ngẫu nhiên các vị trí và thay thế bằng một kí tự ngẫu nhiên nào đó, chúng ta có thể mô phỏng lại hiện tượng đột biến - Đột biến điểm.

![image](https://nerophung.github.io/assets/img/2020-05-28-genetic-algorithm/step7.png)

- Các cá thể đột biến có thể sẽ có khả năng thích nghi tốt hơn (1 -> 2), hoặc cũng có thể ngược lại (4 -> 3). Quá trình này sẽ lặp lại cho đến khi tìm được đáp án phù hợp.

