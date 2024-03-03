-- docgia (ma_docgia, ho, tenlot, ten, ngaysinh)
-- nguoilon (ma_docgia, sonha, duong, quan, dienthoai, han_sd)
-- treem (ma_docgia, ma_docgia_nguoilon)
-- tuasach (ma_tuasach, tuasach, tacgia, tomtat)
-- dausach (isbn, ma_tuasach, ngonngu, bia, trangthai)
-- cuonsach (isbn, ma_cuonsach, tinhtrang)
-- dangky (isbn, ma_docgia, ngay_dk, ghichu)
-- muon (isbn, ma_cuonsach, ma_docgia, ngay_muon, ngay_hethan)
-- qtrinhmuon (isbn, ma_cuonsach, ngay_muon, ma_DocGia, ngay_hethan, ngay_tra, tien_muon, tien_datra, tien_datcoc, ghichu)

-- Drop the tables if they exist
DROP TABLE IF EXISTS qtrinhmuon;
DROP TABLE IF EXISTS muon;
DROP TABLE IF EXISTS dangky;
DROP TABLE IF EXISTS cuonsach;
DROP TABLE IF EXISTS dausach;
DROP TABLE IF EXISTS tuasach;
DROP TABLE IF EXISTS treem;
DROP TABLE IF EXISTS nguoilon;
DROP TABLE IF EXISTS docgia;

-- Create the tables
CREATE TABLE docgia (
    ma_docgia INT IDENTITY(1,1) PRIMARY KEY,
    ho NVARCHAR(50),
    tenlot NVARCHAR(50),
    ten NVARCHAR(50),
    ngaysinh DATE
);

CREATE TABLE nguoilon (
    ma_docgia INT PRIMARY KEY,
    sonha NVARCHAR(50),
    duong NVARCHAR(50),
    quan NVARCHAR(50),
    dienthoai NVARCHAR(20),
    han_sd DATE,
    FOREIGN KEY (ma_docgia) REFERENCES docgia(ma_docgia)
);

CREATE TABLE treem (
    ma_docgia INT PRIMARY KEY,
    ma_docgia_nguoilon INT,
    FOREIGN KEY (ma_docgia) REFERENCES docgia(ma_docgia),
    FOREIGN KEY (ma_docgia_nguoilon) REFERENCES nguoilon(ma_docgia)
);

CREATE TABLE tuasach (
    ma_tuasach INT IDENTITY(1,1) PRIMARY KEY,
    tuasach NVARCHAR(100),
    tacgia NVARCHAR(100),
    tomtat NVARCHAR(MAX)
);

CREATE TABLE dausach (
    isbn NVARCHAR(20) PRIMARY KEY,
    ma_tuasach INT,
    ngonngu NVARCHAR(50),
    bia NVARCHAR(100),
    trangthai NVARCHAR(50),
    FOREIGN KEY (ma_tuasach) REFERENCES tuasach(ma_tuasach)
);

CREATE TABLE cuonsach (
    isbn NVARCHAR(20),
    ma_cuonsach INT IDENTITY(1,1) PRIMARY KEY,
    tinhtrang NVARCHAR(50),
    FOREIGN KEY (isbn) REFERENCES dausach(isbn)
);

CREATE TABLE dangky (
    isbn NVARCHAR(20),
    ma_docgia INT,
    ngay_dk DATE,
    ghichu NVARCHAR(MAX),
    FOREIGN KEY (isbn) REFERENCES dausach(isbn),
    FOREIGN KEY (ma_docgia) REFERENCES docgia(ma_docgia)
);

CREATE TABLE muon (
    isbn NVARCHAR(20),
    ma_cuonsach INT,
    ma_docgia INT,
    ngay_muon DATE,
    ngay_hethan DATE,
    FOREIGN KEY (isbn) REFERENCES dausach(isbn),
    FOREIGN KEY (ma_cuonsach) REFERENCES cuonsach(ma_cuonsach),
    FOREIGN KEY (ma_docgia) REFERENCES docgia(ma_docgia)
);

