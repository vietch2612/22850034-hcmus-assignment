
-- Add validation if the student is doing more than one thesis in the same year
CREATE or ALTER TRIGGER tg_22850034_ThuchienLV ON ThucHienLV
AFTER 
    INSERT, DELETE, UPDATE
AS
BEGIN
    DECLARE @MaLV INT;
    DECLARE @MSSV INT;
    DECLARE @NamThucHien INT;
    DECLARE @Count INT;
    DECLARE @Message NVARCHAR(255);
    DECLARE @Error NVARCHAR(255);

    IF EXISTS (SELECT * FROM inserted)
    BEGIN
        SELECT @MaLV = MaLV, @MSSV = MSSV FROM inserted;
        SELECT @NamThucHien = NamThucHien FROM LuanVan WHERE MaLV = @MaLV;
        SELECT @Count = COUNT(*) FROM ThucHienLV WHERE MSSV = @MSSV AND MaLV IN (SELECT MaLV FROM LuanVan WHERE NamThucHien = @NamThucHien);
        IF @Count > 1
        BEGIN
            SELECT @Message = N'Sinh viên không thể thực hiện nhiều luận văn trong cùng một năm';
            RAISERROR(@Message, 16, 1);
        END
    END

    IF EXISTS (SELECT * FROM deleted)
    BEGIN
        SELECT @MaLV = MaLV, @MSSV = MSSV FROM deleted;
        SELECT @NamThucHien = NamThucHien FROM LuanVan WHERE MaLV = @MaLV;
        SELECT @Count = COUNT(*) FROM ThucHienLV WHERE MSSV = @MSSV AND MaLV IN (SELECT MaLV FROM LuanVan WHERE NamThucHien = @NamThucHien);
        IF @Count > 1
        BEGIN
            SELECT @Message = N'Sinh viên không thể thực hiện nhiều luận văn trong cùng một năm';
            RAISERROR(@Message, 16, 1);
        END
    END
END
GO

CREATE or ALTER PROCEDURE usp_22850034_ThuchienLV 
    @maLV_22850034 INT,
    @maSVTH1_22850034 INT,
    @maSVTH2_22850034 INT
AS
BEGIN
    DECLARE @message NVARCHAR(255);
    -- 1. Check if the thesis is exist, if not, raise an error
    IF NOT EXISTS (SELECT * FROM LuanVan WHERE MaLV = @maLV_22850034)
    BEGIN
        RAISERROR(N'Luận văn không tồn tại', 16, 1);
    END

    -- 2. Check if the students are exist, if not, raise an error
    IF NOT EXISTS (SELECT * FROM SinhVien WHERE MSSV = @maSVTH1_22850034)
    BEGIN
        SET @message = N'Sinh viên' + CAST(@maSVTH1_22850034 AS NVARCHAR(255)) + N' không tồn tại';
        RAISERROR(@message, 16, 1);
    END

    IF NOT EXISTS (SELECT * FROM SinhVien WHERE MSSV = @maSVTH2_22850034)
    BEGIN
        SET @message = N'Sinh viên' + CAST(@maSVTH1_22850034 AS NVARCHAR(255)) + N' không tồn tại';
        RAISERROR(@message, 16, 1);
    END

    -- Check if the thesis is assigned to the other students, if yes, raise an error
    IF EXISTS (SELECT * FROM ThucHienLV WHERE MaLV = @maLV_22850034)
    BEGIN
        SET @message = N'Luận văn' + CAST(@maLV_22850034 AS NVARCHAR(255)) + N' đã được phân công';
        RAISERROR(@message, 16, 1);
    END

    -- Check if other students are doing the thesis in the same year, if yes, raise an error
    DECLARE @NamThucHien INT;
    DECLARE @Count INT;
    SELECT @NamThucHien = NamThucHien FROM LuanVan WHERE MaLV = @maLV_22850034;
    SELECT @Count = COUNT(*) FROM ThucHienLV WHERE MaLV IN (SELECT MaLV FROM LuanVan WHERE NamThucHien = @NamThucHien);
    IF @Count > 0
    BEGIN
        RAISERROR(N'Sinh viên không thể thực hiện nhiều luận văn trong cùng một năm', 16, 1);
    END

    -- Assign the thesis to the students
    BEGIN TRY
        BEGIN TRANSACTION
        INSERT INTO ThucHienLV VALUES (@maLV_22850034, @maSVTH1_22850034);
        INSERT INTO ThucHienLV VALUES (@maLV_22850034, @maSVTH1_22850034);
        PRINT N'Phân công luận văn cho sinh vien' + CAST(@maSVTH1_22850034 AS NVARCHAR(255)) + N' và sinh viên ' + CAST(@maSVTH2_22850034 AS NVARCHAR(255));
        COMMIT TRANSACTION
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION
    END CATCH
END
GO