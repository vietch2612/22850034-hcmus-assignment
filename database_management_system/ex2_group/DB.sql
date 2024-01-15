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
DROP TABLE IF EXISTS docgia;
DROP TABLE IF EXISTS nguoilon;
DROP TABLE IF EXISTS treem;
DROP TABLE IF EXISTS tuasach;
DROP TABLE IF EXISTS dausach;
DROP TABLE IF EXISTS cuonsach;
DROP TABLE IF EXISTS dangky;
DROP TABLE IF EXISTS muon;
DROP TABLE IF EXISTS qtrinhmuon;

-- Tạo bảng docgia
CREATE TABLE docgia (
    ma_docgia SERIAL PRIMARY KEY,
    ho VARCHAR(255),
    tenlot VARCHAR(255),
    ten VARCHAR(255),
    ngaysinh DATE
);

-- Tạo bảng nguoilon
CREATE TABLE nguoilon (
    ma_docgia SERIAL PRIMARY KEY,
    sonha VARCHAR(255),
    duong VARCHAR(255),
    quan VARCHAR(255),
    dienthoai VARCHAR(15),
    han_sd DATE,
    FOREIGN KEY (ma_docgia) REFERENCES docgia(ma_docgia)
);

-- Tạo bảng treem
CREATE TABLE treem (
    ma_docgia SERIAL PRIMARY KEY,
    ma_docgia_nguoilon INT,
    FOREIGN KEY (ma_docgia) REFERENCES docgia(ma_docgia),
    FOREIGN KEY (ma_docgia_nguoilon) REFERENCES nguoilon(ma_docgia)
);

-- Tạo bảng tuasach
CREATE TABLE tuasach (
    ma_tuasach SERIAL PRIMARY KEY,
    tuasach VARCHAR(255),
    tacgia VARCHAR(255),
    tomtat TEXT
);

-- Tạo bảng dausach
CREATE TABLE dausach (
    isbn VARCHAR(13),
    ma_tuasach INT,
    ngonngu VARCHAR(50),
    bia VARCHAR(255),
    trangthai VARCHAR(50),
    primary key (isbn, ma_tuasach),
    FOREIGN KEY (ma_tuasach) REFERENCES tuasach(ma_tuasach)
);


-- Tạo bảng cuonsach
CREATE TABLE cuonsach (
    isbn VARCHAR(13),
    ma_cuonsach SERIAL,
    tinhtrang VARCHAR(50),
    primary key (isbn, ma_cuonsach)
);

-- Tạo bảng dangky
CREATE TABLE dangky (
    isbn VARCHAR(13),
    ma_docgia SERIAL,
    ngay_dk DATE,
    ghichu TEXT,
    PRIMARY KEY (isbn, ma_docgia),
    FOREIGN KEY (ma_docgia) REFERENCES docgia(ma_docgia)
);

-- Tạo bảng muon
CREATE TABLE muon (
    isbn VARCHAR(13),
    ma_cuonsach SERIAL,
    ma_docgia SERIAL,
    ngay_muon DATE,
    ngay_hethan DATE,
    PRIMARY KEY (isbn, ma_cuonsach, ma_docgia),
    FOREIGN KEY (isbn, ma_cuonsach) REFERENCES cuonsach(isbn, ma_cuonsach),
    FOREIGN KEY (ma_docgia) REFERENCES docgia(ma_docgia)
);

-- Tạo bảng qtrinhmuon
CREATE TABLE qtrinhmuon (
    isbn VARCHAR(13),
    ma_cuonsach SERIAL,
    ngay_muon DATE,
    ma_docgia SERIAL,
    ngay_hethan DATE,
    ngay_tra DATE,
    tien_muon DECIMAL(10, 2),
    tien_datra DECIMAL(10, 2),
    tien_datcoc DECIMAL(10, 2),
    ghichu TEXT,
    PRIMARY KEY (isbn, ma_cuonsach, ma_docgia, ngay_muon),
    FOREIGN KEY (isbn, ma_cuonsach) REFERENCES cuonsach(isbn, ma_cuonsach),
    FOREIGN KEY (ma_docgia) REFERENCES docgia(ma_docgia)
);