-- Seed data
INSERT INTO docgia (ho, tenlot, ten, ngaysinh) VALUES
    ('Nguyen', 'Van', 'A', '1990-01-15'),
    ('Tran', 'Thi', 'B', '1985-05-20'),
    ('Le', 'Duc', 'C', '1992-08-10'),
    ('Pham', 'Van', 'D', '1995-10-01'),
    ('Hoang', 'Thi', 'E', '1998-12-30'),
    ('Nguyen', 'Van', 'F', '1999-03-25'),
    ('Tran', 'Thi', 'G', '1997-04-05'),
    ('Le', 'Duc', 'H', '1996-06-15'),
    ('Pham', 'Van', 'I', '1994-07-20'),
    ('Hoang', 'Thi', 'K', '1993-09-10'),
    ('Nguyen', 'Van', 'L', '1991-11-01'),
    ('Tran', 'Thi', 'M', '1990-12-30'),
    ('Le', 'Duc', 'N', '1989-03-25'),
    ('Pham', 'Van', 'O', '1988-04-05'),
    ('Hoang', 'Thi', 'P', '1987-06-15'),
    ('Nguyen', 'Van', 'Q', '1986-07-20'),
    ('Tran', 'Thi', 'R', '1985-09-10'),
    ('Le', 'Duc', 'S', '1984-11-01'),
    ('Pham', 'Van', 'T', '1983-12-30'),
    ('Hoang', 'Thi', 'U', '1982-03-25'),
    ('Nguyen', 'Van', 'V', '1981-04-05'),
    ('Tran', 'Thi', 'X', '1980-06-15'),
    ('Le', 'Duc', 'Y', '1979-07-20'),
    ('Pham', 'Van', 'Z', '1978-09-10'),
    ('Hoang', 'Thi', 'A', '1977-11-01'),
    ('Nguyen', 'Van', 'B', '1976-12-30'),
    ('Tran', 'Thi', 'C', '1975-03-25'),
    ('Le', 'Duc', 'D', '1974-04-05');


INSERT INTO nguoilon (sonha, duong, quan, dienthoai, han_sd, ma_docgia) VALUES
    ('123', 'Le Loi', 'Quan 1', '123456789', '2023-01-01', 1),
    ('456', 'Nguyen Hue', 'Quan 2', '987654321', '2024-02-15', 2),
    ('789', 'Tran Hung Dao', 'Quan 3', '111222333', '2023-05-10', 3),
    ('101', 'Le Duan', 'Quan 4', '444555666', '2022-08-01', 4),
    ('121', 'Nguyen Thi Minh Khai', 'Quan 5', '777888999', '2021-10-30', 5),
    ('141', 'Tran Quoc Toan', 'Quan 6', '000111222', '2020-03-25', 6),
    ('161', 'Le Hong Phong', 'Quan 7', '333444555', '2020-04-05', 7),
    ('181', 'Nguyen Van Cu', 'Quan 8', '666777888', '2020-06-15', 8),
    ('202', 'Tran Van Kieu', 'Quan 9', '999000111', '2020-07-20', 9),
    ('222', 'Le Van Sy', 'Quan 10', '222333444', '2020-09-10', 10),
    ('242', 'Nguyen Thi Thap', 'Quan 11', '555666777', '2020-11-01', 11),
    ('262', 'Tran Thi Rieng', 'Quan 12', '888999000', '2020-12-30', 12),
    ('282', 'Le Thi Hong Gam', 'Quan Binh Tan', '222333444', '2021-03-25', 13),
    ('303', 'Nguyen Thi Tu', 'Quan Binh Thanh', '555666777', '2021-04-05', 14),
    ('323', 'Tran Thi Nghia', 'Quan Go Vap', '888999000', '2021-06-15', 15),
    ('343', 'Le Thi Rieng', 'Quan Phu Nhuan', '222333444', '2021-07-20', 16),
    ('363', 'Nguyen Thi Thap', 'Quan Tan Binh', '555666777', '2021-09-10', 17),
    ('383', 'Tran Thi Rieng', 'Quan Tan Phu', '888999000', '2021-11-01', 18);

INSERT INTO treem (ma_docgia_nguoilon) VALUES
    (1),
    (2),
    (3),
    (4),
    (5);

