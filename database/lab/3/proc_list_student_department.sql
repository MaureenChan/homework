use SC
go 
create procedure list_student_department
@dno char(6)
as
	select * from student 
		where dno = @dno;
