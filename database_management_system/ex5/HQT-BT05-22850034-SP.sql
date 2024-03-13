-- Database Management System
-- Homework 04
-- MSSV: 22850034
-- Họ và tên: Cao Hoài Việt
-- Email: 22850034@student.hcmus.edu.vn


-- Stored procedure BT5-11 (Xóa độc giả)
-- Tên: sp_XoaDocGia_22850034
-- Tham số: @ma_docgia INT
DROP PROCEDURE sp_XoaDocGia_22850034;
GO

CREATE PROCEDURE sp_XoaDocGia_22850034
    @ma_docgia INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1: Check if the reader exists
    IF NOT EXISTS (SELECT * FROM docgia WHERE ma_docgia = @ma_docgia)
    BEGIN
        PRINT 'ERROR: Ma doc gia khong ton tai';
        RETURN;
    END

    -- Step 2: Check if the reader is borrowing books
    IF EXISTS (SELECT * FROM muon WHERE ma_docgia = @ma_docgia)
    BEGIN
        PRINT 'ERROR: Khong the xoa doc gia duoc vi doc gia dang muon sach!';
        RETURN;
    END

    -- Step 3: Check if the reader is an adult or a child
    IF EXISTS (SELECT * FROM nguoilon WHERE ma_docgia = @ma_docgia)
    -- Step 3.1: If the reader is an adult
    BEGIN
        -- Step 3.1.1: Check if the reader sponsors any children
        DECLARE @count_children INT = (SELECT COUNT(*) FROM treem WHERE ma_docgia_nguoilon = @ma_docgia);
        -- Step 3.1.2: If the reader does not sponsor children
        IF @count_children = 0
        BEGIN
            -- Step 3.1.2.1: Delete data in the NguoiLon table, QuaTrinhMuon table, DangKy table
            DELETE FROM qtrinhmuon WHERE ma_docgia = @ma_docgia;
            DELETE FROM dangky WHERE ma_docgia = @ma_docgia;
            DELETE FROM nguoilon WHERE ma_docgia = @ma_docgia;
            -- Step 3.1.2.2: Finally, delete the data in the DocGia table
            DELETE FROM docgia WHERE ma_docgia = @ma_docgia;
        END
        -- Step 3.1.3: If the reader sponsors children
        ELSE
        BEGIN
            -- Step 3.1.3.1 Find the children that this reader sponsors and delete the data of these children
            DELETE FROM treem WHERE ma_docgia_nguoilon = @ma_docgia;
            -- Step 3.1.3.2 Delete data in the NguoiLon table, QuaTrinhMuon table, DangKy table (of this reader and corresponding children)
            DELETE FROM qtrinhmuon WHERE ma_docgia = @ma_docgia;
            DELETE FROM dangky WHERE ma_docgia = @ma_docgia;
            DELETE FROM treem WHERE ma_docgia = @ma_docgia;
            DELETE FROM nguoilon WHERE ma_docgia = @ma_docgia;
            -- Step 3.1.3.3 Finally, delete the data in the DocGia table
            DELETE FROM docgia WHERE ma_docgia = @ma_docgia;
        END
    END
    ELSE
    -- Step 3.2: If the reader is a child
    BEGIN
        -- Step 3.2.1: Delete data in the TreEm table, QuaTrinhMuon table, DangKy table
        DELETE FROM treem WHERE ma_docgia = @ma_docgia;
        DELETE FROM qtrinhmuon WHERE ma_docgia = @ma_docgia;
        DELETE FROM dangky WHERE ma_docgia = @ma_docgia;
        -- Step 3.2.2: Finally, delete the data in the DocGia table
        DELETE FROM docgia WHERE ma_docgia = @ma_docgia;
    END
END
GO


-- Stored procedure BT5-12 (Mượn sách)
-- Tên: sp_MuonSach_22850034
-- Tham số: @ma_docgia INT, @isbn CHAR(13)
DROP PROCEDURE sp_MuonSach_22850034;
GO

