-- Database Management System
-- Homework 02
-- MSSV: 22850034
-- Họ và tên: Cao Hoài Việt
-- Email: 22850034@student.hcmus.edu.vn


-- Stored procedure BT3-1 (Thông tin độc giả)
-- Tên: sp_ThongtinDocGia_22850034
-- Tham số: ma_docgia (INT)
-- Nội dung: Liệt kê thông tin của độc giả có mã số ma_docgia.
-- Buớc 0: Kiểm tra xem độc giả có tồn tại không.
-- Nếu không tồn tại, in ra thông báo lỗi.
-- Buớc 1: Kiểm tra xem độc giả là người lớn hay trẻ em.
-- 1.1 Nếu là người lớn, in ra thông tin của độc giả đó 
-- (mã số độc giả, họ, tên lót, tên, ngày sinh, số nhà, đường, quận, điện thoại, hạn sử dụng).
-- 1.2 Nếu là trẻ em, in ra thông tin của độc giả trẻ em và thông tin của người lớn bảo lãnh đó
-- (mã số độc giả, họ, tên lót, tên, ngày sinh, số nhà, đường, quận, điện thoại, hạn sử dụng).
-- Số nhà, đường, quận, điện thoại, hạn sử dụng là thông tin của người lớn bảo lãnh.

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_ThongtinDocGia_22850034') AND type in (N'P', N'PC'))
    DROP PROCEDURE sp_ThongtinDocGia_22850034;
GO

CREATE PROCEDURE sp_ThongtinDocGia_22850034
    @ma_docgia INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 0: Check if the reader exists
    IF NOT EXISTS (SELECT * FROM docgia WHERE ma_docgia = @ma_docgia)
    BEGIN
        PRINT 'ERROR: Ma doc gia khong ton tai!';
        RETURN;
    END

    -- Step 1: Check if the reader is an adult or a child
    IF EXISTS (SELECT * FROM nguoilon WHERE ma_docgia = @ma_docgia)
    BEGIN
        -- Step 1.1: Print the adult reader's information
        SELECT d.ma_docgia, d.ho, d.tenlot, d.ten, d.ngaysinh, n.sonha, n.duong, n.quan, n.dienthoai, n.han_sd
        FROM docgia d
        JOIN nguoilon n ON d.ma_docgia = n.ma_docgia
        WHERE d.ma_docgia = @ma_docgia;
    END
    ELSE
    BEGIN
        -- Step 1.2: Print the child reader's information and the adult of the child information
        SELECT t.ma_docgia, d.ho, d.tenlot, d.ten, d.ngaysinh, n.sonha, n.duong, n.quan, n.dienthoai, n.han_sd
        FROM treem t
        INNER JOIN docgia d ON t.ma_docgia = d.ma_docgia
        INNER JOIN nguoilon n ON t.ma_docgia_nguoilon = n.ma_docgia
        WHERE t.ma_docgia = @ma_docgia;
    END
END
GO


-- Stored procedure BT3-2 (Thông tin đầu sách)
-- Tên: sp_ThongtinDausach_22850034
-- Tham số: isbn (NVARCHAR(20))
-- Nội dung: Liệt kê thông tin của đầu sách có mã số isbn.
-- Buớc 0: Kiểm tra xem đầu sách có tồn tại không.
-- Nếu không tồn tại, in ra thông báo lỗi.
-- Buớc 1: In ra thông tin của đầu sách đó
-- (mã số đầu sách, tựa sách, tác giả, tóm tắt, số lượng sách đang có và số lượng sách có thể cho mượn).
IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_ThongtinDausach_22850034') AND type in (N'P', N'PC'))
    DROP PROCEDURE sp_ThongtinDausach_22850034;
GO

CREATE PROCEDURE sp_ThongtinDausach_22850034
    @isbn NVARCHAR(20)
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 0: Check if the book exists
    IF NOT EXISTS (SELECT * FROM dausach WHERE isbn = @isbn)
    BEGIN
        PRINT 'ERROR: ISBN khong ton tai!';
        RETURN;
    END

    -- Step 1: Print the information of the book
    SELECT d.isbn, t.tuasach, t.tacgia, t.tomtat, COUNT(c.isbn) AS so_luong_sach_dang_co, COUNT(c.isbn) - COUNT(m.isbn) AS so_luong_sach_co_the_muon
    FROM dausach d
    JOIN tuasach t ON d.ma_tuasach = t.ma_tuasach
    LEFT JOIN cuonsach c ON d.isbn = c.isbn
    LEFT JOIN muon m ON c.isbn = m.isbn AND c.ma_cuonsach = m.ma_cuonsach
    WHERE d.isbn = @isbn
    GROUP BY d.isbn, t.tuasach, t.tacgia, t.tomtat;
END
GO


