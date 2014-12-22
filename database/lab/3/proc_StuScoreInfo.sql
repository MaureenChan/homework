use SC
go 
create procedure StuScoreInfo
as
	select student.class_no, student.s_no, sname, sex, cname, score
		from student, course, student_course, teacher_course
		where student.s_no = student_course.s_no
			and student_course.tcid = teacher_course.tcid	
			and teacher_course.cno = course.cno

