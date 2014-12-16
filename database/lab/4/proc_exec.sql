-- use SC
-- go
-- execute proc_student_department @dept_dno='1' ;

-- use student
-- go
-- exec proc_student_course 
-- @class_no = '001',
-- @spno = '100',
-- @dno = '1',
-- @tcid = '9999';

use student
go
exec proc_reward
	@s_no = '3212';
