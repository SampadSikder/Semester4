DECLARE
	v_out_phone_no VARCHAR2(50);
	
BEGIN 
	CREATE TABLE NEW_TABLE(
	ID VARCHAR2(50),
	PHONE_NO VARCHAR2(50),
	CONSTRAINT CONTACT_PK PRIMARY KEY(ID);
	)
	SELECT PHONE INTO v_out_phone_no from CONTACT WHERE ID='Abhijit';
	format_phone(v_out_phone_no);
	INSERT INTO NEW_TABLE VALUES('Abhijit', v_out_phone_no);
END;
/ 