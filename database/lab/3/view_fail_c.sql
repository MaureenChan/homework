use SC
go
create view fail2 as
	select student.s_no, sname, course.cname
		from student, student_course, teacher_course, course
		where score < '60'
		and student.s_no = student_course.s_no
		and student_course.tcid = teacher_course.tcid
		and teacher_course.cno = course.cno;
