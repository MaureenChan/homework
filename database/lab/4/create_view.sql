
use student
go
create view ies_student_view as
	select s_no, sname, sex, sbirthday, spname 
		from student, speciality 
		where student.spno = speciality.spno 
			and student.dno in (
				select department.dno 
					from department
					where dept_name = 'computer'
		);