CREATE TABLE qtrinhmuon (
    isbn NVARCHAR(20),
    ma_cuonsach INT,
    ngay_muon DATE,
    ma_DocGia INT,
    ngay_hethan DATE,
    ngay_tra DATE,
    tien_muon DECIMAL(10,2),
    tien_datra DECIMAL(10,2),
    tien_datcoc DECIMAL(10,2),
    ghichu NVARCHAR(MAX),
    FOREIGN KEY (isbn) REFERENCES dausach(isbn),
    FOREIGN KEY (ma_cuonsach) REFERENCES cuonsach(ma_cuonsach),
    FOREIGN KEY (ma_DocGia) REFERENCES docgia(ma_docgia)
);


-- Seeds data for docgia table
INSERT INTO docgia (ho, tenlot, ten, ngaysinh)
VALUES ('Nguyen', 'Van', 'A', '1990-01-01'),
       ('Tran', 'Thi', 'B', '1995-02-02'),
       ('Le', 'Van', 'C', '1998-03-03');

-- Seeds data for nguoilon table
INSERT INTO nguoilon (ma_docgia, sonha, duong, quan, dienthoai, han_sd)
VALUES (1, '123', 'Nguyen Van Cu', 'Quan 5', '0123456789', '2022-01-01'),
       (2, '456', 'Le Loi', 'Quan 1', '0987654321', '2023-02-02');
-- Seeds data for treem table
INSERT INTO treem (ma_docgia, ma_docgia_nguoilon)
VALUES (3, 1);

-- Seeds data for tuasach table
INSERT INTO tuasach (tuasach, tacgia, tomtat)
VALUES ('Sach 1', 'Tac gia 1', 'Tom tat sach 1'),
       ('Sach 2', 'Tac gia 2', 'Tom tat sach 2'),
       ('Sach 3', 'Tac gia 3', 'Tom tat sach 3');

-- Seeds data for dausach table
INSERT INTO dausach (isbn, ma_tuasach, ngonngu, bia, trangthai)
VALUES ('ISBN1', 1, 'Tieng Viet', 'Bia sach 1', 'Moi'),
       ('ISBN2', 2, 'Tieng Anh', 'Bia sach 2', 'Cu'),
       ('ISBN3', 3, 'Tieng Viet', 'Bia sach 3', 'Moi');

-- Seeds data for cuonsach table
INSERT INTO cuonsach (isbn, tinhtrang)
VALUES ('ISBN1', 'Tot'),
       ('ISBN1', 'Tot'),
       ('ISBN2', 'Cu');

-- Seeds data for dangky table
INSERT INTO dangky (isbn, ma_docgia, ngay_dk, ghichu)
VALUES ('ISBN1', 1, '2022-01-01', 'Ghi chu 1'),
       ('ISBN2', 2, '2023-02-02', 'Ghi chu 2'),
       ('ISBN3', 3, '2024-03-03', 'Ghi chu 3');

-- Seeds data for muon table
INSERT INTO muon (isbn, ma_cuonsach, ma_docgia, ngay_muon, ngay_hethan)
VALUES ('ISBN1', 1, 1, '2022-01-01', '2025-02-01'),
       ('ISBN2', 2, 2, '2023-02-02', '2023-03-02'),
       ('ISBN3', 3, 3, '2024-03-03', '2024-04-03');

-- Seeds data for qtrinhmuon table
INSERT INTO qtrinhmuon (isbn, ma_cuonsach, ngay_muon, ma_DocGia, ngay_hethan, ngay_tra, tien_muon, tien_datra, tien_datcoc, ghichu)
VALUES ('ISBN1', 1, '2022-01-01', 1, '2022-02-01', null, 100000, 50000, 0, 'Ghi chu 1'),
       ('ISBN2', 2, '2023-02-02', 2, '2023-01-02', null, 150000, 100000, 0, 'Ghi chu 2'),
       ('ISBN3', 3, '2024-03-03', 3, '2024-04-03', null, 200000, 150000, 0, 'Ghi chu 3');
GO