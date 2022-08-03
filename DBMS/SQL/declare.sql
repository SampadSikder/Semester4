DECLARE 
 emp_name employees.last_name%type;
 emp_sal employees.salary%type;

BEGIN
 query_emp(201, emp_name, emp_sal);
 DBMS_OUTPUT.PUT_LINE(emp_name||' has a salary of ' || to_char(emp_sal, '$999,999.00'));
END;
/