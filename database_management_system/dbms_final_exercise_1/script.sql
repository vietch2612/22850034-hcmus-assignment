DROP TABLE IF EXISTS BangDiem;
DROP TABLE IF EXISTS ThucHienLV;
DROP TABLE IF EXISTS LuanVan;
DROP TABLE IF EXISTS SinhVien;
DROP TABLE IF EXISTS GiangVien;
DROP TABLE IF EXISTS Khoa;

CREATE TABLE Khoa (
    MaKhoa INT PRIMARY KEY,
    TenKhoa NVARCHAR(255) NOT NULL,
    GVTruongKhoa NVARCHAR(255) NOT NULL
);

CREATE TABLE GiangVien (
    MaGV INT PRIMARY KEY,
    HoTen NVARCHAR(255) NOT NULL,
    GioiTinh NVARCHAR(255) NOT NULL,
    NgaySinh DATE NOT NULL,
    DiaChi NVARCHAR(255) NOT NULL,
    ThuocKhoa INT NOT NULL,
    FOREIGN KEY (ThuocKhoa) REFERENCES Khoa(MaKhoa)
);

CREATE TABLE SinhVien (
    MSSV INT PRIMARY KEY,
    HoTen NVARCHAR(255) NOT NULL,
    GioiTinh NVARCHAR(255) NOT NULL,
    NgaySinh DATE NOT NULL,
    DiaChi NVARCHAR(255) NOT NULL,
    HocLop INT NOT NULL,
    ThuocKhoa INT NOT NULL,
    FOREIGN KEY (ThuocKhoa) REFERENCES Khoa(MaKhoa)
);

CREATE TABLE LuanVan (
    MaLV INT PRIMARY KEY,
    TenLV NVARCHAR(255) NOT NULL,
    ThuocKhoa INT NOT NULL,
    NamThucHien INT NOT NULL,
    FOREIGN KEY (ThuocKhoa) REFERENCES Khoa(MaKhoa)
);

CREATE TABLE ThucHienLV (
    MaLV INT NOT NULL,
    MSSV INT NOT NULL,
    FOREIGN KEY (MaLV) REFERENCES LuanVan(MaLV),
    FOREIGN KEY (MSSV) REFERENCES SinhVien(MSSV)
);

CREATE TABLE BangDiem (
    MaLV INT NOT NULL,
    MaSVThucHien INT NOT NULL,
    MaGVDanhGia INT NOT NULL,
    VaiTro NVARCHAR(255) NOT NULL,
    Diem FLOAT NOT NULL,
    FOREIGN KEY (MaLV) REFERENCES LuanVan(MaLV),
    FOREIGN KEY (MaSVThucHien) REFERENCES SinhVien(MSSV),
    FOREIGN KEY (MaGVDanhGia) REFERENCES GiangVien(MaGV)
);

INSERT INTO Khoa VALUES (1, N'Khoa Công nghệ thông tin', N'Nguyễn Thị Thanh Hương');
INSERT INTO Khoa VALUES (2, N'Khoa Kinh tế', N'Nguyễn Thị Tèo');
INSERT INTO Khoa VALUES (3, N'Khoa Ngoại ngữ', N'Nguyễn Thị Tò');

INSERT INTO GiangVien VALUES (1, N'Nguyễn Văn A', N'Nam', '1999-01-01', N'Đà Nẵng', 1);
INSERT INTO GiangVien VALUES (2, N'Nguyễn Văn B', N'Nam', '1999-01-01', N'Đà Nẵng', 2);
INSERT INTO GiangVien VALUES (3, N'Nguyễn Văn C', N'Nam', '1999-01-01', N'Đà Nẵng', 3);

INSERT INTO SinhVien VALUES (1, N'Nguyễn Thị A', N'Nữ', '1999-01-01', N'Đà Nẵng', 1, 1);
INSERT INTO SinhVien VALUES (2, N'Nguyễn Thị B', N'Nữ', '1999-01-01', N'Đà Nẵng', 2, 2);
INSERT INTO SinhVien VALUES (3, N'Nguyễn Thị C', N'Nữ', '1999-01-01', N'Đà Nẵng', 3, 3);

INSERT INTO LuanVan VALUES (1, N'Lập trình hướng đối tượng', 1, 2021);
INSERT INTO LuanVan VALUES (2, N'Kinh tế học', 2, 2021);
INSERT INTO LuanVan VALUES (3, N'Tiếng Anh', 3, 2021);
INSERT INTO LuanVan VALUES (4, N'Tiếng Anh', 3, 2021);
INSERT INTO LuanVan VALUES (5, N'Tiếng Anh', 3, 2022);
INSERT INTO LuanVan VALUES (6, N'Tiếng Anh', 3, 2021);
SELECT * FROM LuanVan;