CREATE PROCEDURE sp_MuonSach_22850034
    @ma_docgia INT,
    @isbn CHAR(13)
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1: Check if the reader is borrowing a book of the same type
    IF EXISTS (SELECT * FROM muon WHERE ma_docgia = @ma_docgia AND isbn 
            IN (SELECT isbn FROM dausach WHERE ma_tuasach IN (SELECT ma_tuasach FROM dausach WHERE isbn = @isbn)))
    BEGIN
        -- Step 1.1: Error message
        PRINT 'ERROR: Doc gia dang muon cuon sach cung loai!';
        RETURN;
    END

    -- Step 2: Check the number of books the reader is borrowing
    DECLARE @borrowing_books INT = (SELECT COUNT(*) FROM muon WHERE ma_docgia = @ma_docgia AND ma_cuonsach NOT IN 
                                    (SELECT ma_cuonsach FROM qtrinhmuon WHERE ma_docgia = @ma_docgia));
    -- Step 2.1 Check if the reader is an adult or a child
    IF EXISTS (SELECT * FROM nguoilon WHERE ma_docgia = @ma_docgia)
    BEGIN
        -- Step 2.1.1: If the reader is an adult
        DECLARE @borrowing_books_by_child INT = (SELECT COUNT(*) 
                                                FROM qtrinhmuon q 
                                                LEFT JOIN treem t 
                                                ON q.ma_docgia = t.ma_docgia AND q.ma_docgia = @ma_docgia
                                                WHERE q.ma_DocGia = @ma_docgia AND q.ngay_tra IS NULL
                                                GROUP BY q.ma_DocGia);
        -- Step 2.1.2: If the reader is borrowing 5 books
        IF @borrowing_books + @borrowing_books_by_child >= 5
        BEGIN
            -- Show error message
            PRINT 'ERROR: Doc gia dang muon 5 cuon sach. Khong the muon them!';
            RETURN;
        END
    END
    ELSE
    BEGIN
        -- Step 2.2: If the reader is a child
        -- Step 2.2.1: If the reader is borrowing 1 book
        IF @borrowing_books = 1
        BEGIN
            -- Show error message
            PRINT 'ERROR: Doc gia la tre em. Chi co the muon toi da 1 cuon sach!';
            RETURN;
        END
    END

    -- Step 3: Check if there are any books left in the library
    DECLARE @remaining_books INT = (SELECT COUNT(*) FROM cuonsach WHERE isbn = @isbn AND tinhtrang = 'Y');
    -- Step 3.1: If there are books left
    IF @remaining_books > 0
    BEGIN
        -- Step 3.1.1: Insert a new record to the muon table
        INSERT INTO muon (isbn, ma_cuonsach, ma_docgia, ngay_muon, ngay_hethan) VALUES (
            @isbn, 
            (SELECT TOP 1 ma_cuonsach FROM cuonsach WHERE isbn = @isbn AND tinhtrang = 'Y'), 
            @ma_docgia, 
            GETDATE(),
            GETDATE() + 14
        );
        -- Step 3.1.2: Update the status of the book
        UPDATE cuonsach SET tinhtrang = 'N' WHERE ma_cuonsach = (SELECT TOP 1 ma_cuonsach FROM cuonsach WHERE isbn = @isbn AND tinhtrang = 'Y');
        -- Step 3.1.3: Update the status of the corresponding book
        EXEC sp_CapnhatTrangthaiDausach_22850034 @isbn;
        -- Step 3.1.4: Inform successful borrowing
        PRINT 'Muon sach thanh cong!';
    END
    ELSE
    BEGIN
    -- Step 3.2: If there are no books left
        -- Step 3.2.1: Inform the reader to wait
        PRINT 'Khong con sach trong thu vien. Vui long cho!';
        -- Step 3.2.2: Insert a new record to the DangKy table
        INSERT INTO dangky (ma_docgia, isbn) VALUES (@ma_docgia, @isbn);
    END
END
GO

-- Stored procedure BT5-13 (Trả sách)
-- Tên: sp_TraSach_22850034
-- - Nôi dung: Khi độc giả trả sách thì hệ thống phải chuyển thông tin mượn sang bảng quá trình mượn.
-- • Tham số: Sinh viên tự xác định.
-- • Bước thực hiên:
-- [1] Xác định tiền phạt nếu trả quá hạn (= 1000đ * số ngày trễ hạn)
-- [2] Thêm vào bảng quá trình mượn.
-- [3] Xóa dữ liệu trong bảng mượn.

DROP PROCEDURE sp_TraSach_22850034;
GO

CREATE PROCEDURE sp_TraSach_22850034
    @ma_docgia INT,
    @isbn CHAR(13)
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1: Check if the reader is borrowing the book
    IF NOT EXISTS (SELECT * FROM muon WHERE ma_docgia = @ma_docgia AND isbn = @isbn)
    BEGIN
        -- Step 1.1: Show error message
        PRINT 'ERROR: Doc gia khong muon cuon sach nay!';
        RETURN;
    END

    -- Step 2: Calculate the fine
    DECLARE @fine INT = (SELECT DATEDIFF(DAY, ngay_hethan, GETDATE()) * 1000 FROM muon WHERE ma_docgia = @ma_docgia AND isbn = @isbn AND ngay_hethan IS NULL);
    -- Step 2.1: If the reader returns the book on time
    IF @fine < 0
    BEGIN
        -- Step 2.1.1: Set the fine to 0
        SET @fine = 0;
    END

    -- Step 3: Insert a new record to the qtrinhmuon table
    INSERT INTO qtrinhmuon (isbn, ma_cuonsach, ngay_muon, ma_DocGia, ngay_hethan, ngay_tra, tien_muon, tien_datra, tien_datcoc, ghichu) 
    VALUES (
        @isbn, 
        (SELECT ma_cuonsach FROM muon WHERE ma_docgia = @ma_docgia AND isbn = @isbn), 
        (SELECT ngay_muon FROM muon WHERE ma_docgia = @ma_docgia AND isbn = @isbn), 
        @ma_docgia, 
        (SELECT ngay_hethan FROM muon WHERE ma_docgia = @ma_docgia AND isbn = @isbn), 
        GETDATE(), 
        (SELECT DATEDIFF(DAY, ngay_muon, ngay_hethan) * 1000 FROM muon WHERE ma_docgia = @ma_docgia AND isbn = @isbn AND ngay_hethan IS NULL), 
        @fine, 
        0, 
        NULL
    );

    -- Step 4: Delete the data in the muon table
    DELETE FROM muon WHERE ma_docgia = @ma_docgia AND isbn = @isbn;
    -- Step 4.1: Update the status of the book
    UPDATE cuonsach SET tinhtrang = 'Y' WHERE ma_cuonsach = (SELECT ma_cuonsach FROM qtrinhmuon WHERE ma_docgia = @ma_docgia AND isbn = @isbn AND ngay_tra IS NOT NULL);
    -- Step 4.2: Update the status of the corresponding book
    EXEC sp_CapnhatTrangthaiDausach_22850034 @isbn;
    -- Step 4.3: Inform successful return
    PRINT 'Tra sach thanh cong!';
END
GO