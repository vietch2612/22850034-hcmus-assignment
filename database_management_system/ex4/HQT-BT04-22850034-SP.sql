-- Database Management System
-- Homework 04
-- MSSV: 22850034
-- Họ và tên: Cao Hoài Việt
-- Email: 22850034@student.hcmus.edu.vn

-- Stored procedure BT4-6 (Cập nhật trạng thái của đầu sách)
-- Tên: sp_CapnhatTrangthaiDausach_22850034
-- Nôi dung: Cập nhật trạng thái của một đầu sách cụ thể tương ứng với isbn: 
-- nếu đầu sách này không còn cuốn sách nào trong thư viện thì tình trạng của đầu sách là 'N';
-- nếu đầu sách còn một quyển sách trở lên thì cập nhật tình trạng của đầu sách là 'Y'.
-- Tham số: isbn - mã số sách
-- Bước thực hiện:
-- [1] Xác định số cuốn sách hiện còn trong thư viện của đầu sách có isbn.
-- [2] Nếu không còn quyển nào:
-- [2.1] Cập nhật tình trạng đầu sách là 'N'.
-- [3] Nếu còn ít nhất 1 quyển:
-- [3.1] Cập nhật tình trạng đầu sách là 'Y'.
IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_CapnhatTrangthaiDausach_22850034') AND type in (N'P', N'PC'))
    DROP PROCEDURE sp_CapnhatTrangthaiDausach_22850034;
GO

CREATE PROCEDURE sp_CapnhatTrangthaiDausach_22850034
    @isbn CHAR(13)
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1: Determine the number of remaining books in the library for the book with isbn
    DECLARE @total_books INT = (SELECT COUNT(*) FROM cuonsach WHERE isbn = @isbn);
    DECLARE @borrowing_books INT = (SELECT COUNT(*) 
                                    FROM muon m 
                                    LEFT JOIN qtrinhmuon q 
                                    ON m.isbn = q.isbn AND m.ma_cuonsach = q.ma_cuonsach
                                    WHERE m.isbn = @isbn AND q.ngay_tra IS NULL
                                    GROUP BY m.isbn);
    DECLARE @remaining_books INT = @total_books - @borrowing_books;

    -- Step 2: If there is no remaining book
    IF @remaining_books = 0
    BEGIN
        -- Step 2.1: Update the status of the book to 'N'
        UPDATE dausach SET trangthai = 'N' WHERE isbn = @isbn;
    END
    ELSE
    BEGIN
        -- Step 3.1: Update the status of the book to 'Y'
        UPDATE dausach SET trangthai = 'Y' WHERE isbn = @isbn;
    END
END

