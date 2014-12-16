-- use SC
-- go
-- execute proc_student_department @dept_dno='1' ;

use SC
go
exec proc_student_course 
@class_no = '001',
@spno = '100',
@dno = '1',
@tcid = '9999';