INSERT INTO tuasach (tuasach, tacgia, tomtat) VALUES
    ('Tieu thuyet A', 'Tac gia A', 'Tom tat A'),
    ('Sach khoa hoc B', 'Tac gia B', 'Tom tat B'),
    ('Truyen tranh C', 'Tac gia C', 'Tom tat C'),
    ('Truyen ngan D', 'Tac gia D', 'Tom tat D'),
    ('Truyen dai E', 'Tac gia E', 'Tom tat E'),
    ('Truyen ma F', 'Tac gia F', 'Tom tat F'),
    ('Truyen kiem hiep G', 'Tac gia G', 'Tom tat G'),
    ('Truyen tinh cam H', 'Tac gia H', 'Tom tat H'),
    ('Truyen tien hiep I', 'Tac gia I', 'Tom tat I'),
    ('Truyen co tich K', 'Tac gia K', 'Tom tat K'),
    ('Truyen cuoi L', 'Tac gia L', 'Tom tat L'),
    ('Truyen ngan M', 'Tac gia M', 'Tom tat M'),
    ('Truyen dai N', 'Tac gia N', 'Tom tat N'),
    ('Truyen ma O', 'Tac gia O', 'Tom tat O'),
    ('Truyen kiem hiep P', 'Tac gia P', 'Tom tat P'),
    ('Truyen tinh cam Q', 'Tac gia Q', 'Tom tat Q'),
    ('Truyen tien hiep R', 'Tac gia R', 'Tom tat R'),
    ('Truyen co tich S', 'Tac gia S', 'Tom tat S'),
    ('Truyen cuoi T', 'Tac gia T', 'Tom tat T'),
    ('Truyen ngan U', 'Tac gia U', 'Tom tat U'),
    ('Truyen dai V', 'Tac gia V', 'Tom tat V'),
    ('Truyen ma X', 'Tac gia X', 'Tom tat X'),
    ('Truyen kiem hiep Y', 'Tac gia Y', 'Tom tat Y'),
    ('Truyen tinh cam Z', 'Tac gia Z', 'Tom tat Z'),
    ('Truyen tien hiep A', 'Tac gia A', 'Tom tat A'),
    ('Truyen co tich B', 'Tac gia B', 'Tom tat B'),
    ('Truyen cuoi C', 'Tac gia C', 'Tom tat C'),
    ('Truyen ngan D', 'Tac gia D', 'Tom tat D'),
    ('Truyen dai E', 'Tac gia E', 'Tom tat E');

INSERT INTO dausach (isbn, ma_tuasach, ngonngu, bia, trangthai) VALUES
    ('ISBN123', 1, 'Tieng Viet', 'Bia A', 'Moi'),
    ('ISBN456', 2, 'Tieng Anh', 'Bia B', 'Cu'),
    ('ISBN789', 3, 'Tieng Nhat', 'Bia C', 'Moi'),
    ('ISBN101', 4, 'Tieng Viet', 'Bia D', 'Cu'),
    ('ISBN121', 5, 'Tieng Viet', 'Bia E', 'Moi'),
    ('ISBN141', 6, 'Tieng Viet', 'Bia F', 'Cu'),
    ('ISBN161', 7, 'Tieng Viet', 'Bia G', 'Moi'),
    ('ISBN181', 8, 'Tieng Viet', 'Bia H', 'Cu'),
    ('ISBN202', 9, 'Tieng Viet', 'Bia I', 'Moi'),
    ('ISBN222', 10, 'Tieng Viet', 'Bia K', 'Cu'),
    ('ISBN343', 16, 'Tieng Viet', 'Bia Q', 'Cu'),
    ('ISBN363', 17, 'Tieng Viet', 'Bia R', 'Moi'),
    ('ISBN383', 18, 'Tieng Viet', 'Bia S', 'Cu');

INSERT INTO cuonsach (isbn, ma_cuonsach, tinhtrang) VALUES
    ('ISBN123', 1, 'Moi'),
    ('ISBN456', 2, 'Cu'),
    ('ISBN789', 3, 'Moi'),
    ('ISBN101', 4, 'Cu'),
    ('ISBN121', 5, 'Moi'),
    ('ISBN141', 6, 'Cu'),
    ('ISBN161', 7, 'Moi'),
    ('ISBN181', 8, 'Cu'),
    ('ISBN202', 9, 'Moi'),
    ('ISBN222', 10, 'Cu'),
    ('ISBN343', 16, 'Cu'),
    ('ISBN363', 17, 'Moi'),
    ('ISBN383', 18, 'Cu');

INSERT INTO dangky (isbn, ma_docgia, ngay_dk, ghichu) VALUES
    ('ISBN123', 1, '2023-01-05', 'Ghi chu 1'),
    ('ISBN456', 2, '2024-02-20', 'Ghi chu 2'),
    ('ISBN789', 3, '2023-05-15', 'Ghi chu 3');

INSERT INTO muon (isbn, ma_cuonsach, ma_docgia, ngay_muon, ngay_hethan) VALUES
    ('ISBN123', 1, 1, '2023-01-10', '2023-02-10'),
    ('ISBN456', 2, 2, '2024-02-25', '2024-03-25'),
    ('ISBN789', 3, 3, '2023-05-20', '2023-06-20');

INSERT INTO qtrinhmuon (isbn, ma_cuonsach, ngay_muon, ma_docgia, ngay_hethan, ngay_tra, tien_muon, tien_datra, tien_datcoc, ghichu) VALUES
    ('ISBN123', 1, '2023-01-10', 1, '2023-02-10', '2023-02-20', 50.00, 30.00, 20.00, 'Ghi chu muon 1'),
    ('ISBN456', 2, '2024-02-25', 2, '2024-03-25', '2024-04-10', 60.00, 40.00, 20.00, 'Ghi chu muon 2'),
    ('ISBN789', 3, '2023-05-20', 3, '2023-06-20', '2023-07-05', 70.00, 50.00, 20.00, 'Ghi chu muon 3');