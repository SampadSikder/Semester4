CREATE OR REPLACE PROCEDURE format_phone
(p_phone_no IN OUT VARCHAR2) IS
BEGIN
	p_phone_no := '(' || SUBSTR(p_phone_no,1,3) || ')' ||
			SUBSTR(p_phone_no,4,3) ||'-'|| SUBSTR(p_phone_no,7);
			
END format_phone;
/
DECLARE
	v_out_phone_no VARCHAR2(50);
	
BEGIN 
	SELECT PHONE_NO INTO v_out_phone_no from CONTACT WHERE ID='Abhijit';
	format_phone(v_out_phone_no);
	INSERT INTO NEW_TABLE VALUES('Abhijit', v_out_phone_no);
END;
/ 

