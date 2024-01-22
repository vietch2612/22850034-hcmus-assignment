-- Database Management System
-- Homework 03, Stored Procedure and Function
-- MSSV: 22850034
-- Họ và tên: Cao Hoài Việt

-- REQUIREMENT 1. SCRIPT TO CREATE DATABASE, TABLES, AND SAMPLE DATA
-- Create the database
CREATE DATABASE BankingDB;
GO

-- Use the database
USE BankingDB;
GO

-- Create the Account table
CREATE TABLE Account (
    Id INT PRIMARY KEY,
    CustomerName NVARCHAR(255),
    Balance MONEY DEFAULT 0
);

-- Create the TransHistory table
CREATE TABLE TransHistory (
    Id INT PRIMARY KEY IDENTITY,
    transDate DATETIME DEFAULT GETDATE(),
    fromAccId INT,
    type CHAR(1),
    CONSTRAINT FK_TransHistory_Account FOREIGN KEY (fromAccId) REFERENCES Account(Id)
);

-- Insert sample data into the Account table
INSERT INTO Account (Id, CustomerName, Balance) VALUES
(1, 'Cao Hoai Viet', 1000000),
(2, 'Doan Thi Tam', 500000),
(3, 'Cao Gia Khang', 389000);

-- Insert sample data into the TransHistory table
INSERT INTO TransHistory (transDate, fromAccId, type) VALUES
(GETDATE(), 1, 'T'),
(GETDATE(), 2, 'W'),
(GETDATE(), 3, 'T'),
(GETDATE(), 2, 'T'),
(GETDATE(), 1, 'T'),
(GETDATE(), 1, 'W');


-- REQUIREMENT 2. SCRIPT TO CREATE A FUNCTION TO CHECK IF AN ACCOUNT EXISTS
IF OBJECT_ID('ufn_checkAccExists_22850034', 'FN') IS NOT NULL
    DROP FUNCTION ufn_checkAccExists_22850034
GO

CREATE FUNCTION ufn_checkAccExists_22850034(@accId INT)
RETURNS INT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM Account WHERE Id = @accId)
        RETURN 1;
    ELSE
        RETURN 0;
END;
GO



-- REQUIREMENT 3. SCRIPT TO CREATE A FUNCTION TO CHECK IF AN ACCOUNT HAS ENOUGH BALANCE
-- Drop the function if it exists
IF OBJECT_ID('ufn_checkAccBalance_22850034', 'FN') IS NOT NULL
    DROP FUNCTION ufn_checkAccBalance_22850034
GO

-- Create the function
CREATE FUNCTION ufn_checkAccBalance_22850034(@accId INT, @amount MONEY)
RETURNS INT
AS
BEGIN
    DECLARE @currentBalance MONEY;

    SELECT @currentBalance = Balance FROM Account WHERE Id = @accId;

    IF @currentBalance >= @amount
        RETURN 1;
    ELSE
        RETURN 0;
END;
GO

-- REQUIREMENT 4. SCRIPT TO CREATE A STORED PROCEDURE TO TRANSFER MONEY BETWEEN TWO ACCOUNTS
-- Drop the procedure if it exists
IF OBJECT_ID('usp_transferMoney_22850034', 'P') IS NOT NULL
    DROP PROCEDURE usp_transferMoney_22850034
GO
-- Create the procedure
CREATE PROCEDURE usp_transferMoney_22850034
    @fromAccId INT,
    @toAccId INT,
    @amount MONEY
AS
BEGIN
    SET NOCOUNT ON;

    -- Step 1.1 Check if the accounts exist
    IF dbo.ufn_checkAccExists_22850034(@fromAccId) = 0 OR dbo.ufn_checkAccExists_22850034(@toAccId) = 0
    BEGIN
        PRINT 'Lỗi: Một trong hai tài khoản không tồn tại. Vui lòng kiểm tra lại.';
        RETURN;
    END

    -- Step 1.2 Print the account information before the transfer
    DECLARE @accInfoFrom NVARCHAR(MAX), @accInfoTo NVARCHAR(MAX)
    SELECT @accInfoFrom = 'Mã tài khoản: ' + CONVERT(VARCHAR, Id) + ', Tên: ' + CustomerName + ', Số dư: ' + CONVERT(VARCHAR, Balance) FROM Account WHERE Id = @fromAccId
    SELECT @accInfoTo = 'Mã tài khoản: ' + CONVERT(VARCHAR, Id) + ', Tên: ' + CustomerName + ', Số dư: ' + CONVERT(VARCHAR, Balance) FROM Account WHERE Id = @toAccId
    PRINT @accInfoFrom
    PRINT @accInfoTo

    -- Step 2.1: Check if the source account has enough money to transfer
    IF dbo.ufn_checkAccBalance_22850034(@fromAccId, @amount) = 0
    BEGIN
        PRINT 'Lỗi: Tài khoản nguồn không đủ tiền để chuyển. Vui lòng kiểm tra lại.';
        RETURN;
    END

    -- Step 2.2: Print the transfer date
    PRINT 'Thông tin: Bắt đầu chuyển khoản lúc ' + CONVERT(VARCHAR, GETDATE(), 120);

    BEGIN TRANSACTION
    TRY
        -- Steps 3 and 4: Update balancess
        UPDATE Account SET Balance = Balance - @amount WHERE Id = @fromAccId
        UPDATE Account SET Balance = Balance + @amount WHERE Id = @toAccId

        -- Step 5: Record the transaction
        INSERT INTO TransHistory (fromAccId, type) VALUES (@fromAccId, 'T')

        -- Step 6: Display account details and completion time
        SELECT @accInfoFrom = 'Mã tài khoản: ' + CONVERT(VARCHAR, Id) + ', Tên: ' + CustomerName + ', Số dư: ' + CONVERT(VARCHAR, Balance) FROM Account WHERE Id = @fromAccId
        SELECT @accInfoTo = 'Mã tài khoản: ' + CONVERT(VARCHAR, Id) + ', Tên: ' + CustomerName + ', Số dư: ' + CONVERT(VARCHAR, Balance) FROM Account WHERE Id = @toAccId
        PRINT @accInfoFrom
        PRINT @accInfoTo
        PRINT 'Thông tin: Hoàn thành giao dịch lúc ' + CONVERT(VARCHAR, GETDATE(), 120)

        COMMIT TRANSACTION
    CATCH
        ROLLBACK TRANSACTION
        PRINT 'Lỗi: Có lỗi xảy ra trong quá trình thực hiện giao dịch. Vui lòng thử lại.'
    END TRY
END;