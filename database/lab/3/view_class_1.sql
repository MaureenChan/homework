use SC
go
create view class_1 as
	select student.s_no, sname, spname, score
		from student, student_course, speciality
		where tcid = '2222' 
		and student.s_no = student_course.s_no
		and student.spno = speciality.spno;


