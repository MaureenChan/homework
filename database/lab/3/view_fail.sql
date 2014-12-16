use SC
go
create view fail as
	select student.s_no, sname, teacher_course.cno
		from student, student_course, teacher_course
		where score < '60'
		and student.s_no = student_course.s_no
		and student_course.tcid = teacher_course.tcid;
