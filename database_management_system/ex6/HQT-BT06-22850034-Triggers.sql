-- Database Management System
-- Homework 06
-- MSSV: 22850034
-- Họ và tên: Cao Hoài Việt
-- Email: 22850034@student.hcmus.edu.vn


-- BT6-01 tg_delMuon
-- Trigger trên quan hệ Mượn. 
-- Khi có thao tác xoá 1 dòng trong quan hệ, hãy cập nhật tình trạng của cuốn ách tương ứng trong quan hệ Cuốn sách là giá trị 'Yes'

-- Bảng tầm ảnh hưởng:
--------------------------------------
-- Quan hệ | Insert | Update | Delete
-- muon    | -      | -      | +
--------------------------------------
CREATE OR ALTER TRIGGER tg_delMuon
ON muon
AFTER DELETE
AS
BEGIN
    UPDATE cuonSach
    SET tinhTrang = 'Y'
    FROM cuonSach
    INNER JOIN deleted
    ON cuonSach.ma_cuonsach = deleted.ma_cuonsach;
    PRINT 'TRIGGER tg_delMuon: Cap nhat tinh trang cua ma_cuonsach thanh cong';
END;
GO

-- Test cases
-- UPDATE cuonsach SET tinhtrang = 'N' WHERE ma_cuonsach = 1;
-- SELECT * FROM cuonsach WHERE ma_cuonsach = 1;
-- SELECT * FROM muon WHERE ma_cuonsach = 1;
-- DELETE FROM muon WHERE ma_cuonsach = 1;
-- SELECT * FROM cuonsach WHERE ma_cuonsach = 1;
-- GO


-- BT6.2. tg_insMuon:
-- Nội dung: Trịgger trên quan hệ Mượn.
-- Khi có thao tác thêm 1 dòng mới vào quan hệ
-- Hãy Cập nhật tình trạng của cuốn sách tương ứng trong quan hệ Cuốn sách là giá trị 'N'.
-- Bảng tầm ảnh hưởng:
--------------------------------------
-- Quan hệ | Insert | Update | Delete
-- muon    | +      | -      | -
--------------------------------------
CREATE OR ALTER TRIGGER tg_insMuon
ON muon
AFTER INSERT
AS
BEGIN
    -- Cập nhật tình trạng của cuốn sách
    UPDATE cuonSach
    SET tinhTrang = 'N'
    FROM cuonSach
    INNER JOIN inserted
    ON cuonSach.ma_cuonsach = inserted.ma_cuonsach;
    PRINT 'TRIGGER tg_insMuon: Cap nhat tinh trang cua cuon sach thanh cong!';
END;
GO

-- Test cases
-- DECLARE @ma_cuonsach INT;
-- SET @ma_cuonsach = 1;
-- INSERT INTO muon (ma_cuonsach, ma_docgia, ngay_muon, ngay_hethan) VALUES (@ma_cuonsach, 1, '2021-01-01', '2021-01-01');
-- SELECT * FROM cuonsach WHERE ma_cuonsach = @ma_cuonsach;


-- BT6.3. tg_updCuonSach:
-- Nội dung: Trigger trên quan hệ Cuốn Sách.
-- Khi thuộc tính tình trạng của 1 cuốn sách trên bảng cuốn sách được cập nhật thì
-- Trạng thái của đầu sách cũng được cập nhật tương ứng theo quy định của quản lý thư viện.
-- Bảng tầm ảnh hưởng:
--------------------------------------
-- Quan hệ   | Insert | Update | Delete
-- cuonsach  | -      | +      | -
--------------------------------------
CREATE OR ALTER TRIGGER tg_updCuonSach
ON cuonSach
AFTER UPDATE
AS
BEGIN
    -- Cập nhật tình trạng của đầu sách
    -- Using [dbo].[sp_CapnhatTrangthaiDausach_22850034]
    DECLARE @isbn NVARCHAR(20);
    DECLARE isbn_cursor CURSOR FOR 
    SELECT DISTINCT isbn FROM inserted;

    -- Trong trường hợp nhiều cuốn sách và đầu sách được cập nhật cùng một lúc
    -- Thì sẽ có nhiều ISBN/Đầu sách cần được cập nhật
    -- Nên em sẽ sử dụng con trỏ để loop qua từng ISBN để update.
    OPEN isbn_cursor
    FETCH NEXT FROM isbn_cursor INTO @isbn
    WHILE @@FETCH_STATUS = 0
    BEGIN
        -- Cập nhật trạng thái của đầu sách suwr dụng stored procedure được tạo ở bài 4
        EXEC sp_CapnhatTrangthaiDausach_22850034 @isbn;
        PRINT 'TRIGGER tg_updCuonSach: Cap nhat trang thai cua ISBN: ' + @isbn + ' thanh cong';
        FETCH NEXT FROM isbn_cursor INTO @isbn
    END

    -- Giải phóng bộ nhớ của con trỏ
    CLOSE isbn_cursor;
    DEALLOCATE isbn_cursor;
END;

-- Test cases
-- UPDATE cuonsach SET tinhtrang = 'N' WHERE ma_cuonsach = 1;
-- UPDATE cuonsach SET tinhtrang = 'N' WHERE ma_cuonsach IN (1, 8);
-- Update nhiều cuốn sách cùng một lúc
-- UPDATE cuonsach SET tinhtrang = 'N';