INSERT INTO ThucHienLV VALUES (1, 1);
INSERT INTO ThucHienLV VALUES (2, 2);
INSERT INTO ThucHienLV VALUES (3, 3);

INSERT INTO BangDiem VALUES (1, 1, 1, N'Sinh viên', 10);
INSERT INTO BangDiem VALUES (2, 2, 2, N'Sinh viên', 9);
INSERT INTO BangDiem VALUES (3, 3, 3, N'Sinh viên', 8);
GO


CREATE OR ALTER TRIGGER tg_22850034_ThuchienLV ON ThucHienLV
FOR
    INSERT, UPDATE, DELETE
AS
BEGIN
    IF EXISTS (SELECT 1 FROM inserted)
    BEGIN
        DECLARE @MaLV INT, @MSSV INT, @NamThucHien INT;
        -- SET values
        SELECT @MaLV = MaLV, @MSSV = MSSV FROM inserted;
        SELECT @NamThucHien = NamThucHien FROM LuanVan WHERE MaLV = @MaLV;
        IF EXISTS (SELECT 1 FROM ThucHienLV WHERE MSSV = @MSSV AND MaLV IN (SELECT MaLV FROM LuanVan WHERE NamThucHien = @NamThucHien))
        BEGIN
            PRINT 'Mot sinh vien khong the thuc hien 2 lan dang ki cac luan van cung 1 nam';
            RETURN;
        END
    END
END
GO

CREATE OR ALTER PROCEDURE usp_22850034_ThuchienLV
    @maLV_22850034 INT,
    @maSVTH1_22850034 INT,
    @maSVTH2_22850034 INT
AS
BEGIN
    -- 1. Kiem tra xem MaLV co ton tai hay khong
    IF NOT EXISTS (SELECT 1 FROM LuanVan WHERE MaLV = @maLV_22850034)
    BEGIN
        PRINT 'Ma luan van ' + CAST(@maLV_22850034 AS NVARCHAR(100)) + ' khong ton tai.';
        RETURN;
    END

    -- 2. Kiem tra xem MSSV cua 2 sv co ton tai hay khong
    IF NOT EXISTS (SELECT 1 FROM SinhVien WHERE MSSV = @maSVTH1_22850034)
    BEGIN
        PRINT 'MSSV ' + CAST(@maSVTH1_22850034 AS NVARCHAR(100)) + ' khong ton tai.';
        RETURN;
    END

    IF NOT EXISTS (SELECT 1 FROM SinhVien WHERE MSSV = @maSVTH1_22850034)
    BEGIN
        PRINT 'MSSV ' + CAST(@maSVTH2_22850034 AS NVARCHAR(100)) + ' khong ton tai.';
        RETURN;
    END

    SELECT * FROM SinhVien WHERE MSSV IN (@maSVTH1_22850034, @maSVTH2_22850034);

    -- 3. Kiem tra Luan Van da duoc assign cho sinh vien nao hay chua
    IF EXISTS (SELECT 1 FROM ThucHienLV WHERE MaLV = @maLV_22850034)
    BEGIN
        PRINT 'MaLV ' + CAST(@maLV_22850034 AS NVARCHAR(100)) + ' da duoc phan cong.';
        RETURN;
    END

    -- 4. 
    DECLARE @NamThucHien INT, @TenLV NVARCHAR(255);
    SELECT @NamThucHien = NamThucHien FROM LuanVan WHERE MaLV = @maLV_22850034;
    -- 4.1 Kiem tra SV1
    IF EXISTS (SELECT 1 FROM ThucHienLV WHERE MSSV = @maSVTH1_22850034 AND MaLV IN (SELECT MaLV FROM LuanVan WHERE NamThucHien = @NamThucHien))
    BEGIN
        SELECT @TenLV = TenLV FROM LuanVan WHERE MaLV IN (SELECT MaLV FROM ThucHienLV WHERE MSSV = @maSVTH1_22850034) AND NamThucHien = @NamThucHien;
        PRINT 'Sinh vien thu nhat da thuc hien de tai ' + @TenLV + ' trong nam ' + CAST(@NamThucHien AS NVARCHAR(255)) + '.';
        RETURN;
    END
    -- 4.1 Kiem tra SV2
    IF EXISTS (SELECT 1 FROM ThucHienLV WHERE MSSV = @maSVTH2_22850034 AND MaLV IN (SELECT MaLV FROM LuanVan WHERE NamThucHien = @NamThucHien))
    BEGIN
        SELECT @TenLV = TenLV FROM LuanVan WHERE MaLV IN (SELECT MaLV FROM ThucHienLV WHERE MSSV = @maSVTH2_22850034) AND NamThucHien = @NamThucHien;
        PRINT 'Sinh vien thu nhat da thuc hien de tai ' + @TenLV + ' trong nam ' + CAST(@NamThucHien AS NVARCHAR(255)) + '.';
        RETURN;
    END

    -- 5,6. Them 2 dong du lieu moi
    BEGIN TRY
        BEGIN TRANSACTION
            SET IDENTITY_INSERT ThucHienLV ON;
            INSERT INTO ThucHienLV VALUES (@maLV_22850034, @maSVTH1_22850034);
            INSERT INTO ThucHienLV VALUES (@maLV_22850034, @maSVTH2_22850034);
            SET IDENTITY_INSERT ThucHienLV OFF;
        COMMIT TRANSACTION
        PRINT 'Them thanh cong ma luan van ' + CAST(@maLV_22850034 AS NVARCHAR(100)) + ' cho MSSV ' + CAST(@maSVTH1_22850034 AS NVARCHAR(100));
        PRINT 'Them thanh cong ma luan van ' + CAST(@maLV_22850034 AS NVARCHAR(100)) + ' cho MSSV ' + CAST(@maSVTH2_22850034 AS NVARCHAR(100));
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
    END CATCH
