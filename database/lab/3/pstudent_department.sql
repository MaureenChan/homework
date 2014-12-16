use SC
go
create procedure proc_student_department
@dept_dno char(6)
as
	select * from student
		where dno = @dept_dno;

