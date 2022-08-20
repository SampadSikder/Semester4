---SELECT FIRST_NAME||' ' ||LAST_NAME NAME FROM EMPLOYEES WHERE UPPER(FIRST_NAME) LIKE 'WILLIAM';
---SELECT FIRST_NAME FROM EMPLOYEES WHERE UPPER(SUBSTR(FIRST_NAME,1,3)) LIKE 'SHE';
---SELECT FIRST_NAME,RPAD(SALARY,10,'*')SALARY FROM EMPLOYEES WHERE UPPER(SUBSTR(FIRST_NAME,1,3)) LIKE 'SHE';
---SELECT CONCAT(FIRST_NAME, LAST_NAME), RPAD(SALARY,10,'*')SALARY FROM EMPLOYEES WHERE UPPER(SUBSTR(FIRST_NAME,1,3)) LIKE 'SHE';
---SELECT FIRST_NAME FROM EMPLOYEES WHERE LENGTH(CONCAT(FIRST_NAME,LAST_NAME))>=15;
---SELECT FIRST_NAME, (SYSDATE-HIRE_DATE)/365 AS YEARS FROM EMPLOYEES WHERE (SYSDATE-HIRE_DATE)/365 >=20;
---SELECT SYSDATE FROM DUAL;
---SELECT ROUND(45.92,-2) FROM DUAL;
SELECT FIRST_NAME, ROUND((SYSDATE-HIRE_DATE)/365, 0) AS YEARS, (((SYSDATE-HIRE_DATE)/365)-ROUND(SUBSTR((SYSDATE-HIRE_DATE)/365,1,2)/30),0)) AS MONTHS FROM EMPLOYEES WHERE (SYSDATE-HIRE_DATE)/365 >=20;
SELECT FIRST_NAME, TRUNC((SYSDATE-HIRE_DATE)/365, 0) AS YEARS, TRUNC(MOD((SYSDATE-HIRE_DATE),365)/30,0) AS MONTHS, TRUNC(MOD((SYSDATE-HIRE_DATE),365),0) AS DAYS FROM EMPLOYEES WHERE (SYSDATE-HIRE_DATE)/365 >=20;