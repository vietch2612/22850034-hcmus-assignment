-- Database Management System
-- Homework 02
-- MSSV: 22850034
-- Họ và tên: Cao Hoài Việt

-- Truy vấn nhóm A

-- 1. Liệt kê danh sách thông tin độc giả có mã độc giả trong khoảng từ 25 đến 88
-- Test passed
SELECT * 
FROM docgia
WHERE ma_docgia BETWEEN 25 AND 88;

-- 2. Liệt kê danh sách độc giả người lớn có mã độc giả trong khoảng 25 đến 88 (Mã độc giả, họ tên, ngày sinh, điện thoại, hạn sử dụng)
-- Test passed
SELECT nguoilon.ma_docgia, ho, tenlot, ten, ngaysinh, nguoilon.dienthoai, nguoilon.han_sd
FROM docgia
JOIN nguoilon ON docgia.ma_docgia = nguoilon.ma_docgia
WHERE nguoilon.ma_docgia BETWEEN 25 AND 88;

-- 3. Liệt kê họ tên độc giả trẻ em và họ tên độc giả người lớn đã bảo lãnh trẻ em đó có địa chỉ nhà ở quận 1, 6, 7, BT và GV
-- Test passed
SELECT 
    te.ho as TE_Ho,
    te.tenlot as TE_Lot,
    te.ten as TE_Ten
    nl.ho as NL_Ho,
    nl.tenlot as NL_Lot,
    nl.ten as NL_Ten
FROM (SELECT ho, tenlot, ten, ma_docgia_nguoilon
    FROM docgia
    JOIN treem ON docgia.ma_docgia = treem.ma_docgia) AS te
JOIN (SELECT ho, tenlot, ten, docgia.ma_docgia 
    FROM docgia
    JOIN nguoilon ON docgia.ma_docgia = nguoilon.ma_docgia
    WHERE quan IN ('1', '6', '7', 'BT', 'GV')) AS nl
ON te.ma_docgia_nguoilon = nl.ma_docgia;

-- 4. Liệt kê danh sách họ tên và mã độc giả không có bảo lãnh trẻ em
-- Test passed
SELECT docgia.ma_docgia, ho, tenlot, ten
FROM docgia
LEFT JOIN treem ON docgia.ma_docgia = treem.ma_docgia_nguoilon
WHERE treem.ma_docgia IS NULL;

-- 5. Liêt kê tất cả họ tên đọc giả người lớn có trong hệ thống và số lượng trẻ em mà họ bảo lãnh (nếu có)
-- Test passed
SELECT ho, tenlot, ten, COUNT(treem.ma_docgia_nguoilon) AS so_luong_tre_em
FROM docgia
JOIN nguoilon ON docgia.ma_docgia = nguoilon.ma_docgia
LEFT JOIN treem ON nguoilon.ma_docgia = treem.ma_docgia_nguoilon
GROUP BY docgia.ma_docgia;

-- 6. Liệt kê thông tin các đầu sách vẫn còn khả năng được mượn
-- Test passed
SELECT tuasach.tuasach, tuasach.tacgia, tuasach.tomtat
FROM tuasach
JOIN dausach ON tuasach.ma_tuasach = dausach.ma_tuasach
-- WHERE dausach.trangthai IN ('Con', 'con', 'OK', 'ok', 'Ok', 'Co the muon', 'co the muon', 'Co the muon sach', 'co the muon sach');
WHERE dausach.trangthai = 'Con';

-- 7. Với mỗi đầu sách, liệt kê thông tin đầu sách và số lượng cuốn sách vẫn còn trong thư viện
-- Test passed
SELECT tuasach.tuasach, tuasach.tacgia, tuasach.tomtat, COUNT(cuonsach.ma_cuonsach) AS so_luong_cuon_sach
FROM tuasach
JOIN dausach ON tuasach.ma_tuasach = dausach.ma_tuasach
JOIN cuonsach ON dausach.isbn = cuonsach.isbn
LEFT JOIN muon ON cuonsach.ma_cuonsach = muon.ma_cuonsach
WHERE muon.ngay_hethan IS NULL OR muon.ngay_hethan <= now()
GROUP BY tuasach.tuasach, tuasach.tacgia, tuasach.tomtat;

-- 8. Với từng ngôn ngữ sách có trong hệ thống, cho biết tên ngôn ngữ và số lượng đầu sách thuộc ngôn ngữ đó
-- Test passed
SELECT ngonngu, COUNT(dausach.isbn) AS SoLuongDauSach
FROM dausach
GROUP BY ngonngu;