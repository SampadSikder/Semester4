--SELECT FIRST_NAME||' '||LAST_NAME||'''s' || ' SALARY WITH COMMISSION IS '|| (SALARY+NVL(COMMISSION_PCT,0))*12 "ANNUAL SALARY" FROM EMPLOYEES;
--SELECT FIRST_NAME||' '||LAST_NAME||'''s' || ' SALARY WITH COMMISSION IS '|| (SALARY+NVL(COMMISSION_PCT,0))*12 "ANNUAL SALARY" FROM EMPLOYEES WHERE FIRST_NAME LIKE '%PAUL%' OR LAST_NAME LIKE '%PAUL';
--SELECT FIRST_NAME||' '||LAST_NAME||'''s' || ' SALARY WITH COMMISSION IS '|| (SALARY+NVL(COMMISSION_PCT,0))*12 "ANNUAL SALARY", DEPARTMENT_ID FROM EMPLOYEES 
--ORDER BY DEPARTMENT_ID, SALARY DESC;
--SELECT FIRST_NAME||' '||LAST_NAME||'''s' || ' SALARY WITH COMMISSION IS '|| (SALARY+NVL(COMMISSION_PCT,0))*12 "ANNUAL SALARY" FROM EMPLOYEES WHERE EMPLOYEE_ID=&EMPLOYEE_IN;
SELECT &INPUT FROM EMPLOYEES ORDER BY &&INPUT;  
select ((select count(city) from station)-(select count(distinct city) from station)) from dual;
