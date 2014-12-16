use SC
go
alter view ies_student_view as
	select distinct student.s_no, sname, sex, sbirthday, dept_name, spname
	from department, speciality, student
	where department.dno = student.dno
	and student.spno = speciality.spno;