-- Stored procedure BT4-7 (Thêm tựa sách mới)
-- Tên: sp_ThemTuaSach_22850034
-- Nôi dung: Thêm 1 tựa sách mới vào hệ thống với điều kiện là bộ 3 thuộc tính (tựa sách, tác giả, tóm
-- Và phải bảo đảm thoả quỳ định
-- tát, phải khác với các bộ trong bảng tựa sách đã có. Và phải bảo đảm thoả quy định QĐ-2 được tuấn
-- Tham số: Sinh viên tự xác định.
-- Bước thực hiện:
-- [1] Xác định mã tựa sách sẽ cấp cho tựa sách này thỏa quy định QĐ-2.
-- [2] Kiểm tra phải có ít nhất 1 trong 3 thuộc tính tựa sách, tác giả, tóm tắt khác với các bộ trong bảng tựa sách đã có.
-- [3] Nếu thỏa điều kiện này thì:
-- [3.1] Thêm vào tựa sách.
-- [4] Nếu không thỏa điều kiện thì:
-- [4.1] Thông báo lỗi.
-- [4.2] Chấm dứt stored procedure.
-- QD2: Mã tựa sách là số thứ tự của các tựa sách có trong hệ thống bắt đầu từ 1. Khi thêm mới phải kiểm tra có những số thứ tự bị xóa thì bổ sung vào những số thứ tự còn trống này;
-- nếu không có (nghĩa là những số thứ tự liên tục với nhau) thì thêm với số thứ tự tiếp theo.
-- Trong trường hợp xóa thì không phải chỉnh sửa lại số thứ tự của các tựa sách ở phía sau.
IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_ThemTuaSach_22850034') AND type in (N'P', N'PC'))
    DROP PROCEDURE sp_ThemTuaSach_22850034;
GO

CREATE PROCEDURE sp_ThemTuaSach_22850034
    @tuasach NVARCHAR(100),
    @tacgia NVARCHAR(100),
    @tomtat NVARCHAR(100)
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1: Determine the id of the book title to be assigned to this book title to satisfy the QD-2 regulation
    DECLARE @id INT = (SELECT MIN(ma_tuasach) + 1 FROM tuasach WHERE ma_tuasach + 1 NOT IN (SELECT ma_tuasach FROM tuasach));
    IF @id IS NULL
        SET @id = (SELECT MAX(ma_tuasach) + 1 FROM tuasach);

    -- Step 2: Check if at least 1 of the 3 attributes title, author, summary is different from the existing book titles
    IF NOT EXISTS (SELECT * FROM tuasach WHERE tuasach = @tuasach OR tacgia = @tacgia OR tomtat = @tomtat)
    BEGIN
        -- Step 3.1: Add to the book title
        INSERT INTO tuasach (ma_tuasach, tuasach, tacgia, tomtat) VALUES (@id, @tuasach, @tacgia, @tomtat);
    END
    ELSE
    BEGIN
        -- Step 4.1: Error message
        PRINT 'ERROR: Tựa sách, tác giả hoặc tóm tắt đã tồn tại trong hệ thống!';
        RETURN;
    END
END


-- Stored procedure BT4-8 (Thêm cuốn sách mới)
-- Tên: sp_ThemCuonSach_22850034
-- Nội dung: Thêm cuốn sách mới vào hệ thống với điều kiện phải bảo đảm quy định
-- QĐ-3 được tuân thủ. Và phải cập nhật trạng thái của đầu sách tương ứng.
-- Tham số: Sinh viên tự xác định.
-- Bước thực hiện:
-- [1] Kiểm tra mã isbn nếu không tồn tại thì thông báo & ngừng xử lý.
-- [2] Xác định mã cuốn sách sẽ cấp cho cuốn sách này thỏa quy định QĐ-3.
-- [3] Thêm cuốn sách mới với mã cuốn sách đã xác định và tình trạng là yes ('Y').
-- [4] Thay đổi trạng thái của đầu sách tương ứng là yes ('Y').
-- QD3: Tương tự, mã cuốn sách và mã độc giả cũng là số thứ tự như mã tựa sách (QĐ-2).
IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_ThemCuonSach_22850034') AND type in (N'P', N'PC'))
    DROP PROCEDURE sp_ThemCuonSach_22850034;
GO

CREATE PROCEDURE sp_ThemCuonSach_22850034
    @isbn CHAR(13)
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1: Check if the isbn exists
    IF NOT EXISTS (SELECT * FROM dausach WHERE isbn = @isbn)
    BEGIN
        PRINT 'ERROR: ISBN không tồn tại!';
        RETURN;
    END

    -- Step 2: Determine the id of the book to be assigned to this book to satisfy the QD-3 regulation
    DECLARE @id INT = (SELECT MIN(ma_cuonsach) + 1 FROM cuonsach WHERE ma_cuonsach + 1 NOT IN (SELECT ma_cuonsach FROM cuonsach));
    IF @id IS NULL
        SET @id = (SELECT MAX(ma_cuonsach) + 1 FROM cuonsach);

    -- Step 3: Add a new book with the determined book id and status is yes ('Y')
    INSERT INTO cuonsach (ma_cuonsach, isbn, tinhtrang) VALUES (@id, @isbn, 'Y');

    -- Step 4: Change the status of the corresponding book to yes ('Y')
    EXEC sp_CapnhatTrangthaiDausach_22850034 @isbn;
END


-- Stored procedure BT4-9 (Thêm độc giả người lớn)
-- Tên: sp_ThemNguoilon_22850034
-- Nôi dung: Thêm thông tin mới vào bảng dữ liệu người lớn và bảng dữ liệu độc giả của hệ thống.
-- Tham số: Sinh viên tự xác định.
-- Bước thưc hiên:
-- [1] Xác định mã độc giả sẽ cấp cho độc giả người lớn này thỏa QĐ-3 (tương tự như mã tựa sách).
-- [2] Thêm một bộ dữ liệu vào bảng độc giả.
-- [3] Kiểm tra tuổi của độc giả này có đủ 18 tuổi.
-- [4] Nếu không đủ tuổi :
-- [4.1] Thông báo lỗi.
-- [4.2] Chấm dứt stored procedure.
-- [5] Nếu đủ tuổi thì:
-- [5.1] Thêm một bộ dữ liệu vào bảng người lớn.
-- QD3: Tương tự, mã cuốn sách và mã độc giả cũng là số thứ tự như mã tựa sách (QĐ-2).
IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_ThemNguoilon_22850034') AND type in (N'P', N'PC'))
    DROP PROCEDURE sp_ThemNguoilon_22850034;
GO

CREATE PROCEDURE sp_ThemNguoilon_22850034
    @ho NVARCHAR(50),
    @tenlot NVARCHAR(50),
    @ten NVARCHAR(50),
    @ngaysinh DATE,
    @sonha NVARCHAR(50),
    @duong NVARCHAR(50),
    @quan NVARCHAR(50),
    @dienthoai NVARCHAR(15),
    @han_sd DATE
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1: Determine the id of the reader to be assigned to this adult reader to satisfy the QD-3 regulation
    DECLARE @id INT = (SELECT MIN(ma_docgia) + 1 FROM docgia WHERE ma_docgia + 1 NOT IN (SELECT ma_docgia FROM docgia));
    IF @id IS NULL
        SET @id = (SELECT MAX(ma_docgia) + 1 FROM docgia);

    -- Step 2: Add a new data set to the reader table
    INSERT INTO docgia (ma_docgia, ho, tenlot, ten, ngaysinh) VALUES (@id, @ho, @tenlot, @ten, @ngaysinh);

    -- Step 3: Check the age of this reader is enough 18 years old
    IF DATEDIFF(YEAR, @ngaysinh, GETDATE()) < 18
    BEGIN
        -- Step 4.1: Error message
        PRINT 'ERROR: Độc giả chưa đủ 18 tuổi!';
        RETURN;
    END
    ELSE
    BEGIN
        -- Step 5.1: Add a new data set to the adult table
        INSERT INTO nguoilon (ma_docgia, sonha, duong, quan, dienthoai, han_sd) VALUES (@id, @sonha, @duong, @quan, @dienthoai, @han_sd);
    END
END


-- Stored procedure BT4-10 (Thêm độc giả trẻ em)
-- Tên: sp_ThemTreEm_228050034
-- Nôi dung: thêm thông tin mới vào bảng dữ liệu trẻ em và bảng dữ liệu độc giả trong hệ thống.
-- Bước thưc hiên:
-- [1] Xác định mã độc giả sẽ cấp cho độc giả trẻ em này thỏa quy định QĐ-3 (tương tự như mã tựa sách).
-- [2] Thêm một bộ dữ liệu vào bảng độc giả.
-- [3] Đếm số lượng trẻ em của độc giả người lớn sẽ bảo lãnh trẻ em mới này.
-- [4] Kiểm tra, nếu số lượng không thỏa quy định QĐ-1 thì:
-- [4.1] Thông báo lỗi.
-- [4.2] Chấm dứt stored procedure.
-- [5] Nếu thỏa quy định QĐ-1 thì: Thêm một bộ dữ liệu vào bảng trẻ em.
-- QD3: Tương tự, mã cuốn sách và mã độc giả cũng là số thứ tự như mã tựa sách (QĐ-2).
-- QD1: Mỗi độc giả người lớn chỉ có thể bảo lãnh tối đa cho 2 trẻ em.

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_ThemTreEm_22850034') AND type in (N'P', N'PC'))
    DROP PROCEDURE sp_ThemTreEm_22850034;
GO

CREATE PROCEDURE sp_ThemTreEm_22850034
    @ho NVARCHAR(50),
    @tenlot NVARCHAR(50),
    @ten NVARCHAR(50),
    @ngaysinh DATE,
    @ma_docgia_nguoilon INT
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1: Determine the id of the reader to be assigned to this child reader to satisfy the QD-3 regulation
    DECLARE @id INT = (SELECT MIN(ma_docgia) + 1 FROM docgia WHERE ma_docgia + 1 NOT IN (SELECT ma_docgia FROM docgia));
    IF @id IS NULL
        SET @id = (SELECT MAX(ma_docgia) + 1 FROM docgia);

    -- Step 2: Add a new data set to the reader table
    INSERT INTO docgia (ma_docgia, ho, tenlot, ten, ngaysinh) VALUES (@id, @ho, @tenlot, @ten, @ngaysinh);

    -- Step 3: Count the number of children of the adult reader who will sponsor this new child
    DECLARE @count_children INT = (SELECT COUNT(*) FROM treem WHERE ma_docgia_nguoilon = @ma_docgia_nguoilon);

    -- Step 4: Check, if the number does not satisfy the QD-1 regulation
    IF @count_children >= 2
    BEGIN
        -- Step 4.1: Error message
        PRINT 'ERROR: Độc giả người lớn đã bảo lãnh tối đa 2 trẻ em!';
        RETURN;
    END
    ELSE
    BEGIN
        -- Step 5.1: Add a new data set to the child table
        INSERT INTO treem(ma_docgia, ma_docgia_nguoilon) VALUES (@id, @ma_docgia_nguoilon);
    END
END