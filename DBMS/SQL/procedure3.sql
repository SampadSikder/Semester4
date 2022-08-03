CREATE OR REPLACE PROCEDURE format_phone
(p_phone_no IN OUT EMPLOYEES.PHONE_NUMBER%TYPE, emp_id IN EMPLOYEES.EMPLOYEE_ID%TYPE) IS
BEGIN
	SET p_phone_no = '(' || SUBSTR(p_phone_no,1,3) || ')' ||
			SUBSTR(p_phone_no,4,3) ||'-'|| SUBSTR(p_phone_no,7)
			WHERE emp_id=201;
END format_phone;
/
/*DECLARE
	emp_phone EMPLOYEES.PHONE_NUMBER%TYPE;
	emp_id EMPLOYEES.EMPLOYEE_ID%TYPE;
BEGIN
	---emp_phone:='8006330575';
	format_phone(emp_phone,201);
	---DBMS_OUTPUT.PUT_LINE(emp_phone);
END;
/*/