END
GO

CREATE OR ALTER FUNCTION fn_GetClassValue(@ClassChar NVARCHAR(10))
RETURNS FLOAT
AS
BEGIN
    DECLARE @value FLOAT;
    IF @ClassChar = 'C' SET @value = 2.00
    IF @ClassChar = 'I' SET @value = 1.50
    IF @ClassChar = 'Y' SET @value = 1.25
    IF @ClassChar = 'K' SET @value = 1.00
    IF @ClassChar = 'T' SET @value = 0.50

    RETURN @value
END
GO

CREATE OR ALTER FUNCTION fnMSSV_TinhDam(@HangVe NVARCHAR(10), @KhoangCach INT)
RETURNS FLOAT
AS
BEGIN
    DECLARE @return_value FLOAT;
    SET @return_value = @KhoangCach * dbo.fn_GetClassValue(@HangVe);
    RETURN @return_value;
END
GO

CREATE OR ALTER PROCEDURE sp22850034_ThemDamChoKhachHang
    @MaVMB INT,
    @MaKH INT
AS
BEGIN
    -- 1. Check exists
    IF NOT EXISTS (SELECT 1 FROM VeMayBay WHERE MaVMB = @MaVMB)
    BEGIN
        PRINT 'Ma ve may bay ' + CAST(@MaVMB AS NVARCHAR(50)) + ' khong ton tai.';
        RETURN;
    END
    IF NOT EXISTS (SELECT 1 FROM KhachHang WHERE MaKH = @MaKH)
    BEGIN
        PRINT 'Ma ve khach hang ' + CAST(@MaKH AS NVARCHAR(50)) + ' khong ton tai.';
        RETURN;
    END

    -- 2. Print the info
    SELECT * FROM KhachHang WHERE MaKH = @MaKH;
    SELECT * FROM VeMayBay WHERE MaVMB = @MaVMB;

    -- 3. Check
    IF EXISTS (SELECT 1 FROM VeMayBay WHERE MaVMB = @MaVMB AND TrangThai = 1)
    BEGIN
        PRINT 'Ve may bay da duoc thuc hien';
        RETURN;
    END

    -- 4. Cap nhat
    UPDATE VeMayBay SET TrangThai = 1 WHERE MaVMB = @MaVMB;

    -- 5. Tinh dam bay
    DECLARE @DamBay FLOAT;
    DECLARE @HangVe CHAR(1);
    DECLARE @DamBay INT;
    SET @DamBay = dbo.fnMSSV_TinhDam()

END

DECLARE @test FLOAT;
SET @test = dbo.fnMSSV_TinhDam('I', 1000);
PRINT(CAST(@test AS NVARCHAR(255)));

INSERT INTO ThucHienLV VALUES (4, 1);
EXEC usp_22850034_ThuchienLV 6, 1, 2

SELECT * FROM ThucHienLV
LEFT JOIN SinhVien ON ThucHienLV.MSSV = SinhVien.MSSV