-- Stored procedure BT3-3 (Liệt kê những độc giả người lớn đang mượn sách)
-- Tên: sp_ThongtinNguoilonDangmuon_22850034
-- Tham số: không có
-- Nội dung: Liệt kê thông tin của những độc giả người lớn đang mượn sách.
IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_ThongtinNguoilonDangmuon_22850034') AND type in (N'P', N'PC'))
    DROP PROCEDURE sp_ThongtinNguoilonDangmuon_22850034;
GO

CREATE PROCEDURE sp_ThongtinNguoilonDangmuon_22850034
AS
BEGIN
    SET NOCOUNT ON;

    SELECT d.ma_docgia, d.ho, d.tenlot, d.ten, d.ngaysinh, n.sonha, n.duong, n.quan, n.dienthoai, n.han_sd, m.isbn, m.ma_cuonsach, m.ngay_muon, m.ngay_hethan
    FROM docgia d
    JOIN nguoilon n ON d.ma_docgia = n.ma_docgia
    JOIN muon m ON d.ma_docgia = m.ma_docgia
    JOIN qtrinhmuon q ON m.isbn = q.isbn AND m.ma_cuonsach = q.ma_cuonsach AND m.ma_docgia = q.ma_DocGia
    WHERE m.ngay_hethan >= GETDATE() AND q.ngay_tra IS NULL;
END


-- Stored procedure BT3-4 (Liệt kê những độc giả người lớn đang mượn sách quá hạn)
-- Tên: sp_ThongtinNguoilonQuahan_22850034
-- Tham số: không có
-- Nội dung: Liệt kê thông tin của những độc giả người lớn đang mượn sách quá hạn.
IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_ThongtinNguoilonQuahan_22850034') AND type in (N'P', N'PC'))
    DROP PROCEDURE sp_ThongtinNguoilonQuahan_22850034;
GO

CREATE PROCEDURE sp_ThongtinNguoilonQuahan_22850034
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1: Print the information of adult readers who are currently borrowing books
    SELECT d.ma_docgia, d.ho, d.tenlot, d.ten, d.ngaysinh, n.sonha, n.duong, n.quan, n.dienthoai, n.han_sd, m.isbn, m.ma_cuonsach, m.ngay_muon, m.ngay_hethan
    FROM docgia d
    JOIN nguoilon n ON d.ma_docgia = n.ma_docgia
    JOIN muon m ON d.ma_docgia = m.ma_docgia
    JOIN qtrinhmuon q ON m.isbn = q.isbn AND m.ma_cuonsach = q.ma_cuonsach AND m.ma_docgia = q.ma_DocGia
    WHERE m.ngay_hethan < GETDATE() AND q.ngay_tra IS NULL;
END
GO


-- Stored procedure BT3-5 (Liệt kê những độc giả người lớn đang mượn sách có trẻ em cũng đang mượn sách)
-- Tên: sp_DocGiaCoTreEmMuon_22850034
-- Tham số: không có
-- Nội dung: Liệt kê thông tin của những độc giả người lớn đang mượn sách có trẻ em cũng đang mượn sách.
IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_DocGiaCoTreEmMuon_22850034') AND type in (N'P', N'PC'))
    DROP PROCEDURE sp_DocGiaCoTreEmMuon_22850034;
GO

CREATE PROCEDURE sp_DocGiaCoTreEmMuon_22850034
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1: Print the information of adult readers who are currently borrowing books
    SELECT d.ma_docgia, d.ho, d.tenlot, d.ten, d.ngaysinh, n.sonha, n.duong, n.quan, n.dienthoai, n.han_sd, m.isbn, m.ma_cuonsach, m.ngay_muon, m.ngay_hethan, 'nguoi_lon' AS loai
    FROM docgia d
    JOIN nguoilon n ON d.ma_docgia = n.ma_docgia
    JOIN muon m ON d.ma_docgia = m.ma_docgia
    JOIN qtrinhmuon q ON m.isbn = q.isbn AND m.ma_cuonsach = q.ma_cuonsach AND m.ma_docgia = q.ma_DocGia
    WHERE m.ngay_hethan >= GETDATE() AND q.ngay_tra IS NULL
    UNION
    SELECT d.ma_docgia, d.ho, d.tenlot, d.ten, d.ngaysinh, n.sonha, n.duong, n.quan, n.dienthoai, n.han_sd, m.isbn, m.ma_cuonsach, m.ngay_muon, m.ngay_hethan, 'tre_em' AS loai
    FROM treem t
    JOIN docgia d ON t.ma_docgia = d.ma_docgia
    JOIN nguoilon n ON t.ma_docgia_nguoilon = n.ma_docgia
    JOIN muon m ON d.ma_docgia = m.ma_docgia
    JOIN qtrinhmuon q ON m.isbn = q.isbn AND m.ma_cuonsach = q.ma_cuonsach AND m.ma_docgia = q.ma_DocGia
    WHERE m.ngay_hethan >= GETDATE() AND q.ngay_tra IS NULL;
END
GO