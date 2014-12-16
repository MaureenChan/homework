use SC
go
alter procedure proc_student_department
@s_no char(8)
as
	select s_no, sname, sbirthday, dept_name, spname
		from student, department, speciality
		where s_no = @s_no 
			and student.dno = department.dno
			and student.spno = speciality.spno;
